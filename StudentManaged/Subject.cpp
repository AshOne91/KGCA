#include "Subject.h"
#include "Packet.h"

Subject::Subject()
{

}

Subject::~Subject()
{

}

void Subject::SetType(ESubjectType type)
{
	_type = type;
}

ESubjectType Subject::GetType() const
{
	return _type;
}

void Subject::SetScore(short score)
{
	_score = score;
}

short Subject::GetScore() const
{
	return _score;
}

void Subject::Serialize(Packet* packet)
{
	packet->Write((int)_type);
	packet->Write(_score);
}
void Subject::Deserialize(Packet* packet)
{
	int* type = reinterpret_cast<int*>(&_type);
	packet->Read(type);
	packet->Read(&_score);
}
