#pragma once

#include "Base_FileLoader.h"

_FileLoader* _FileLoader::m_pSingleton = nullptr;

_FileLoader::_FileLoader(){}
_FileLoader::~_FileLoader(){}
_FileLoader* _FileLoader::GetSingleton(){return m_pSingleton;}
void _FileLoader::Destroy(){
	if(m_pSingleton != nullptr){
		delete m_pSingleton;
		m_pSingleton = nullptr;
	}
}