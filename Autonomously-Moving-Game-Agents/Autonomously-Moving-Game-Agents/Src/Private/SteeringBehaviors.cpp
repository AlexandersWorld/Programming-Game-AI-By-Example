#include "SteeringBehaviors.h"
#include "Vehicle.h"
#include <cmath>

// Constructor: store vehicle pointer
SteeringBehaviors::SteeringBehaviors(Vehicle* Owner)
    : m_pVehicle(Owner)
{
}

SteeringBehaviors::SteeringBehaviors()
{
    std::random_device rd;
    m_RNG.seed(rd());
}

SVector2D SteeringBehaviors::Calculate()
{
    // EXAMPLE: only using Seek for now
    // Later you will add Flee, Arrive, Wander etc.

    SVector2D target(400, 300); // Temporary hardcoded target
    return Seek(target);
}

SVector2D SteeringBehaviors::Seek(const SVector2D& Target)
{
    // Desired velocity = normalize(target - position) * max_speed
    SVector2D desired = Target - m_pVehicle->Pos();
    desired.Normalize();
    desired *= m_pVehicle->MaxSpeed();

    // Steering force = desired - current velocity
    return desired - m_pVehicle->Velocity();
}

SVector2D SteeringBehaviors::Flee(const SVector2D& TargetPos)
{
    const double PanicDistanceSq = 100.0 * 100.0;

    // Calculate squared distance to avoid sqrt for performance
    float distSq = SVector2D::DistanceSquared(m_pVehicle->Pos(), TargetPos);

    if (distSq > PanicDistanceSq)
    {
        return SVector2D(0, 0);  // No fleeing if too far away
    }

    // Calculate desired velocity AWAY from target
    SVector2D DesiredVelocity = m_pVehicle->Pos() - TargetPos;
    DesiredVelocity.Normalize();

    // Scale by max speed (not add!)
    DesiredVelocity = DesiredVelocity * m_pVehicle->MaxSpeed();

    // Return steering force = desired - current
    return DesiredVelocity - m_pVehicle->Velocity();
}

SVector2D SteeringBehaviors::Arrive(const SVector2D& TargetPos, EDeceleration Deceleration)
{
    SVector2D ResultVelocity = SVector2D(0, 0);

    SVector2D ToTarget = TargetPos - m_pVehicle->Pos();

    double Dist = ToTarget.Lenth();
    
    if (Dist > 0)
    {
        const double DecelerationTweaker = 0.3;

        double Speed = Dist / ((double)Deceleration * DecelerationTweaker);

        Speed = min(Speed, m_pVehicle->MaxSpeed());

        SVector2D DesiredVelocity = ToTarget * Speed / Dist;

        ResultVelocity = (DesiredVelocity - m_pVehicle->Velocity());
    }

    return ResultVelocity;
}

SVector2D SteeringBehaviors::Pursuit(const Vehicle* Evader)
{
    SVector2D ToEvader = Evader->Pos() - m_pVehicle->Pos();

    double RelativeHeading = m_pVehicle->Heading().Dot(Evader->Heading());

    if (ToEvader.Dot(m_pVehicle->Heading() > 0 && RelativeHeading < -0.95) //acos(0.95)=18 degs
    {
        return Seek(Evader->Pos());
    }

    double LookAheadTime = ToEvader.Length() / (m_pVehicle->MaxSpeed() + evader->Speed());

    return Seek(evader->Pos() + evader->Velocity() * LookAheadTime);
}

double SteeringBehaviors::TurnaroundTime(const Vehicle* pAgent, SVector2D TargetPos)
{
    SVector2D ToTarget = SVector2D(TargetPos - pAgent->Pos()).Normalize();

    double dot = pAgent->Heading().Dot(ToTarget);

    const double coefficient = 0.5;

    //the dot product gives a value of 1 if the target is directly ahead and -1
    //if it is directly behind. Substracting 1 and multiplying by the negative of
    //the coefficient gives a positive value proportional to the rotational
    //displacement of the vehiucle and target.
    return (dot - 1.0) * -coefficient;
}

SVector2D SteeringBehaviors::Evade(const Vehicle* pursuer)
{
    SVector2D ToPursuer = pursuer->Pos() - m_pVehicle->Pos();

    //the look-ahead time is proportional to the distance between the pursuer
    //and the evader; and is inversely proportional to the sum of the agents' velocities

    double LookAheadTime = ToPursuer.Length() / (m_pVehicle->MaxSpeed() + pursuer->Speed());

    //now flee away from predicted future position of the pursuer
    return Flee(pursuer->Pos() + pursuer->Velocity() * LookAheadTime);
}

SVector2D SteeringBehaviors::Wander()
{
    //first, add a small random vector to the target's position (RandomClamped
    //return a value between -1 and 1)
    m_vWanderTarget += SVector2D(RandomClamped() * m_dWanderJitter, RandomClamped() * m_dWanderJitter);
    m_vWanderTarget.Normalize();

    //increase the length of the vector to the same as the radius
    //of the wander circle
    m_vWanderTarget *= m_dWanderRadius;
    
    //move the target into a position WanderDist in front of the agent
    SVector2D targetLocal = m_vWanterTarget + SVector2D(m_dWanderDistance, 0);


    return Flee(pursuer->Pos() + pursuer->Velocity() * LookAheadTime);
}
