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
	return m_pReceivingPlayer;
}

void SoccerTeam::SetReceiver(PlayerBase* Receiver)
{
	m_pReceivingPlayer = Receiver;
}

PlayerBase* SoccerTeam::SupportingPlayer()
{
	return m_pSupportingPlayer;
}

void SoccerTeam::SetSupportingPlayer(PlayerBase* SupportingPlayer)
{
	m_pSupportingPlayer = SupportingPlayer;
}

PlayerBase* SoccerTeam::ControllingPlayer()
{
	return m_pControllingPlayer;
}

void SoccerTeam::SetControllingPlayer(PlayerBase* ControllingPlayer)
{
	m_pControllingPlayer = ControllingPlayer;
}

PlayerBase* SoccerTeam::PlayerClosestToBall()
{
	return m_pPlayerClosestToBall;
}

void SoccerTeam::SetPlayerClosestBall(PlayerBase* PlayerClosestToBall)
{
	m_pPlayerClosestToBall = PlayerClosestToBall;
}
