#pragma once

class SoccerBall;

class Goal
{

private:
	Vector2D m_vLeftPost;
	Vector2D m_vRightPost;

	//a vector representing the facing direction of the goal
	Vector2D m_vFacing;

	//the position of the center of the goal
	Vector2D m_vCenter;

	//each time Scored() detects a goal this is incremented
	int m_iNumGoalsScored;
public:
	Goal(Vector2D left, Vector2D right) :
		m_vLeftPost(left),
		m_vRightPost(right),
		m_vCenter((left + right) / 2.0),
		m_iNumGoalsScored(0)
	{
		m_vFacing = Vector2D(right - left).Normalize().Perp();
	}
	//Given the current ball position and the previous ball position,
	//this method returns true if the ball has crossed the goal line
	//and increments m_iNumGoalsScored
	inline bool Scored(SoccerBall* const ball);
};