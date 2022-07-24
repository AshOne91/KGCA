#pragma once
#include <string>
#include "Serialization.h"
#include "LinkedList.h"
#include "enum.h"

class Subject;
class Student sealed : public SerializableInterface 
{
private:
	unsigned __int64 _index;
	LinkedList<Subject*> _subjects;
	std::string _name;

public:
	Student();
	~Student();

public:
	unsigned __int64 GetIndex();
	short GetSubjectScore(ESubjectType type);
	short GetTotalScore();
	std::string GetName();

public:
	void SetIndex(unsigned __int64 index);
	void AddSubject(Subject* pSubject);
	void SetName(std::string& name);

public:
	virtual void Serialize(Packet* packet);
	virtual void Deserialize(Packet* packet);
};