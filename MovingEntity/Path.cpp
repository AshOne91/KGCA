#include "Path.h"
#include "Utils.h"
#include "Transformations.h"

void Path::SetNextWaypoint()
{
	if (++_curWayPoint == _WayPointList.end())
	{
		if (_bLooped)
		{
			_curWayPoint = _WayPointList.begin();
		}
	}
}

std::list<Vector2D> Path::CreateRandomPath(int NumWaypoints,
	float MinX,
	float MinY,
	float MaxX,
	float MaxY)
{
	_WayPointList.clear();

	float midX = (MaxX + MinX) / 2.0f;
	float midY = (MaxY + MinY) / 2.0f;

	float smaller = min(midX, midY);

	float spacing = KSHCore::UTIL::TwoPi / (float)NumWaypoints;

	for (int i = 0; i < NumWaypoints; ++i)
	{
		float RadialDist = KSHCore::UTIL::RandInRange(smaller * 0.2f, smaller);

		Vector2D temp(RadialDist, 0.0f);

		Vec2DRotateAroundOrigin(temp, i * spacing);

		temp.x += midX; temp.y += midY;

		_WayPointList.push_back(temp);

	}

	_curWayPoint = _WayPointList.begin();

	return _WayPointList;
}

void Path::AddWayPoint(Vector2D new_point)
{

}

void Path::Render() const
{
	/*gdi->OrangePen();

	std::list<Vector2D>::const_iterator it = m_WayPoints.begin();

	Vector2D wp = *it++;

	while (it != m_WayPoints.end())
	{
		gdi->Line(wp, *it);

		wp = *it++;
	}

	if (m_bLooped) gdi->Line(*(--it), *m_WayPoints.begin());*/
}