#pragma once

#include "Vector2D.h"

class SoccerBall
{
public:
	void Update();
	void Render();

protected:
	void Kick(Vector2D direction, double force);
	Vector2D FuturePosition(double time);
	void Trap();
	double TimeToCoverDistance(Vector2D A, Vector2D B, double force);
};