#pragma once
enum class SpacePartitionType : int
{
	QUADTREE,
	OCTREE,
	BSP
};

class Config
{
public:
	Config() {}
	~Config() {}

public:
	int _frame = 60;
	SpacePartitionType _partitionType = SpacePartitionType::QUADTREE;
};
