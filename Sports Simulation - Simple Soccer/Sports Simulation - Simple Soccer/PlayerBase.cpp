#include "PlayerBase.h"

PlayerBase::PlayerBase()
{
}

Vector2D PlayerBase::Pos()
{
	return m_vPos;
}

bool PlayerBase::CanPassForward(Vector2D receiver, Vector2D target, float power)
{
	return false;
}

bool PlayerBase::CanPassBackward(Vector2D receiver, Vector2D target, float power)
{
	return false;
}

bool PlayerBase::IsThreatened()
{
	return false;
}

bool PlayerBase::BallWithingPlayerRange()
{
	return false;
}

bool PlayerBase::BallWithinKickingRange()
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

bool PlayerBase::IsControllingPlayer()
{
	return false;
}

bool PlayerBase::BallWithinReceivingRange()
{
	return false;
}

bool PlayerBase::InHomeRegion()
{
	return false;
}

bool PlayerBase::IsWithinSupportSpotRange()
{
	return false;
}

bool PlayerBase::IsWithinTargetRange()
{
	return false;
}

bool PlayerBase::IsClosestTeamMemberToBall()
{
	return false;
}

bool PlayerBase::IsClosestPlayerOnPitchToBall()
{
	return false;
}
