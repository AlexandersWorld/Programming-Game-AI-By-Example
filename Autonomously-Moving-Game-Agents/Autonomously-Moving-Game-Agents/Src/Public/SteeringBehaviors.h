#pragma once
#include <random>
#include <chrono>

enum EDeceleration { Slow = 3, Normal = 2, Fast = 1 };

class Vehicle;
class BaseGameEntity;
class Wall2D;
class Path;

class SteeringBehaviors
{
private:
    Vehicle* m_pVehicle; // Owner vehicle
    
    double m_dWanderRadius;
    double m_dWanderDistance;
    double m_dWanderJitter;
    double m_dDBoxLength;
    double MaxDouble;
    double m_dMultWallAvoidance;
    Path* m_pPath;
    std::vector<Wall2D> m_Feelers;
    SVector2D m_vWanderTarget;
    SVector2D m_vSteeringForce;

    mutable std::mt19937 m_RNG;
    mutable std::uniform_real_distribution<double> m_Distribution;

protected:
    SteeringBehaviors(Vehicle* owner);
    SteeringBehaviors();


    // Main steering force calculation
    SVector2D Calculate();

    // Seek behavior
    SVector2D Seek(const SVector2D& Target);

    SVector2D Flee(const SVector2D& TargetPos);
    
    SVector2D Pursuit(const Vehicle* Evader);

    SVector2D Arrive(const SVector2D& TargetPos, EDeceleration Deceleration);

    double TurnaoundTime(const Vehicle* pAgent, SVector2D TargetPos);

    SVector2D Evade(const Vehicle* pursuer);

    SVector2D Wander();

    double RandomClamped() const
    {
        return m_Distribution(m_RNG);
    }

    SVector2D PointToWorldSpace(SVector2D targetLocal, SVector2D VehicleHeading, SVector2D VehicleSide, SVector2D VehiclePos);

    SVector2D ObstacleAvoidance(const std::vector<BaseGameEntity*>& obstacles);

    SVector2D VectorToWorldSpace(SVector2D SterringForce, SVector2D Heading, SVector2D Side);

    SVector2D WallAvoidance(const std::vector<Wall2D>& walls);

    SVector2D Interpose(const Vehicle* AgentA, const Vehicle* AgentB);

    SVector2D GetHidingPosition(const SVector2D& posOb, const double radiusOb, const SVector2D& posTarget);

    SVector2D Hide(const Vehicle* target, vector<BaseGameEntity*>& obstacles);

    SVector2D FollowPath();

    SVector2D OffsetPursuit(const Vehicle* leader, const SVector2D offset);

    SVector2D Separation(const std::vector<Vehicle*>& neighbors);

    SVector2D Alignment(const std::vector<Vehicle*>& neighbors);

    SVector2D Cohesion(const std::vector<Vehicle*>& neighbors);

    SVector2D Calculate();

    bool AccumulateForce(SVector2D& RunningTot, SVector2D ForceToAdd);
};
