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
	
protected:
	bool CanShoot(Vector2D from, Vector2D to, Vector2D heading, double power);
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

private:
	std::vector<PlayerBase*> m_pPlayers;
	StateMachine<SoccerTeam*> m_pStateMachine;

	PlayerBase* m_pReceivingPlayer;
	PlayerBase* m_pPlayerClosestToBall;
	PlayerBase* m_pControllingPlayer;
	PlayerBase* m_pSupportingPlayer;
};
