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
	static _FileLoader* GetSingleton(){
		if(m_pSingleton == nullptr){
			m_pSingleton = new _Win32FileLoader;
		}
		else if(m_pSingleton->GetType() != _PLATFORM::Win32){
			Destroy();
			m_pSingleton = new _Win32FileLoader;
		}
		return m_pSingleton;
	}
	bool FileLoader(char* name, UINT* size, BYTE** buf){
		if(_access_s(name, 0x04) != 0x00){return false;}

		int handle = 0;
		_sopen_s(&handle, name, _O_RDONLY | _O_BINARY, _SH_DENYWR, _S_IREAD);
		*size = _filelength(handle);
		if(*buf != nullptr){
			delete [] *buf;
			*buf = nullptr;
		}
		*buf = new BYTE[*size];
		_read(handle, *buf, *size);
		_close(handle);
		return true;
	}
};