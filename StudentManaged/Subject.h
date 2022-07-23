#pragma once
#include <iostream>
#include "Serialization.h"

enum class ESubjectType : int
{
	None = 0,
	Korean = 1,
	English = 2,
	Math = 3,
	MAX = INT_MAX
};

class Subject sealed: public SerializableInterface
{
private:
	ESubjectType _type = ESubjectType::None;
	short _score = 0;

public:
	Subject();
	~Subject();

public:
	void SetType(ESubjectType type);
	ESubjectType GetType() const;

	void SetScore(short score);
	short GetScore() const;

public:
	virtual void Serialize(Packet* packet);
	virtual void Deserialize(Packet* packet);
};
