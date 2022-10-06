#include "UIHpBar.h"

extern int g_iMaxHP;
extern int g_iCurrentHP;
bool UIHpBar::CInit()
{
    UIHpBar::Init();
    return true;
}

bool UIHpBar::CFrame()
{
    UIHpBar::Frame();
    return true;
}

bool UIHpBar::CRender()
{
    UpdateVertexBuffer();
    UIHpBar::Render();
    return true;
}

bool UIHpBar::CRelease()
{
    UIHpBar::Release();
    ComponentObject::CRelease();
    return true;
}

bool UIHpBar::OnEvent(EventType eventType, ComponentObject* pSender, Message* msg)
{
    if (eventType == EventType::HpChange)
    {
        float hp = ((float)g_iCurrentHP / (float)g_iMaxHP);
        float width = (hp) * 590.0f;
        float temp = (590.0f - hp * 590.0f) * 0.5f;
        float pos = 340.0f - temp;
        SetAttribute({ pos, 75.0f }, { 50, 320, width, 62.0f });
    }
    return true;
}
