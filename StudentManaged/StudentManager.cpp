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
	Clear();
	AppSubSystem::Destruct();
}

unsigned __int64 StudentManager::AllocIndex()
{
	return _AllocIndex++;
}

void StudentManager::CreateDummy()
{
	srand(time(0));
	for (int i = 0; i < 10; ++i)
	{
		std::string name;
		name += 65 + rand() % 26;
		name += 65 + rand() % 26;
		name += 65 + rand() % 26;

		LinkedList<Subject*> subjectList;
		Subject* pSubject = new Subject();
		pSubject->SetType(ESubjectType::Korean);
		pSubject->SetScore(rand() % 101);
		subjectList.push_back(pSubject);
		pSubject = new Subject();
		pSubject->SetType(ESubjectType::English);
		pSubject->SetScore(rand() % 101);
		subjectList.push_back(pSubject);
		pSubject = new Subject();
		pSubject->SetType(ESubjectType::Math);
		pSubject->SetScore(rand() % 101);
		subjectList.push_back(pSubject);
		CreateStudent(name, subjectList);
	}
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

bool StudentManager::DeleteStudnet(unsigned __int64 no)
{
	bool find = false;
	for (auto iter = _listStudent.begin(); iter != _listStudent.end(); ++iter)
	{
		if ((*iter)->GetIndex() == no)
		{
			_listStudent.erase(iter);
			find = true;
			break;
		}
	}
	return find;
}

void StudentManager::FindStudnet(std::string& name, LinkedList<unsigned __int64>& listno)
{
	bool find = false;
	for (auto iter = _listStudent.begin(); iter != _listStudent.end(); ++iter)
	{
		if ((*iter)->GetName() == name)
		{
			listno.push_back((*iter)->GetIndex());
		}
	}
}

void StudentManager::SortStudent(bool totalAscending, LinkedList<unsigned __int64>& listno)
{
	LinkedList<Student*> tempList;
	bool isFirst = true;
	if (totalAscending == true)
	{
		while (_listStudent.size() > 0)
		{
			short min = SHRT_MAX;
			Iterator<Student*> minIter;
			auto iter = _listStudent.begin();
			for (; iter != _listStudent.end(); ++iter)
			{
				if (isFirst)
				{
					tempList.push_back(*iter);
				}
				if (min > (*iter)->GetTotalScore())
				{
					minIter = iter;
					min = (*iter)->GetTotalScore();
				}
			}
			listno.push_back((*minIter)->GetIndex());
			_listStudent.erase(minIter);
			isFirst = false;
		}
	}
	else
	{
		while (_listStudent.size() > 0)
		{
			short max = SHRT_MIN;
			Iterator<Student*> maxIter = nullptr;
			auto iter = _listStudent.begin();
			for (; iter != _listStudent.end(); ++iter)
			{
				if (isFirst)
				{
					tempList.push_back(*iter);
				}
				if (max < (*iter)->GetTotalScore())
				{
					maxIter = iter;
					max = (*iter)->GetTotalScore();
				}
			}
			listno.push_back((*maxIter)->GetIndex());
			_listStudent.erase(maxIter);
			isFirst = false;
		}
	}
	_listStudent.clear();
	//노드를 다 삭제하였기에 다시 로드해준다.
	for (auto iter = tempList.begin(); iter != tempList.end(); ++iter)
	{
		_listStudent.push_back(*iter);
	}
}

void StudentManager::Clear()
{
	for (auto iter = _listStudent.begin(); iter != _listStudent.end(); ++iter)
	{
		delete (*iter);
	}
	_listStudent.clear();
}

void StudentManager::GetIndexList(LinkedList<unsigned __int64>& studentIndexList)
{
	for (auto iter = _listStudent.begin(); iter != _listStudent.end(); ++iter)
	{
		studentIndexList.push_back((*iter)->GetIndex());
	}
}

std::string StudentManager::GetName(unsigned __int64 no)
{
	for (auto iter = _listStudent.begin(); iter != _listStudent.end(); ++iter)
	{
		if ((*iter)->GetIndex() == no)
		{
			return (*iter)->GetName();
		}
	}
}

short StudentManager::GetSubjectScore(unsigned __int64 no, ESubjectType type)
{
	for (auto iter = _listStudent.begin(); iter != _listStudent.end(); ++iter)
	{
		if ((*iter)->GetIndex() == no)
		{
			return (*iter)->GetSubjectScore(type);
		}
	}
}

int StudentManager::GetTotalScore(unsigned __int64 no, LinkedList<ESubjectType>& subjects)
{
	int totalScore = 0;
	for (auto iter = subjects.begin(); iter != subjects.end(); ++iter)
	{
		ESubjectType type = (*iter);
		totalScore += GetSubjectScore(no, type);
	}

	return totalScore;
}

float StudentManager::GetAverage(unsigned __int64 no, LinkedList<ESubjectType>& subjects)
{
	float totalScore = (float)GetTotalScore(no, subjects);
	return ((totalScore != 0.0f) ? (totalScore / (float)subjects.size()) : 0.0f);
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