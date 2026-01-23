#pragma once
#include "Vector2D.h"
#include "MovingEntity.h"

class SteeringBehaviors;
class SoccerTeam;

class PlayerBase : public MovingEntity
{
public:
	PlayerBase();

protected:
	bool CanPassForward(Vector2D receiver, Vector2D target, float power);
	bool CanPassBackward(Vector2D receiver, Vector2D target, float power);
	bool IsThreatened();
	bool BallWithingPlayerRange();
	bool BallWithinKickingRange();
	bool BallWithinReceivingRange();
	bool InHomeRegion();
	bool IsWithinSupportSpotRange();
	bool IsWithinTargetRange();
	bool IsClosestTeamMemberToBall();
	bool IsClosestPlayerOnPitchToBall();
	bool AtTarget();
	bool IsControllingPlayer();
	bool WhithinShootingRange();
	bool AtTarget();

private:
	SteeringBehaviors* m_pSteering;
	SoccerTeam* m_pTeam;
	int m_iHomeRegion;
};