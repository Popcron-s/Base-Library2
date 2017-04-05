#include "FileLoader.h"
#include "..\\Interface\\Base_FileLoader.cpp"

_FileLoader* _Win32FileLoader::GetSingleton(){
	if(m_pSingleton == nullptr){
		m_pSingleton = new _Win32FileLoader;
	}
	else if(m_pSingleton->GetType() != _PLATFORM::Win32){
		Destroy();
		m_pSingleton = new _Win32FileLoader;
	}
	return m_pSingleton;
}
bool _Win32FileLoader::FileLoader(char* name, UINT* size, BYTE** buf){
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