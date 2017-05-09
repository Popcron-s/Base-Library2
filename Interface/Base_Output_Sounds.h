#pragma once

#include "..\\BaseLibrary\\Object.h"
#include "..\\Common\\variable.h"
#include "..\\Common\\Enum.h"

#include "InterfaceSingleton.h"

class _O_Sounds : public InterfaceSingleton<_O_Sounds>{
public:
	_O_Sounds(){}
	~_O_Sounds(){}

	virtual _INTERFACE::SOUND GetType() = 0;

	virtual bool Init() = 0;
	virtual bool Release() = 0;
	virtual bool RegistGraph(SOUND s, UINT loop = 0) = 0;
	virtual bool RemoveGraph(UINT id) = 0;
	virtual void Run() = 0;
};