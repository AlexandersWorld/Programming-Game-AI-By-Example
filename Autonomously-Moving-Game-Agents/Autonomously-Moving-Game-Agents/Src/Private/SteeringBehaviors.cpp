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
    SVector2D desired = target - m_pVehicle->m_vPos();
    desired.Normalize();
    desired *= m_pVehicle->MaxSpeed();

    // Steering force = desired - current velocity
    return desired - m_pVehicle->Velocity();
}

SVector2D SteeringBehaviors::Flee(const SVector2D& TargetPos)
{
    const double PanicDistanceSq = 100.0 * 100.0;

    if (Vec2DDistance(m_pVehicle->m_vPos(), TargetPos) > PanicDistanceSq)
    {
        return Vector2D(0, 0);
    }

    SVector2D DesiredVelocity = m_pVehicle->m_vPos() - TargetPos;
    DesiredVelocity.Normalize();
    DesiredVelocity += m_pVehicle->m_dMaxSpeed();

    return desired - m_pVehicle->Velocity();
}