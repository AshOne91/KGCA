#pragma once
#include <vector>
#include <list>
#include "InvertedAABBox2D.h"

template <class entity>
struct Cell
{
	std::list<entity> Members;
	InvertedAABBox2D BBox;
	Cell(Vector2D topleft, Vector2D botright) : BBox(InvertedAABBox2D(topleft, botright)) {}

};

template <class entity>
class CellSpacePartition
{
private:
	std::vector<Cell<entity>> _Cells;

	std::vector<entity> _Neighbors;

	typename std::vector<entity>::iterator _curNeighbor;

	float _fSpaceWidth;
	float _fSpaceHeight;

	int _iNumCellsX;
	int _iNumCellsY;

	float _fCellSizeX;
	float _fCellSizeY;

	int PositionToIndex(const Vector2D& pos) const;

public:
	CellSpacePartition(double width,
		double height,
		int cellsX,
		int cellsY,
		int MaxEntitys);

	void AddEntity(const entity& ent);
	void UpdateEntity(const entity& ent, Vector2D oldPos);
	void CalculateNeighbors(Vector2D TargetPos, double QueryRadius);
	entity& begin() { _curNeighbor = _Neighbors.begin(); return *_curNeighbor; }
	entity& next() { ++_curNeighbor; return *_curNeighbor; }
	bool end() { return (_curNeighbor == _Neighbors.end()) || (*_curNeighbor == 0); }

	void EmptyCells();

	void RenderCells() const;
};

template<class entity>
inline int CellSpacePartition<entity>::PositionToIndex(const Vector2D& pos) const
{
	int idx = (int)(_iNumCellsX * pos.x / _fSpaceWidth) + ((int)((_iNumCellsY) * pos.y / _fSpaceHeight) * _iNumCellsX);

	if (idx > _Cells.size() - 1)
	{
		idx = _Cells.size() - 1;
	}
	return idx;
}

template<class entity>
inline CellSpacePartition<entity>::CellSpacePartition(double width, double height, int cellsX, int cellsY, int MaxEntitys):
	_fSpaceWidth(width),
	_fSpaceHeight(height),
	_iNumCellsX(cellsX),
	_iNumCellsY(cellsY),
	_Neighbors(MaxEntitys, entity())
{
	_fCellSizeX = width / cellsX;
	_fCellSizeY = height / cellsY;

	for (int y = 0; y < _iNumCellsY; ++y)
	{
		for (int x = 0; x < _iNumCellsX; ++x)
		{
			float left = x * _fCellSizeX;
			float right = left + _fCellSizeX;
			float top = y * _fCellSizeY;
			float bot = top + _fCellSizeY;

			_Cells.push_back(Cell<entity>(Vector2D(left, top), Vector2D(right, bot)));
		}
	}
}

template<class entity>
inline void CellSpacePartition<entity>::AddEntity(const entity& ent)
{
	int idx = PositionToIndex(ent->Pos());
	_Cells[idx].Members.push_back(ent);
}

template<class entity>
inline void CellSpacePartition<entity>::UpdateEntity(const entity& ent, Vector2D oldPos)
{
	int OldIdx = PositionToIndex(OldPos);
	int NewIdx = PositionToIndex(ent->Pos());

	if (NewIdx == OldIdx) return;

	_CellList[OldIdx].
}

template<class entity>
inline void CellSpacePartition<entity>::CalculateNeighbors(Vector2D TargetPos, double QueryRadius)
{
	std::vector<entity>::iterator curNbor = _Neighbors.begin();

	InvertedAABBox2D QueryBox(TargetPos - Vector2D(QueryRadius, QueryRadius),
		TargetPos + Vector2D(QueryRadius, QueryRadius));

	std::vector<Cell<entity> >::iterator curCell;
	for (curCell = _Cells.begin(); curCell != _Cells.end(); ++curCell)
	{
		//test to see if this cell contains members and if it overlaps the
		//query box
		if (curCell->BBox.isOverlappedWith(QueryBox) &&
			!curCell->Members.empty())
		{
			//add any entities found within query radius to the neighbor list
			std::list<entity>::iterator it = curCell->Members.begin();
			for (it; it != curCell->Members.end(); ++it)
			{
				if (Vec2DDistanceSq((*it)->Pos(), TargetPos) <
					QueryRadius * QueryRadius)
				{
					*curNbor++ = *it;
				}
			}
		}
	}//next cell

	//mark the end of the list with a zero.
	*curNbor = 0;
}

template<class entity>
inline void CellSpacePartition<entity>::EmptyCells()
{
	std::vector<Cell<entity> >::iterator it = _Cells.begin();

	for (it; it != _Cells.end(); ++it)
	{
		it->Members.clear();
	}
}

template<class entity>
inline void CellSpacePartition<entity>::RenderCells() const
{
	std::vector<Cell<entity> >::const_iterator curCell;
	for (curCell = _Cells.begin(); curCell != _Cells.end(); ++curCell)
	{
		curCell->BBox.Render(false);
	}
}
