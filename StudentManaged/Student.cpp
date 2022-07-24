#include "Student.h"
#include "Subject.h"
#include "Packet.h"
#include "enum.h"

Student::Student()
{

}

Student::~Student()
{
	for (auto iter = _subjects.begin(); iter != _subjects.end(); ++iter)
	{
		delete (*iter);
	}
	_subjects.clear();
}

unsigned __int64 Student::GetIndex()
{
	return _index;
}

short Student::GetSubjectScore(ESubjectType type)
{
	for (auto iter = _subjects.begin(); iter != _subjects.end(); ++iter)
	{
		if ((*iter)->GetType() == type)
		{
			return (*iter)->GetScore();
		}
	}
	return 0;
}

short Student::GetTotalScore()
{
	short totalScore = 0;
	for (auto iter = _subjects.begin(); iter != _subjects.end(); ++iter)
	{
		totalScore += (*iter)->GetScore();
	}
	return totalScore;
}

std::string Student::GetName()
{
	return _name;
}

void Student::SetIndex(unsigned __int64 index)
{
	_index = index;
}

void Student::AddSubject(Subject* pSubject)
{
	_subjects.push_back(pSubject);
}

void Student::SetName(std::string& name)
{
	_name = name;
}

void Student::Serialize(Packet* packet)
{
	packet->Write(_index);
	packet->Write(_name);
	int size = _subjects.size();
	packet->Write(size);
	if (size > 0)
	{
		for (auto iter = _subjects.begin(); iter != _subjects.end(); ++iter)
		{
			(*iter)->Serialize(packet);
		}
	}

}

void Student::Deserialize(Packet* packet)
{
	packet->Read(&_index);
	packet->Read(&_name);
	int size = -1;
	packet->Read(&size);
	if (size > 0)
	{
		for (int i = 0; i < size; ++i)
		{
			Subject* pSubject = new Subject();
			pSubject->Deserialize(packet);
			_subjects.push_back(pSubject);
		}
	}
}