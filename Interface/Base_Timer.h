#pragma once

#include "..\\Common\\variable.h"

#include "InterfaceSingleton.h"

class _Timer : public InterfaceSingleton<_Timer>{
protected:
	UINT m_Current;
	UINT m_Tick;

public:
	_Timer(){}
	~_Timer(){}

	virtual _PLATFORM::TYPE GetType() = 0;
	virtual void Update() = 0;
	virtual UINT GetTick(){return m_Tick;}
};