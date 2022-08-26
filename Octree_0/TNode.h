#pragma once
#include <windows.h>
#include <map>
#include <queue>
#include "TObject.h"
class TNode
{
public:
    TRect m_rt;
    int    m_iDepth;
    std::vector<TObject*>  m_ObjectStaticList;
    std::vector<TObject*>  m_ObjectDynamicList;
    std::vector<TNode*> m_Child;
    TNode* m_pParent;
public:
    TNode(TNode* pParent, float x, float y, float w, float h, int size)
    {
        m_rt.Set(x, y, w, h);
        m_iDepth = 0;
        m_pParent = nullptr;
        if (pParent != nullptr)
        {
            m_pParent = pParent;
            m_iDepth = pParent->m_iDepth + 1;
        }
        m_Child.resize(size);
    }
    ~TNode()
    {
        for(auto child : m_Child)
        {
            delete child;
        }
    }
};
