#include <list>
#include <cassert>

class SVector2D;

class Path
{
private:
	std::list<SVector2D> m_WayPoints;
	std::list<SVector2D> curWaypoint;

	bool m_bLooped;

public:
	Path() :m_bLooped(false), curWaypoint(NULL) {}


	SVector2D CurrentWaypoint() const { assert(curWaypoint != NULL); return *curWaypoint; }
};


inline void Path::SetNextWaypoint()
{
	assert(m_WayPoints.size() > 0);

	if (++curWaypoint == m_WayPoints.end())
	{
		if (m_bLooped)
		{
			curWaypoint = m_WayPoints.begin();
		}
	}
}