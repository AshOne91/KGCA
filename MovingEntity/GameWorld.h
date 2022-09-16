#pragma once
#include "Std.h"
#include "Vehicle.h"
#include "Wall2D.h"
#include "CellSpacePartition.h"
#include "Path.h"

class GameWorld
{
private:
	std::vector<Vehicle*> _VehicleList;
	std::vector<BaseObject*> _ObstacleList;
	std::vector<Wall2D> _WallList;
	CellSpacePartition<Vehicle*>* _pCellSpace;
	Path* _pPath;
	bool _bPaused;
	int _cxClient;
	int _cyClient;
	Vector2D _vCrosshair;
	float _fAvFrameTime;

	bool  _bShowWalls;
	bool  _bShowObstacles;
	bool  _bShowPath;
	bool  _bShowDetectionBox;
	bool  _bShowWanderCircle;
	bool  _bShowFeelers;
	bool  _bShowSteeringForce;
	bool  _bShowFPS;
	bool  _bRenderNeighbors;
	bool  _bViewKeys;
	bool  _bShowCellSpaceInfo;

public:
	GameWorld(int cx, int cy);
	~GameWorld();

	void Update(float time_elapsed);
	void Render();
	void  NonPenetrationContraint(Vehicle* v) { EnforceNonPenetrationConstraint(v, _VehicleList); }
	void  TagVehiclesWithinViewRange(BaseObject* pVehicle, double range)
	{
		TagNeighbors(pVehicle, _VehicleList, range);
	}

	void  TagObstaclesWithinViewRange(BaseObject* pVehicle, double range)
	{
		TagNeighbors(pVehicle, _ObstacleList, range);
	}

	const std::vector<Wall2D>& Walls() { return _WallList; }
	CellSpacePartition<Vehicle*>* CellSpace() { return _pCellSpace; }
	const std::vector<BaseObject*>& Obstacles()const { return _ObstacleList; }
	const std::vector<Vehicle*>& Agents() { return _VehicleList; }

	void        HandleKeyPresses(WPARAM wParam);
	void        HandleMenuItems(WPARAM wParam, HWND hwnd);

	void        TogglePause() { m_bPaused = !m_bPaused; }
	bool        Paused()const { return m_bPaused; }

	Vector2D    Crosshair()const { return m_vCrosshair; }
	void        SetCrosshair(POINTS p);
	void        SetCrosshair(Vector2D v) { m_vCrosshair = v; }

	int   cxClient()const { return m_cxClient; }
	int   cyClient()const { return m_cyClient; }

	bool  RenderWalls()const { return m_bShowWalls; }
	bool  RenderObstacles()const { return m_bShowObstacles; }
	bool  RenderPath()const { return m_bShowPath; }
	bool  RenderDetectionBox()const { return m_bShowDetectionBox; }
	bool  RenderWanderCircle()const { return m_bShowWanderCircle; }
	bool  RenderFeelers()const { return m_bShowFeelers; }
	bool  RenderSteeringForce()const { return m_bShowSteeringForce; }

	bool  RenderFPS()const { return m_bShowFPS; }
	void  ToggleShowFPS() { m_bShowFPS = !m_bShowFPS; }

	void  ToggleRenderNeighbors() { m_bRenderNeighbors = !m_bRenderNeighbors; }
	bool  RenderNeighbors()const { return m_bRenderNeighbors; }

	void  ToggleViewKeys() { m_bViewKeys = !m_bViewKeys; }
	bool  ViewKeys()const { return m_bViewKeys; }
};