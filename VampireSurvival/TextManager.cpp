#include "TextManager.h"
#include "Message.h"
#include "Writer.h"
#include "EventManager.h"

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
	for (auto& drawText : _textDrawList)
	{
		auto pTextInfo = drawText.second.first;
		drawText.second.second->Draw(pTextInfo->x, pTextInfo->y, pTextInfo->text, pTextInfo->color);
	}
	return true;
}

bool TextManager::CRelease()
{
	for (auto& data : _textDrawList)
	{
		delete data.second.first;
		data.second.second->Release();
		delete data.second.second;
	}
	_textDrawList.clear();
	ComponentObject::CRelease();
	return true;
}

bool TextManager::OnEvent(EventType eventType, ComponentObject* pSender, Message* msg)
{
	return true;
}

unsigned __int64 TextManager::CreateText(std::wstring& font, int x, int y, int size, D2D1_COLOR_F color)
{
	Writer* pWriter = new Writer();
	TextInfo* pTextInfo = new TextInfo();
	pWriter->Init(font, size);

	IDXGISurface1* pBackBuffer;
	_pSwapChain->GetBuffer(0, __uuidof(IDXGISurface1),
		(void**)&pBackBuffer);
	pWriter->Set(pBackBuffer);
	pBackBuffer->Release();

	pTextInfo->x = x;
	pTextInfo->y = y;
	pTextInfo->color = color;
	unsigned __int64 allocIndex = ++_AllocIndex;
	_textDrawList.insert({ allocIndex, {pTextInfo, pWriter} });
	return allocIndex;
}

void TextManager::DestroyText(unsigned __int64 index)
{
	auto iter = _textDrawList.find(index);
	delete iter->second.first;
	iter->second.second->Release();
	delete iter->second.second;
	_textDrawList.erase(iter);
}

void TextManager::SetText(unsigned __int64 index, std::wstring& text, D2D1_COLOR_F color)
{
	auto iter = _textDrawList.find(index);
	auto pTextInfo = iter->second.first;
	iter->second.first->color = color;
	iter->second.first->text = text;
}

TextManager::TextManager()
{

}

TextManager::~TextManager()
{
	CRelease();
}
