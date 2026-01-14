#include "PlayerBase.h"

PlayerBase::PlayerBase()
{
}

bool PlayerBase::CanPassForward(Vector2D receiver, Vector2D target, float power)
{
	return false;
}

bool PlayerBase::CanPassBackward(Vector2D receiver, Vector2D target, float power)
{
	return false;
}

bool PlayerBase::WhithinShootingRange()
{
	return false;
}

bool PlayerBase::AtTarget()
{
	return false;
}
