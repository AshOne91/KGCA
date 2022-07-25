#pragma once
#include <string>
#include "AppSubSystem.h"
#include "PacketAssist.h"
#include "LinkedList.h"
#include "enum.h"

class Student;
class Packet;
class Subject;
class StudentManager : public AppSubSystem<StudentManager>, public PacketAssist
{
private:
	static unsigned __int64 _AllocIndex;
	LinkedList<Student*> _listStudent;

public:
	StudentManager();
	virtual ~StudentManager();

private:
	unsigned __int64 AllocIndex();

public:
	void CreateDummy();
	void CreateStudent(std::string name, LinkedList<Subject*>& subjectList);
	bool DeleteStudnet(unsigned __int64 no);
	void FindStudnet(std::string& name, LinkedList<unsigned __int64>& listno);
	void SortStudent(bool totalAscending, LinkedList<unsigned __int64>& listno);
	void Clear();

public:
	void GetIndexList(LinkedList<unsigned __int64>& studentIndexList);
	std::string GetName(unsigned __int64 no);
	short GetSubjectScore(unsigned __int64 no, ESubjectType type);
	int GetTotalScore(unsigned __int64 no, LinkedList<ESubjectType>& subjects);
	float GetAverage(unsigned __int64 no, LinkedList<ESubjectType>& subjects);

public:
	virtual void DoUpdate();

public:
	virtual void OnEnable();
	virtual void OnDisable();

public:
	virtual void Construct();
	virtual void Destruct();

public:
	virtual void Serialize(Packet* packet);
	virtual void Deserialize(Packet* packet);

public:
	virtual bool OnMessage(BaseObject* sender, const std::string& message);
};
