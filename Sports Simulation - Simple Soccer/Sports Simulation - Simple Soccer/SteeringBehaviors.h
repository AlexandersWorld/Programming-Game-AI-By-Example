#pragma once
#include "Vector2D.h"

class SoccerBall;
class SoccerPitch;
class PlayerBase;

class SteeringBehaviors
{
public:

protected:
	Vector2D Calculate();
	void ArriveOn();
	void ArriveOff();
	void SeekOn();
	void SeekOff();
	void SeparationOn();
	void SeparationOff();
	void InterPoseOn();
	void InterPoseOff();
	void PursuitOn();
	void PursuitOff();

private:
	SoccerBall* m_pBall;
	SoccerPitch* m_pPitch;
	PlayerBase* m_pPlayer;
};