#include "SoccerPitch.h"

SoccerPitch::SoccerPitch(int cxClient, int cyClient)
	: m_pBlueTeam(nullptr),
	  m_pRedTeam(nullptr),
	  m_pSoccerBall(nullptr),
	  m_pRedGoal(nullptr),
	  m_pBlueGoal(nullptr),
	  m_bGameOn(false),
	  m_bGoalKeeperHasBall(false),
	m_cxClient(cxClient),
	m_cyClient(cyClient)
{
}

SoccerPitch::~SoccerPitch()
{
}

void SoccerPitch::Update()
{
}

void SoccerPitch::Render()
{
}



