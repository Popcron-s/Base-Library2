#pragma once

//#include "Base_Output_Graphics.h"

_O_Graphics* _O_Graphics::m_pSingleton = nullptr;

_O_Graphics::_O_Graphics(){}
_O_Graphics::~_O_Graphics(){}

_O_Graphics* _O_Graphics::GetSingleton(){return m_pSingleton;}
void _O_Graphics::Destroy(){
	if(m_pSingleton != nullptr){
		delete m_pSingleton;
		m_pSingleton = nullptr;
	}
}