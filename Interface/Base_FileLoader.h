#pragma once

#include "..\\Common\\variable.h"
#include "..\\Common\\Enum.h"

#include "InterfaceSingleton.h"

class _FileLoader : public InterfaceSingleton<_FileLoader>{
public:
	_FileLoader(){}
	~_FileLoader(){}

	virtual _PLATFORM::TYPE GetType() = 0;
	virtual bool FileLoader(char* name, UINT* size, BYTE** buf) = 0;
};
