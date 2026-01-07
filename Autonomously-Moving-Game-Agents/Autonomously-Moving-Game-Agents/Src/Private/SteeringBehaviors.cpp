#include <vector>
#include <iostream>
#include <cmath>
#include "Path.h"
#include "SteeringBehaviors.h"
#include "Vehicle.h"
#include "Wall2D.h"
#include "Vector2D.h"
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

double SteeringBehaviors::TurnaoundTime(const Vehicle* pAgent, SVector2D TargetPos)
{
    return 0.0;
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

SVector2D SteeringBehaviors::VectorToWorldSpace(SVector2D SterringForce, SVector2D Heading, SVector2D Side)
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

SVector2D SteeringBehaviors::WallAvoidance(const std::vector<Wall2D>& walls)
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

SVector2D SteeringBehaviors::Interpose(const Vehicle* AgentA, const Vehicle* AgentB)
{
    //first we need to figure out where the two agents are going to be at
    //time T in the future. This is approximated by determining the time
    //taken to reach the midway point at the current time at max speed.
    SVector2D MidPoint = (AgentA->Pos() + AgentB->Pos()) / 2.0;

    double TimeToReachMidPoint = SVector2D::Distance(m_pVehicle->Pos(), MidPoint, m_pVehicle->MaxSpeed());

    //now we have T, we assume that agent A and agent B will continue on a
    //straight trajectory and extrapolate to get their future positions
    SVector2D APos = AgentA->Pos() + AgentA->Velocity() * TimeToReachMidPoint;
    SVector2D BPos = AgentB->Pos() + AgentB->Velocity() * TimeToReachMidPoint;

    //calculate the midpoint of these predicted positions
    MidPoint = (APos + BPos) / 2.0;

    //then steer to arrive at it
    return Arrive(MidPoint, EDeceleration::Fast);
}

SVector2D SteeringBehaviors::GetHidingPosition(const SVector2D& posOb, const double radiusOb, const SVector2D& posTarget)
{
    //calculate how far away the agent is to be from the chosen obtscle's
    //bounding radius
    const double DistanceFromBoundary = 30.0;

    double DistAway = radiusOb + DistanceFromBoundary;

    //calculate the heading toward the object from the target
    SVector2D ToOb = SVector2D::Normalize(posOb - posTarget);

    //scale it to size and add to the obstacle's position to get
    //the hiding spot.
    return (ToOb * DistAway) + posOb;
}

SVector2D SteeringBehaviors::Hide(const Vehicle* target, vector<BaseGameEntity*>& obstacles)
{
    double DistToClosest = MaxDouble;
    SVector2D BestHidingSpot;

    std::vector<BaseGameEntity*>::iterator curOb = obstacles.begin();

    while (curOb != obstacles.end())
    {
        //calculate the position of the hiding spot for this obstacle
        SVector2D HidingSpot = GetHidingPosition(
            (*curOb)->Pos(), (*curOb)->BRadius(), target->Pos()
        );

        //work in distance-squared space to find  the closest hiding
        //spot to the agent
        double dist = SVector2D::DistanceSquared(HidingSpot, m_pVehicle->Pos());

        if (dist < DistToClosest)
        {
            DistToClosest = dist;
            BestHidingSpot = HidingSpot;
        }

        ++curOb;
    }

    //if no suitable obstacles found then evade the target
    if (DistToClosest == MaxDouble)
    {
        return Evade(target);
    }

    return Arrive(BestHidingSpot, EDeceleration::Fast);
}

SVector2D SteeringBehaviors::FollowPath()
{
    //move to next target if close enough to current target (working in distance squared space)
    if (SVector2D::DistanceSquared(m_pPath->CurrentWaypoint(), m_pVehicle->Pos()) < m_WaypointSeekDistSq)
    {
        m_pPath->SetNextWaypoint();
    }
    if (!m_pPath->Finished())
    {
        return Seek(m_pPath->CurrentWaypoint());
    }
    else
    {
        return Arrive(m_pPath->CurrentWaypoint(), EDeceleration::Normal);
    }

    return SVector2D();
}

SVector2D SteeringBehaviors::OffsetPursuit(const Vehicle* leader, const SVector2D offset)
{
    //calculate the offset's position in the world space
    SVector2D WorldOffsetPos = PointToWorldSpace(offset, leader->Heading(), leader->Side(), leader->Pos());

    SVector2D ToOffset = WorldOffsetPos - m_pVehicle->Pos();

    //the look-ahead time is proportional to the distance between the leader
    //and the pursuer; and is inversely proportional to the sum of both
    //agent's velocities
    double LookAheadTime = ToOffset.Length() / (m_pVehicle->MaxSpeed() + leader->Speed());

    //now arrive at the predicted future position of the offset
    return Arrive(WorldOffsetPos + leader->Velocity() * LookAheadTime, EDeceleration::Fast);
}

SVector2D SteeringBehaviors::Separation(const std::vector<Vehicle*>& neighbors)
{
    SVector2D SteeringForce;

    for (int a = 0; a < neighbors.size(); ++a)
    {
        //make sure this  agent isn't included in the calculations and that
        //the agent being examined is close enough.
        if ((neighbors[a] != m_pVehicle) && neighbors[a]->IsTagged())
        {
            SVector2D ToAgent = m_pVehicle->Pos() - neighbors[a]->Pos();

            //scale the force inversely proportional to the  agent's   distance
            //from its neighbor.
            SteeringForce += SVector2D::Normalize(ToAgent) / ToAgent.Length();
        }
    }

    return SteeringForce;
}

SVector2D SteeringBehaviors::Alignment(const std::vector<Vehicle*>& neighbors)
{
    //used to record the avarage heading of the neighbors
    SVector2D AverageHeading;

    //used to count the number of vehicles in the neighborhood
    int NeighborCount = 0;

    //iterate through all the tagged vehicles and sum their heading vectors
    for (int a = 0; neighbors.size(); ++a)
    {
        //make sure *this* agent isn't included in the calculations and that
        //the agent being examined is close enough
        if ((neighbors[a] != m_pVehicle) && neighbors[a]->IsTagged())
        {
            AverageHeading += neighbors[a]->Heading();

            ++NeighborCount;
        }
    }

    //if the neighborhood contained one or more vehicles, average their
    //heading vectors.
    if (NeighborCount > 0)
    {
        AverageHeading /= (double)NeighborCount;

        AverageHeading -= m_pVehicle->Heading();
    }

    return AverageHeading;
}

SVector2D SteeringBehaviors::Cohesion(const std::vector<Vehicle*>& neighbors)
{
    //first find the center of mass of all the agents
    SVector2D CenterOfMass, SteeringForce;

    int NeighborCount = 0;

    //iterate through the neighbors and sum up all the position vectors
    for (int a = 0; neighbors.size(); ++a)
    {
        //make sure *this* agent isn't included in  the calculations and that
        //the agent being examined is a neighbor
        if ((neighbors[a] != m_pVehicle) && neighbors[a]->IsTagged())
        {
            CenterOfMass += neighbors[a]->Pos();

            ++NeighborCount;
        }

    }

    if (NeighborCount > 0)
    {
        //the  center of mass is the average of the  sum of positions
        CenterOfMass =  CenterOfMass / (double)NeighborCount;

        //now seek toward that position
        SteeringForce = Seek(CenterOfMass);
    }

    return SteeringForce();
}

bool SteeringBehaviors::AccumulateForce(SVector2D& RunningTot, SVector2D ForceToAdd)
{
    //calculate how much steering force the vehicle has used so far
    double MagnitudeSoFar = RunningTot.Length();

    //calculate how much steering force remains to be used by this vehicle
    double MagnitudeRemaining = m_pVehicle->MaxForce() - MagnitudeSoFar;

    //return false if there is no more force left to use
    if (MagnitudeRemaining <= 0.0) return false;

    //calculate the magnitude of the force we want to add
    double MagnitudeToAdd = ForceToAdd.Length();

    //if the magnitude of the sum of ForceToAdd and the running total
    //does not exceed the maximum force available to this vehicle, just
    //add together. Otherwise add as much of the ForceToAdd vector as
    //possible without going over the max.
    if (MagnitudeToAdd < MagnitudeRemaining)
    {
        RunningTot += ForceToAdd;
    }
    else
    {
        //add it to the steering force
        RunningTot += (SVector2D::Normalize(ForceToAdd) * MagnitudeRemaining);
    }

    return true;
}

SVector2D SteeringBehaviors::Calculate()
{
    //reset the force.
    m_vSteeringForce.Zero();

    SVector2D force;

    if (On(wall_avoidance))
    {
        force = WallAvoidance(m_pVehicle->World()->Walls) * m_dMultWallAvoidance;

        if (!AccumulateForce(m_vSteeringForce, force)) return m_vSteeringForce;
    }

    if (On(obstacle_avoidance))
    {
        force = Separation(m_pVehicle->World()->Agents()) * m_dMultSeparation;

        if (!AccumulateForce(m_vSteeringForce, force)) return m_vSteeringForce;
    }

    return m_vSteeringForce;
}
