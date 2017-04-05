#pragma once

#include "..\\Interface\\Base_FileLoader.h"

#include <io.h>
#include <fcntl.h>
#include <share.h>
#include <sys\\stat.h>

class _Win32FileLoader : public _FileLoader{
private:
	_Win32FileLoader(){}
	~_Win32FileLoader(){}

public:
	_PLATFORM::TYPE GetType(){return _PLATFORM::Win32;}
	static _FileLoader* GetSingleton();
	bool FileLoader(char* name, UINT* size, BYTE** buf);
};