#pragma once
#include "TDefine.h"

namespace TBASIS_BASE {

template<class T> class TSingleton
{		
public:
	static T& GetInstance() 
	{		
		static T theSingleInstance;  
		return theSingleInstance; 
	}
	static T* GetInstancePtr() 
	{
		static T theSingleInstance; 
		return &theSingleInstance; 
	}
};

}