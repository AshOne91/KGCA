#pragma once
class Param
{
public:
	static Param* Instance();

	int	NumAgents;
	int	NumObstacles;
	float MinObstacleRadius;
	float MaxObstacleRadius;

	//number of horizontal cells used for spatial partitioning
	int   NumCellsX;
	//number of vertical cells used for spatial partitioning
	int   NumCellsY;

	//how many samples the smoother will use to average a value
	int   NumSamplesForSmoothing;

	//used to tweak the combined steering force (simply altering the MaxSteeringForce
	//will NOT work!This tweaker affects all the steering force multipliers
	//too).
	float SteeringForceTweaker;

	float MaxSteeringForce;
	float MaxSpeed;
	float VehicleMass;

	float VehicleScale;
	float MaxTurnRatePerSecond;

	float SeparationWeight;
	float AlignmentWeight;
	float CohesionWeight;
	float ObstacleAvoidanceWeight;
	float WallAvoidanceWeight;
	float WanderWeight;
	float SeekWeight;
	float FleeWeight;
	float ArriveWeight;
	float PursuitWeight;
	float OffsetPursuitWeight;
	float InterposeWeight;
	float HideWeight;
	float EvadeWeight;
	float FollowPathWeight;

	//how close a neighbour must be before an agent perceives it (considers it
	//to be within its neighborhood)
	float ViewDistance;

	//used in obstacle avoidance
	float MinDetectionBoxLength;

	//used in wall avoidance
	float WallDetectionFeelerLength;

	//these are the probabilities that a steering behavior will be used
	//when the prioritized dither calculate method is used
	float prWallAvoidance;
	float prObstacleAvoidance;
	float prSeparation;
	float prAlignment;
	float prCohesion;
	float prWander;
	float prSeek;
	float prFlee;
	float prEvade;
	float prHide;
	float prArrive;
};

#define Prm (*Param::Instance())