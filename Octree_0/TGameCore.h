#pragma once
#include "TQuadtree.h"
#include "TGamePlayer.h"
#include "TMapObject.h"
#include "TNonCharacter.h"
class TGameCore
{
public:
    TGamePlayer             m_player;   
    TQuadtree               m_pWorldSP;
    std::map<int, TObject*> m_npcList;
    std::map<int, TObject*> m_AllObjectList;
    std::vector<TObject*>   m_DrawList;
public:
    bool    Init();     // 초기화	
    bool    Frame(float fDeltaTime, float fGameTime);    // 실시간 계산
    bool    Render();   // 화면에 드로우
    bool    Release();  // 소멸하자
    bool	Run();      // 실행하자
};

