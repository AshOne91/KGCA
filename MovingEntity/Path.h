#pragma once
#include <list>
#include "Vector.h"

class Path
{
private:
	std::list<Vector2D> _WayPointList;
	std::list<Vector2D>::iterator _curWayPoint;
	bool _bLooped;

public:
	Path() :_bLooped(false) {}
	Path(int NumWaypoints,
		float MinX,
		float MinY,
		float MaxX,
		float MaxY,
		bool looped) :_bLooped(looped)
	{
		CreateRandomPath(NumWaypoints, MinX, MinY, MaxX, MaxY);

		_curWayPoint = _WayPointList.begin();
	}

	Vector2D CurrentWaypoint() const { return *_curWayPoint; }

	bool Finished() { return !(_curWayPoint != _WayPointList.end()); }

	inline void SetNextWaypoint();

	std::list<Vector2D> CreateRandomPath(int NumWaypoints,
										float MinX,
										float MinY,
										float MaxX,
										float MaxY);

	void LoopOn() { _bLooped = true; }
	void LoopOff() { _bLooped = false; }

	void AddWayPoint(Vector2D new_point);

	void Set(std::list<Vector2D> new_path) { _WayPointList = new_path; _curWayPoint = _WayPointList.begin(); }
	void Set(const Path& path) { _WayPointList = path.GetPath(); _curWayPoint = _WayPointList.begin(); }

	void Clear() { _WayPointList.clear(); }
	std::list<Vector2D> GetPath() const { return _WayPointList; }

	void Render() const;
};
