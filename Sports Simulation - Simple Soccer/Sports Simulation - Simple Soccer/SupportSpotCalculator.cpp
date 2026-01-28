#include "SupportSpotCalculator.h"
#include "SupportSpot.h"
#include "PlayerBase.h"
#include "SoccerTeam.h"

Vector2D SupportSpotCalculator::DetermineBestSupportingPostion()
{
	//only update the spots every few frames
	if (!m_pRegulator->AllowCodeFlow() && m_pBestSupportingSpot)
	{
		return m_pBestSupportingSpot->Pos();
	}

	//reset the best supporting spot
	m_pBestSupportingSpot = NULL;

	double BestScoreSoFar = 0.0;

	std::vector<SupportSpot>::iterator curSpot;

	for (curSpot = m_Spots.begin(); curSpot != m_Spots.end(); ++curSpot)
	{
		//first remove any previous score. (the score is set to one so that
		//the viewer can see the positions of all the spots if he has the
		//aids turned on)

		curSpot->SetScore(1.0);

		//Test 1. is it possible to make a safe pass from the ball's position
		//to this position?
		if (m_pTeam->isPassSafeFromAllOpponents(m_pTeam->ControllingPlayer()->Pos()))
		{

		}
	}

    return Vector2D();
}
