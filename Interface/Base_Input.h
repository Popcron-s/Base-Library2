#pragma once

#include "..\\Common\\variable.h"
#include "..\\Common\\Enum.h"

#include "InterfaceSingleton.h"

class _Input : public InterfaceSingleton<_Input>{
protected:
	KEYBOARD* m_pKeyboard;
	MOUSE* m_pMouse;

public:
	_Input() : m_pKeyboard(nullptr), m_pMouse(nullptr){}
	~_Input(){}

	virtual _PLATFORM::TYPE GetType() = 0;
	virtual void Update() = 0;

	virtual KEYBOARD* GetKeyboard(){return m_pKeyboard;}
	virtual MOUSE* GetMouse(){return m_pMouse;}
};