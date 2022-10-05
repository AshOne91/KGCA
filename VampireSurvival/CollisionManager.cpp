#include "CollisionManager.h"
#include "ObjectManager.h"
#include "Message.h"
#include "Circle.h"
#include "Component.h"
#include "Collision.h"
#include "EventManager.h"
#include "GameWorld.h"

void CollisionManager::Set(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pImmediateContext)
{
	_pd3dDevice = pd3dDevice;
	_pImmediateContext = pImmediateContext;
}

bool CollisionManager::CInit()
{
	_fCollisionCheckRadious = float(dfSCREEN_WIDTH * dfSCREEN_WIDTH) + float(dfSCREEN_HEIGHT * dfSCREEN_HEIGHT);
	_fCollisionCheckRadious = sqrtf(_fCollisionCheckRadious) * 0.5f;
	_frameSkip.SetFramePerSec(5);
	return true;
}

bool CollisionManager::CFrame()
{
	if (_frameSkip.Update(g_fGameTimer) == false)
	{
		return true;
	}
	std::vector<std::pair<ComponentObject*, CircleComponent*>> tempList;
	for (auto& data : _circleComponentList)
	{
		for (auto& data2 : data.second)
		{
			auto pParent = data2.first;
			auto pCircle = data2.second;
			pCircle->_transform.SetPostion(pParent->_transform.GetPosition());
			Vector2D position = pCircle->_transform.GetPosition();
			pCircle->cx = position.x;
			pCircle->cy = position.y;
			Circle checkCircle;
			checkCircle.cx = I_GameWorld.GetCameraPos().x;
			checkCircle.cy = I_GameWorld.GetCameraPos().y;
			checkCircle.fRadius = _fCollisionCheckRadious;
			if (Collision::CircleToCircle(*pCircle, checkCircle))
			{
				tempList.push_back({ pParent, pCircle });
			}
		}
	}

	//FIXME : 레지드바디 중심으로 체크해야함(원래는)
	for (int i = 0; i < tempList.size(); ++i)
	{
		for (int j = 0; j < tempList.size(); ++j)
		{
			if (tempList[i].second == tempList[j].second)
			{
				continue;
			}

			//auto pCheck = _collisionCheckList.find(tempList[i].second);
			//if (pCheck != _collisionCheckList.end())
			//{
			//	auto isCollOnce = pCheck->second.find(tempList[j].second);
			//	if (isCollOnce != pCheck->second.end())
			//	{
			//		continue;
			//	}
			//}

			if (Collision::CircleToCircle(*tempList[i].second, *tempList[j].second))
			{
				Message message;
				message.eventType = EventType::CollisionIn;
				message._uiSender = GetIndex();
				message._uiReceiver = tempList[i].first->GetIndex();
				message._pExtraInfo = tempList[j].first;
				I_EventManager.PostNotifycation(message.eventType, NotifyType::Mono, this, &message);

				/*auto iter = _collisionCheckList.find(tempList[i].second);
				if (iter == _collisionCheckList.end())
				{
					_collisionCheckList.insert({ tempList[i].second, std::set<CircleComponent*>() });
					_collisionCheckList[tempList[i].second].insert(tempList[j].second);
				}
				else
				{
					_collisionCheckList[tempList[i].second].insert(tempList[j].second);
				}*/
			}
		}
	}

	//std::vector<std::pair<CircleComponent*, CircleComponent*>> _outList;
	// 밖으로 나간 것들 체크해줌
	/*for (auto& data1 : _collisionCheckList)
	{
		for (auto& data2 : data1.second)
		{
			if (Collision::CircleToCircle(*data1.first, *data2) == false)
			{
				_outList.push_back({ data1.first , data2 });
				Message message;
				message.eventType = EventType::CollisionOut;
				message._uiSender = GetIndex();
				message._uiReceiver = data1.first->GetParentPtr()->GetIndex();
				message._pExtraInfo = data2->GetParentPtr();
				I_EventManager.PostNotifycation(message.eventType, NotifyType::Mono, this, &message);
			}
		}
	}*/

	//인 체크 리스트에서 빼줌
	/*for (auto& pair : _outList)
	{
		auto& iter = _collisionCheckList[pair.first];
		iter.erase(pair.second);
		if (iter.size() <= 0)
		{
			_collisionCheckList.erase(pair.first);
		}
	}*/
	return true;
}

bool CollisionManager::CRender()
{
	return true;
}

bool CollisionManager::CRelease()
{
	_circleComponentList.clear();
	_collisionCheckList.clear();
	return true;
}

bool CollisionManager::OnEvent(EventType eventType, ComponentObject* pSender, Message* msg)
{
	if (eventType == EventType::CreateComponent)
	{
		ComponentObject* pExtraInfo = static_cast<ComponentObject*>(msg->_pExtraInfo);
		auto pData = dynamic_cast<CircleComponent*>(pExtraInfo);
		if (pData != nullptr)
		{
			ComponentObject* pParent = pData->GetParentPtr();
			auto iter = _circleComponentList.find(pParent->GetIndex());
			if (iter == _circleComponentList.end())
			{
				_circleComponentList.insert({ pParent->GetIndex() , std::unordered_map<ComponentObject*, CircleComponent*>() });
				_circleComponentList[pParent->GetIndex()].insert({ pParent, pData });
			}
			return true;
		}
	}

	if (eventType == EventType::ReleaseComponent)
	{
		ComponentObject* pExtraInfo = static_cast<ComponentObject*>(msg->_pExtraInfo);
		auto pData = dynamic_cast<CircleComponent*>(pExtraInfo);
		if (pData != nullptr)
		{
			auto iter = _circleComponentList.find(pData->GetParentPtr()->GetIndex());
			if (iter == _circleComponentList.end())
			{
				return true;
			}
			_circleComponentList.erase(iter);
			auto iter2 = _collisionCheckList.find(pData);
			if (iter2 == _collisionCheckList.end())
			{
				return true;
			}
			for (auto& pData : iter2->second)
			{
				auto iter = _collisionCheckList.find(pData);
				if (iter != _collisionCheckList.end())
				{
					iter->second.erase(iter2->first);
				}
			}
			_collisionCheckList.erase(iter2->first);
		}
		return true;
	}
	return false;
}

CollisionManager::CollisionManager()
{

}

CollisionManager::~CollisionManager()
{
	CRelease();
}