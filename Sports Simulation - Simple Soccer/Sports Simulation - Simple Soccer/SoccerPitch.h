#pragma once
#include "SoccerTeam.h"
#include "Goal.h"
#include "SoccerBall.h"
#include "Wall2D.h"
#include "Region.h"

class SoccerPitch
{

public:
	SoccerPitch(int cxClient, int cyClient);

	~SoccerPitch();

	void Update();
	void Render();

private:
	SoccerTeam* m_pBlueTeam;
	SoccerTeam* m_pRedTeam;
	SoccerBall* m_pSoccerBall;
	Goal* m_pRedGoal;
	Goal* m_pBlueGoal;

	std::vector<Wall2D> m_vecWallks;
	std::vector<Region*> m_Regions;

	bool m_bGameOn;
	bool m_bGoalKeeperHasBall;

	int m_cxClient;
	int m_cyClient;

};