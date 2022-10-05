#include "TextManager.h"
#include "Message.h"
#include "Writer.h"

unsigned __int64 TextManager::_AllocIndex = 0;

void TextManager::Set(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pImmediateContext, IDXGISwapChain* pSwapChain)
{
	_pd3dDevice = pd3dDevice;
	_pImmediateContext = pImmediateContext;
	_pSwapChain = pSwapChain;
}

bool TextManager::CInit()
{
	return true;
}

bool TextManager::CFrame()
{
	return true;
}

bool TextManager::CRender()
{
	return true;
}

bool TextManager::CRelease()
{
	return true;
}

bool TextManager::OnEvent(EventType eventType, ComponentObject* pSender, Message* msg)
{
	if (eventType == EventType::CreateTextDraw)
	{
		//msg->_pExtraInfo
	}

	if (eventType == EventType::CreatedTextDraw)
	{

	}
	return true;
}

TextManager::TextManager()
{

}

TextManager::~TextManager()
{
	CRelease();
}
