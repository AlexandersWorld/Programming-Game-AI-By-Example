#pragma once
#include "Vector2D.h"

class SupportSpot
{

public:
	Vector2D Pos() const { return m_vPos; }
	void SetScore(double indScore) { m_dScore = indScore; }

private:
	Vector2D m_vPos;
	double m_dScore;

public:

	SupportSpot(Vector2D pos, double val) : m_vPos(pos), m_dScore(val) {}
};
