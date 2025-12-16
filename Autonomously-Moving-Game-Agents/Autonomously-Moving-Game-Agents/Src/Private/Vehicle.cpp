#include "Vehicle.h"
#include "SVector2D.h"
#include "GameWorld.h"
#include "SteeringBehaviors.h"

Vehicle::Vehicle()
{

}

void Vehicle::Update(double time_elapsed)
{
	SVector2D StreeringForce = m_pSteering->Calculate();
	SVector2D Acceleration = StreeringForce / m_dMass;

	m_vVelocity += Acceleration * time_elapsed;

	m_vVelocity.Truncate(m_dMaxSpeed);

	m_vPos += m_vVelocity * time_elapsed;

	if (m_vVelocity.LengthSq() > 0.000001)
	{
		m_vHeading = Vec2DNormalize(m_vVelocity);

		m_vSide = m_vHeading.Perp();
	}

	WrapAround(m_vPos, m_pWorld->cxClient(), m_pWorld->cyClient());
}