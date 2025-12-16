#include "SteeringBehaviors.h"
#include "Vehicle.h"
#include <cmath>

// Constructor: store vehicle pointer
SteeringBehaviors::SteeringBehaviors(Vehicle* owner)
    : m_pVehicle(owner)
{
}

SVector2D SteeringBehaviors::Calculate()
{
    // EXAMPLE: only using Seek for now
    // Later you will add Flee, Arrive, Wander etc.

    SVector2D target(400, 300); // Temporary hardcoded target
    return Seek(target);
}

SVector2D SteeringBehaviors::Seek(const SVector2D& target)
{
    // Desired velocity = normalize(target - position) * max_speed
    SVector2D desired = target - m_pVehicle->Pos();
    desired.Normalize();
    desired *= m_pVehicle->MaxSpeed();

    // Steering force = desired - current velocity
    return desired - m_pVehicle->Velocity();
}

SVector2D SteeringBehaviors::Flee(const SVector2D& TargetPos)
{
    const double PanicDistanceSq = 100.0 * 100.0;

    if (Vec2DDistance(m_pVehicle->Pos(), TargetPos) > PanicDistanceSq)
    {
        return Vector2D(0, 0);
    }

    SVector2D DesiredVelocity = m_pVehicle->Pos() - TargetPos;
    DesiredVelocity.Normalize();
    DesiredVelocity += m_pVehicle->MaxSpeed();

    return desired - m_pVehicle->Velocity();
}

SVector2D SteeringBehaviors::Arrive(const SVector2D& TargetPos, Deceleration deceleration)
{
    S2Vector2D ResultVelocity = S2Vector2D(0, 0);

    SVector2D ToTarget = TargetPos - m_pVehicle->Pos();

    double Dist = ToTarget.Lenth();
    
    if (Dist > 0)
    {
        const double DecelerationTweaker = 0.3;

        double Speed = Dist / ((double)deceleration * DecelerationTweaker);

        Speed = min(Speed, m_pVehicle->MaxSpeed());

        SVector2D DesiredVelocity = ToTarget * Speed / Dist;

        ResultVelocity = (DesiredVelocity - m_pVehicle->Velocity());
    }

    return ResultVelocity;
}