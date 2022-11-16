#include "SceneMain.h"
#include "MapManager.h"
#include "User2DComponent.h"
#include "SoundManager.h"
#include "UIHpBar.h"
#include "EventManager.h"
#include "SceneManager.h"
#include "SceneEnd.h"
#include "GameWorld.h"

unsigned __int64 g_CreateMonster = 0;
unsigned __int64 g_currentMonster = 0;
unsigned __int64 g_DeadMonster = 0;
bool g_bClear = false;
int g_iRemainTime = 180;

extern int g_iMaxHP;
extern int g_iCurrentHP;
void SceneMain::OnEnter()
{
	g_CreateMonster = 0;
	g_currentMonster = 0;
	g_DeadMonster = 0;
	g_iRemainTime = 180;
	g_bClear = false;
	I_GameWorld.SetCameraPos({ 0.0f, 0.0f });
	I_Sprite.Load(L"SpriteInfo.txt");
	I_MapManager.CInit();
	_pUser = CreateObject<User2DComponent>();
	_pBackGroundMusic = I_Sound.Load(L"../../resource/sfx/bgm_elrond_plant.ogg");
	_pBackGroundMusic->Play(true);
	monsterTextIndex = CreateText(L"고딕", 10, 550, 25);
	hpTextIndex = CreateText(L"고딕", 500, 55, 25);
	remainTimeTextIndex = CreateText(L"고딕", 10, 100, 25);
	auto pUI = CreateUI<UIHpBar>();
	pUI->Create(_pd3dDevice, _pImmediateContext, L"DefaultShape.txt", L"../../resource/hpbar.png");
	pUI->SetAttribute({ 340.0f, 75.0f }, { 50, 320, 590.0f, 62.0f });
	I_EventManager.AddListener(EventType::HpChange, pUI);
	pUI = CreateUI<UIHpBar>();
	pUI->Create(_pd3dDevice, _pImmediateContext, L"DefaultShape.txt", L"../../resource/hpbar.png");
	pUI->SetAttribute({ 350.0f, 110.0f }, { 0, 0, 689.0f, 218.0f });

}

void SceneMain::OnExecute()
{
	if (g_iRemainTime < 0)
	{
		g_bClear = true;
		I_SceneManager.ChangeState(&SceneEnd::GetInstance());
		return;
	}
	if (g_iCurrentHP <= 0)
	{
		I_SceneManager.ChangeState(&SceneEnd::GetInstance());
		return;
	}
	_fTimer += g_fSecondPerFrame;
	if (_fTimer >= 1.0f)
	{
		g_iRemainTime -= 1;
		_fTimer -= 1.0f;
	}
	std::wstring remainTime = L"남은시간:";
	remainTime += std::to_wstring(g_iRemainTime);
	SetText(remainTimeTextIndex, remainTime, { 1.0f, 1.0f, 1.0f, 1.0f });
	g_currentMonster = g_CreateMonster - g_DeadMonster;
	std::wstring monsterText = L"";
	monsterText += L"생성몬스터:";
	monsterText += std::to_wstring(g_CreateMonster);
	monsterText += L" ";
	monsterText += L"현재몬스터:";
	monsterText += std::to_wstring(g_currentMonster);
	monsterText += L" ";
	monsterText += L"죽은몬스터:";
	monsterText += std::to_wstring(g_DeadMonster);
	SetText(monsterTextIndex, monsterText, { 1.0f, 1.0f, 1.0f, 1.0f });
	std::wstring hpText = L"";
	hpText += std::to_wstring(g_iCurrentHP);
	hpText += L"/";
	hpText += std::to_wstring(g_iMaxHP);
	SetText(hpTextIndex, hpText, { 1.0f, 1.0f, 1.0f, 1.0f });
	I_MapManager.CFrame();
}

void SceneMain::OnExit()
{
	I_EventManager.RemoveEvent(EventType::HpChange);
	_pBackGroundMusic->Stop();
	I_MapManager.CRelease();
}

