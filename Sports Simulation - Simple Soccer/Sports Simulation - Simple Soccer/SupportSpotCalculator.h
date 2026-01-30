#pragma once
#include "Vector2D.h"
#include <vector>

class SupportSpot;
class SoccerTeam;
class  Regulator;

class SupportSpotCalculator
{
public:
	Vector2D DetermineBestSupportingPostion();

protected:


private:
	SupportSpot* m_pBestSupportingSpot;

	std::vector<SupportSpot> m_Spots;

	SoccerTeam* m_pTeam;

	Regulator* m_pRegulator;

};