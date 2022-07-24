#pragma once
#include <iostream>
#include "Serialization.h"
#include "enum.h"

class Subject sealed: public SerializableInterface
{
private:
	ESubjectType _type;
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
