#include "SupportSpotCalculator.h"
#include "SupportSpot.h"
#include "PlayerBase.h"
#include "Regulator.h"
#include "Params.h"
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
		if (m_pTeam->isPassSafeFromAllOpponents(m_pTeam->ControllingPlayer()->Pos(), curSpot->Pos(),  NULL, Prm.MaxPassingForce))
		{
			double newScore = curSpot->GetScore();
			newScore += Prm.Spot_PassSafeStrength;
			curSpot->SetScore(newScore);
		}
		//Test 2. Determine if a  goal can be scored from this position.
		if (m_pTeam->CanShoot(curSpot->Pos(), Prm.MaxShootingForce))
		{
			double newScore = curSpot->GetScore();
			newScore += Prm.Spot_CanScoreStrength;
			curSpot->SetScore(newScore);
		}
		//Test 3. calculate how far this spot is away from the controlling
		//player. The  farther away,  the higher the score. Any    distances farther
		//away than OptimalDistance pixels do not receive a score.
		if (m_pTeam->SupportingPlayer())
		{
			const double  OptimalDistance = 200.0;
			double dist = Vector2D::Distance(m_pTeam->ControllingPlayer()->Pos(), curSpot->Pos());
			double temp = fabs(OptimalDistance - dist);

			if (temp < OptimalDistance)
			{
				//normalize the distance and add it to the score
				double newScore  =  curSpot->GetScore();
				newScore += Prm.Spot_DistFromControllingPlayerStrength * (OptimalDistance - temp) / OptimalDistance;
				curSpot->SetScore(newScore);
			}
		}
		//check  to see  if this spot has  the highest score so far
		if (curSpot->GetScore() > BestScoreSoFar)
		{
			BestScoreSoFar = curSpot->GetScore();

			m_pBestSupportingSpot = &(*curSpot);
		}
	}

    return Vector2D();
}
