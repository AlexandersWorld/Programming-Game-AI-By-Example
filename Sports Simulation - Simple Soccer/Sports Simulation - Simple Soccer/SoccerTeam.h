#pragma once

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

private:
	std::vector<PlayerBase*> m_pPlayers;
};