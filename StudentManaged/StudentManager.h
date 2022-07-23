#pragma once
#include <string>
#include "AppSubSystem.h"
#include "PacketAssist.h"
#include "LinkedList.h"

class Student;
class Packet;
class Subject;
class StudentManager : public AppSubSystem<StudentManager>, public PacketAssist
{
public:
	static unsigned __int64 _AllocIndex;
	LinkedList<Student*> _listStudent;

public:
	StudentManager();
	virtual ~StudentManager();

private:
	unsigned __int64 AllocIndex();

public:
	void CreateStudent(std::string name, LinkedList<Subject*>& subjectList);

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
