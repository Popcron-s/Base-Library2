#pragma once

#include "..\\Common\\variable.h"
#include "..\\Common\\Enum.h"

#include "InterfaceSingleton.h"

class _FileIO : public InterfaceSingleton<_FileIO>{
public:
	_FileIO(){}
	~_FileIO(){}

	virtual _PLATFORM::TYPE GetType() = 0;
	virtual bool FileRead(char* name, UINT& size, BYTE*& buf) = 0;
	virtual bool FileWrite(char* name, UINT size, BYTE* buf) = 0;
};
