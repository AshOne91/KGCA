#include <filesystem>
#include "StudentManager.h"
#include "Packet.h"
#include "Student.h"
#include "Subject.h"

unsigned __int64 StudentManager::_AllocIndex = 0;

StudentManager::StudentManager()
{
	
}

StudentManager::~StudentManager()
{
	for (auto iter = _listStudent.begin(); iter != _listStudent.end(); ++iter)
	{
		delete (*iter);
	}
	_listStudent.clear();
}

void StudentManager::DoUpdate()
{

}

void StudentManager::OnEnable()
{
	AppSubSystem::OnEnable();
}

void StudentManager::OnDisable()
{
	AppSubSystem::OnDisable();
}

void StudentManager::Construct()
{
	AppSubSystem::Construct();

	std::string filePath = std::filesystem::current_path().string();
	filePath += "\\Record.bin";
	PacketAssist::OnInit(filePath);
	PacketAssist::Deserialize();
}

void StudentManager::Destruct()
{
	PacketAssist::Serialize();
	AppSubSystem::Destruct();
}

unsigned __int64 StudentManager::AllocIndex()
{
	return _AllocIndex++;
}

void StudentManager::CreateStudent(std::string name, LinkedList<Subject*>& subjectList)
{
	Student* pStudent = new Student();
	pStudent->SetIndex(AllocIndex());
	pStudent->SetName(name);
	for (auto iter = subjectList.begin(); iter != subjectList.end(); ++iter)
	{
		pStudent->AddSubject((*iter));
	}
	_listStudent.push_back(pStudent);
}

void StudentManager::Serialize(Packet* packet)
{
	packet->Write(_AllocIndex);
	int size = _listStudent.size();
	packet->Write(size);
	if (size > 0)
	{
		for (auto iter = _listStudent.begin(); iter != _listStudent.end(); ++iter)
		{
			(*iter)->Serialize(packet);
		}
	}
}

void StudentManager::Deserialize(Packet* packet)
{
	packet->Read(&_AllocIndex);
	int size = 0;
	packet->Read(&size);
	if (size > 0)
	{
		for (int i = 0; i < size; ++i)
		{
			Student* pStudent = new Student();
			pStudent->Deserialize(packet);
			_listStudent.push_back(pStudent);
		}
	}
}

bool StudentManager::OnMessage(BaseObject* sender, const std::string& message)
{
	return false;
}