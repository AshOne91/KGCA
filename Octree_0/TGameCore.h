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
    bool    Init();     // �ʱ�ȭ	
    bool    Frame(float fDeltaTime, float fGameTime);    // �ǽð� ���
    bool    Render();   // ȭ�鿡 ��ο�
    bool    Release();  // �Ҹ�����
    bool	Run();      // ��������
};

