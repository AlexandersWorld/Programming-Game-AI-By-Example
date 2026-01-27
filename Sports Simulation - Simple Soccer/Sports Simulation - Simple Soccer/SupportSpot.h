#pragma once
#include "Vector2D.h"

class SupportSpot
{

private:
	Vector2D m_vPos;
	double m_dScore;

public:

	SupportSpot(Vector2D pos, double val) : m_vPos(pos), m_dScore(val) {}
};
