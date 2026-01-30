#include "SoccerTeam.h"
#include "PlayerBase.h"

SoccerTeam::SoccerTeam()
	: m_pStateMachine(this),
	m_pReceivingPlayer(nullptr),
	m_pPlayerClosestToBall(nullptr),
	m_pControllingPlayer(nullptr),
	m_pSupportingPlayer(nullptr)
{
}

void SoccerTeam::Update()
{
	m_pStateMachine.Update();
}

bool SoccerTeam::CanShoot(Vector2D from, Vector2D to, Vector2D heading, double power)
{
	return false;
}

bool SoccerTeam::CanShoot(Vector2D from, double power)
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

bool SoccerTeam::isPassSafeFromAllOpponents(Vector2D PlayerPos, Vector2D Pos, PlayerBase* Player, double MaxPassingForcew)
{
	return false;
}

void SoccerTeam::ReturnAllFieldPlayersToHome()
{
}

bool SoccerTeam::AllPlayersAtHome() const
{
	for (auto player : m_pPlayers)
	{
		if (!player->AtHomeRegion())
		{
			return false;
		}
	}
	return true;
}
