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
	void SetReceiver();
	PlayerBase* SupportingPlayer();
	void SetSupportingPlayer();
	PlayerBase* ControllingPlayer();
	void SetControllingPlayer();
	PlayerBase* PlayerClosestToBall();
	void SetPlayerClosestBall();

private:
	std::vector<PlayerBase*> m_pPlayers;
	StateMachine<SoccerTeam*> m_pStateMachine;
};