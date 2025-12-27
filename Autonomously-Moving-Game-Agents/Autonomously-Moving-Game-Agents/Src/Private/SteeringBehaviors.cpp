#include <vector>
#include <iostream>
#include <cmath>
#include "SteeringBehaviors.h"
#include "Vehicle.h"
#include "Wall2D.h"
#include "Params.h"

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

    //project the target into world space
    SVector2D targetWorld = PointToWorldSpace(targetLocal, m_pVehicle->Heading(), m_pVehicle->Side(), m_pVehicle->Pos());

    return targetWorld - m_pVehicle->Pos();
}

SVector2D SteeringBehaviors::PointToWorldSpace(SVector2D targetLocal, SVector2D VehicleHeading, SVector2D VehicleSide, SVector2D VehiclePos)
{
    SVector2D worldPoint;

    worldPoint.x = (VehicleHeading.x * targetLocal.x) + (VehicleSide.x * targetLocal.y);

    worldPoint.y = (VehicleHeading.y * targetLocal.x) + (VehicleSide.y * targetLocal.y);

    worldPoint += VehiclePos;

    return worldPoint;
}

SVector2D SteeringBehaviors::VectorToWorldSpac(SVector2D SterringForce, SVector2D Heading, SVector2D Side)
{

}

SVector2D SteeringBehaviors::ObstacleAvoidance(const std::vector<BaseGameEntity*>& obstacles)
{
    //the detection box length is proportional to the agent's velocity
    m_dDBoxLength = Prm.MinDetectionBoxLength + (m_pVehicle->Speed() / m_pVehicle->MaxSpeed()) * Prm.MinDetectionBoxLength;

    m_pVehicle->World()->TagObstaclesWithinViewRange(m_pVehicle, m_dDBoxLength);

    BaseGameEntity* ClosesIntersectingObstacle = nullptr;

    double DistToClosestIP = MaxDouble;

    SVector2D LocalPosOfClosestObstacle;

    std::vector<BaseGameEntity*>::const_iterator curOb = obstacles.begin();

    while (curOb != obstacles.end())
    {
        //if the obstacle has been tagged within ranged proceed
        if ((*curOb)->IsTagged())
        {
            SVector2D LocalPos = PointToLocalSpace((*curOb)->Pos(), m_pVehicle->Heading(), m_pVehicle->Side(), m_pVehicle->Pos());

            if (LocalPos.x >= 0)
            {
                //if the distance from the x axis to the object's position is less
                //than its radius + half the width of the detection box then there
                //is a potential intersection.
                double ExpandedRadius = (*curOb)->BRadius() + m_pVehicle->BRadius();

                if (fabs(LocalPos.y) < ExpandedRadius)
                {
                    //now to do a  line/circle intersection test. The center of the
                    //circle is represented by (cX, cY). The intersection points are
                    //given by the formula x = cX +/-sqrt(r^2 - cY^2) for y=0.
                    //We only need to look at the smallest positive value of x because
                    //that will be the closest point of intersection.
                    double cX = LocalPos.x;
                    double cY = LocalPos.y;

                    //we only need to calculate the sqrt part of the above equation once
                    double SqrtPart = sqrt(ExpandedRadius * ExpandedRadius - cY * cY);

                    double ip = A - SqrtPart;

                    if (ip <= 0)
                    {
                        ip = A + SqrtPart;
                    }

                    //test to see if this is the closest so far. If it is, keep a
                    //record of the obstacle and its local coordinates
                    if (ip < DistToClosestIP)
                    {
                        DistToClosestIP = ip;

                        ClosesIntersectingObstacle = *curOb;
                        LocalPosOfClosestObstacle = LocalPos;
                    }
                }
            }
        }
        ++curOb;
    }

    //if we have found an intersecting obstacle, calculate a steering
    //force away from it
    SVector2D SteeringForce;

    if (ClosesIntersectingObstacle)
    {
        //the closer the agent is to an object, the stronger the steering force should be
        double multiplier = 1.0 + (m_dDBoxLength - LocalPosOfClosestObstacle.x) / m_dDBoxLength;

        //calculate the lateral force
        SteeringForce.y = (ClosesIntersectingObstacle->BRadius() - LocalPosOfClosestObstacle.y) * multiplier;

        //apply a braking force proportional to the obstacle's distance from the vehicle.
        const double BrakingWeght = 0.2;

        SteeringForce.x = (ClosesIntersectingObstacle->BRadius() - LocalPosOfClosestObstacle.x) * BrakingWeght;
    }

    //finally, convert the steering vector  from local to world space
    return VectorToWorldSpace(SteeringForce, m_pVehicle->Heading(), m_pVehicle->Side());
}

Vector2D SteeringBehaviors::WallAvoidance(const std::vector<Wall2D>& walls)
{
    //the feelers are contained in a std::vector, m_Feelers
    CreateFeelers();

    double DistToThisIP = 0.0;
    double DistToClosestIP = MaxDouble;

    //this will hold an index into the vector of walls
    int ClosestWall = -1;

    SVector2D SteeringForce, 
        point, //used for storing temporary info 
        ClosestPoint; //holds the closest intersection point

    //examine each feeler in turn
    for (int flr = 0; flr < m_Feelers.size(); ++flr)
    {
        //run through each wall checing for any intersection points
        for (int w = 0; w < walls.size(); ++w)
        {
            if (LineIntersection2D(m_pVehicle->Pos(), m_Feelers[flr], walls[w].From(), walls[w].To(), DistToThisIP, point))
            {
                //is this the closest found so far? If so keep a record
                if (DistToThisIP < DistToClosestIP)
                {
                    DistToClosestIP = DistToThisIP;

                    ClosestWall = w;

                    ClosestPoint = point;
                }
            }
        } //next wall

        //if an intersection point has been detected, calculate a force
        //that will direct the agent away
        if (ClosestWall >= 0)
        {
            //calculate by what distance the projected position of the agent
            //will overshoot the wall
            SVector2D OverShoot = m_Feelers[flr] - ClosestPoint;

            //create a force in the direction of the wall normal, with a magnitude of the overshoot
            SteeringForce = walls[ClosestWall].Normal() * OverShoot.Length();

        }
    } // next feeler

    return SteeringForce;
}
