#include <iostream>
#include <map>
#include "TQuadtree.h"
#include "TShape.h"
int main()
{
	TQuadtree qt;
	std::map<int, TObject*> objectlist;

	if (qt.Create(TRect{ -100, -100, 200, 200 }))
	{
		for (int iObj = 0; iObj < 10; ++iObj)
		{
			TObject* pNewObject = new TObject;
			TRect rt;
			rt.left = cosf(rand()) * 100.0f;
			rt.top = sinf(rand()) * 100.0f;
			rt.right = 10.0f;
			rt.bottom = 10.0f;
			pNewObject->Create(rt);

			//pNewObject.SetPos(TRect());
			objectlist.insert(std::make_pair(iObj, pNewObject));
			qt.AddObject(pNewObject);
			//qt.AddObject(iObj);
		}

	}
	while (1)
	{
		qt.Reset(qt._pRootNode);
		for (auto object : objectlist)
		{
			TObject* pObject = object.second;
			pObject->SetPos(pObject->_rt.left, pObject->_rt.top);
			qt.AddObject(pObject);
		}
		_sleep(1000);
	}

	for (auto object : objectlist)
	{
		TObject* pObject = object.second;
		delete pObject;
	}
}