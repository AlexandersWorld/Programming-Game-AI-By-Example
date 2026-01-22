#pragma once

#include <vector>
#include "MovingEntity.h"

class PlayerBase;
class Wall2D;
class Telegram;
class Vector2D;

class SoccerBall : public MovingEntity
{
private:
	//keeps a record of the ball's position at the last update
	Vector2D m_vOldPos;

	//a pointer to the player (or goalkeeper) who possesses the ball
	PlayerBase* m_pOwner;

	double m_dMass = 10.f;

	Vector2D m_vVelocity;

	//a local reference to the walls that make up the pitch boundary
	//(used in the collision detection)
	const std::vector<Wall2D>& m_PitchBoundary;

	//tests to see if the ball has collided with a wall and reflects
	//the ball's velocity accordingly
	void TestCollisionWithWalls(const std::vector<Wall2D>& walls);
public:

	SoccerBall(Vector2D pos, double Ballsize, double mass, std::vector<Wall2D>& PitchBoundary)
		: MovingEntity(pos, Ballsize, Vector2D(0, 0), -1.0, Vector2D(0, 1), mass, Vector2D(1.0, 1.0), 0, 0), m_PitchBoundary(PitchBoundary), m_pOwner(nullptr) {}

	//implement base class Update
	void Update(double time_elapsed);
	//implement base class Render
	void Render();
	//a soccer ball doesn't need to handle messages
	bool HandleMessage(const Telegram& msg) { return false; }
	//this method applies a directional force to the ball (kicks it!)
	void Kick(Vector2D direction, double force);
	//given a kicking force and a distance to traverse defined by start
	//and finish points, this method calculates how long it will take the
	//ball to cover the distancece.
	double TimeToCoverDistance(Vector2D from, Vector2D to, double force) const;
	//this method calculates where the ball will be at a given time
	Vector2D FuturePosition(double time) const;
	//this is used by players and goalkeepers to 'trap' a ball -- to stop
	//it dead. The  trapping player is then assumed to be in possession of
	//the ball and m_pOwner is adjusted accordingly
	void Trap(PlayerBase* owner) { m_vVelocity.Zero(); m_pOwner = owner; }

	Vector2D OldPos() const { return m_vOldPos; }
	//this places the ball at the desired location and sets its velocity to zero
	void PlaceAtPosition(Vector2D NewPos);

protected:
	void Kick(Vector2D direction, double force);
	Vector2D FuturePosition(double time);
	void Trap();
	Vector2D Pos() const;
	double TimeToCoverDistance(Vector2D A, Vector2D B, double force);
};
