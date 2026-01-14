#pragma once
#include "Vector2D.h"
#include "MovingEntity.h"

class PlayerBase : public MovingEntity
{
public:
	PlayerBase();

protected:
	bool CanPassForward(Vector2D receiver, Vector2D target, float power);
	bool CanPassBackward(Vector2D receiver, Vector2D target, float power);
	bool WhithinShootingRange();
	bool AtTarget();
};