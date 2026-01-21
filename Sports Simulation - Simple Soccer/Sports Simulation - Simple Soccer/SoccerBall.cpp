#include "SoccerBall.h"
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
	return 0.0;
}
