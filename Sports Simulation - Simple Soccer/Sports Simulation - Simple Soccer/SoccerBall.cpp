#include "SoccerBall.h"
#include "Vector2D.h"
#include "Params.h"

void SoccerBall::TestCollisionWithWalls(const std::vector<Wall2D>& walls)
{
}

void SoccerBall::Update(double time_elapsed)
{
}

void SoccerBall::PlaceAtPosition(Vector2D NewPos)
{
}

void SoccerBall::Kick(Vector2D direction, double force)
{
}

double SoccerBall::TimeToCoverDistance(Vector2D from, Vector2D to, double force) const
{
	return 0.0;
}

Vector2D SoccerBall::FuturePosition(double time) const
{
	//using the equation x = ut + 1/2at^2, where x = distance, a = friction
	//u = start velocity

	//calculate the ut term, which is a vector
	Vector2D ut = m_vVelocity * time;
	
	//calculate the 1/2at^2 term, wich is scalar
	double half_a_t_squared = 0.5 * Prm.Friction * time * time;

	//turn the scalar quantity into a vector by multiplying the value with
	//the normalized velocity vector (because that gives the direction)
	Vector2D ScalarToVector = m_vVelocity.Normalize() * half_a_t_squared;

	//the predicted position is the ball's position plus these two terms
	return Pos() + ut + ScalarToVector;
}

Vector2D SoccerBall::FuturePosition(double time)
{
	return Vector2D();
}

void SoccerBall::Trap()
{
}

Vector2D SoccerBall::Pos() const
{
	return m_vOldPos;
}

double SoccerBall::TimeToCoverDistance(Vector2D A, Vector2D B, double force)
{
	//this will be the velocity of the ball in the bext time step *if*
	//the player was to make the pass.
	double speed = force / m_dMass;

	//calculate the velocity at B using the equation
	// v^2 = u^2 + 2ax

	//first calculate s (the distance between the two positions)
	double DistanceToCover = Vector2D::Distance(A, B);

	double term = speed * speed + 2.0 * DistanceToCover * Prm.Friction;

	//if (u^2 + 2ax) is negative it means the ball cannot reach point B.
	if (term <= 0) return 1.0f;

	double v = sqrt(term);

	//it's possible for the ball to reach B and we know its speed when it
	//gets there, so now it's easy to calculate the time using the equation

	//t = v - u / a
	return (v - speed) / Prm.Friction;
}
