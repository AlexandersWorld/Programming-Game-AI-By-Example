#include "SoccerTeam.h"

SoccerTeam::SoccerTeam()
{
}

bool SoccerTeam::CanShoot(Vector2D from, Vector2D to, Vector2D heading, double power)
{
	return false;
}

void SoccerTeam::RequestPass(PlayerBase* playerbase)
{
}

Vector2D SoccerTeam::GetSupportSpot()
{
	return Vector2D();
}

void SoccerTeam::InControl()
{
}

PlayerBase* SoccerTeam::Receiver()
{
	return nullptr;
}

void SoccerTeam::SetReceiver()
{
}

PlayerBase* SoccerTeam::SupportingPlayer()
{
	return nullptr;
}

void SoccerTeam::SetSupportingPlayer()
{
}

PlayerBase* SoccerTeam::ControllingPlayer()
{
	return nullptr;
}

void SoccerTeam::SetControllingPlayer()
{
}

PlayerBase* SoccerTeam::PlayerClosestToBall()
{
	return nullptr;
}

void SoccerTeam::SetPlayerClosestBall()
{
}
