#pragma once

#include "StateMachine.h"
#include <vector>
#include "Vector2D.h"

class PlayerBase;

class SoccerTeam
{
public:
	SoccerTeam();

	void Update();
	void Render();
	
public:
	bool CanShoot(Vector2D from, Vector2D to, Vector2D heading, double power);
	bool CanShoot(Vector2D from, double power);
	void RequestPass(PlayerBase* player);
	Vector2D GetSupportSpot();
	void InControl();
	PlayerBase* Receiver();
	void SetReceiver(PlayerBase* Receiver);
	PlayerBase* SupportingPlayer();
	void SetSupportingPlayer(PlayerBase* SupportingPlayer);
	PlayerBase* ControllingPlayer();
	void SetControllingPlayer(PlayerBase* ControllingPlayer);
	PlayerBase* PlayerClosestToBall();
	void SetPlayerClosestBall(PlayerBase* PlayerClosestToBall);
	bool isPassSafeFromAllOpponents(Vector2D PlayerPos, Vector2D Pos, PlayerBase* Player, double MaxPassingForcew);
	void ReturnAllFieldPlayersToHome();
	bool AllPlayersAtHome() const;
	SoccerTeam* Opponents() const;
	SoccerTeam* Opponents() const { return m_pOpponents; }
	void SetOpponents(SoccerTeam* opponents) { m_pOpponents = opponents; }
	StateMachine<SoccerTeam*>* GetFSM()
	{
		return &m_pStateMachine;
	}

private:
	std::vector<PlayerBase*> m_pPlayers;
	StateMachine<SoccerTeam*> m_pStateMachine;


	SoccerTeam* m_pOpponents;

	PlayerBase* m_pReceivingPlayer;
	PlayerBase* m_pPlayerClosestToBall;
	PlayerBase* m_pControllingPlayer;
	PlayerBase* m_pSupportingPlayer;
};
