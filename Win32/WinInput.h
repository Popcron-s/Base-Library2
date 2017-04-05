#pragma once

#include "..\\Interface\\Base_Input.h"

#include "Windows.h"
#include <iostream>

class _Win32Input : public _Input{
private:
	unsigned long cur_time[8];

	_Win32Input(){
		m_pKeyboard = new KEYBOARD;
		*m_pKeyboard = {};
		m_pMouse = new MOUSE;
		*m_pMouse = {};

		for(UINT i = 0 ; i<8 ; ++i){cur_time[i] = 0;}
	}
	~_Win32Input(){
		if(m_pKeyboard != nullptr){
			delete m_pKeyboard;
			m_pKeyboard = nullptr;
		}
		if(m_pMouse != nullptr){
			delete m_pMouse;
			m_pMouse = nullptr;
		}
	}

public:
	_PLATFORM::TYPE GetType(){return _PLATFORM::Win32;}
	static _Input* GetSingleton(){
		if(m_pSingleton == nullptr){
			m_pSingleton = new _Win32Input;
		}
		else if(m_pSingleton->GetType() != _PLATFORM::Win32){
			Destroy();
			m_pSingleton = new _Win32Input;
		}
		return m_pSingleton;
	}
	void Update(){
		//Keyboard
		for(UINT i = 0 ; i<0x100 ; ++i){
			if(GetAsyncKeyState(i) & 0x8001){
				if(m_pKeyboard->KEY[i] & 0x80){
					m_pKeyboard->KEY[i] = 0x80;
				}
				else{
					m_pKeyboard->KEY[i] = 0x81;
				}
			}
			else{
				if(m_pKeyboard->KEY[i] & 0x80){
					m_pKeyboard->KEY[i] = 0x01;
				}
				else{
					m_pKeyboard->KEY[i] = 0x00;
				}
			}
		}
		//Mouse

#define MOUSE_CLICK(key,num)												\
		if(GetAsyncKeyState(key) & 0x8001){									\
			if(m_pMouse->button[num] & 0x80){								\
				m_pMouse->button[num] = 0x80;								\
			}																\
			else{															\
				if(GetDoubleClickTime() >= (GetTickCount()-cur_time[num])){	\
					m_pMouse->button[num] = 0x82;							\
					cur_time[num] = GetTickCount();							\
				}															\
				else{														\
					m_pMouse->button[num] = 0x81;							\
					cur_time[num] = GetTickCount();							\
				}															\
			}																\
		}																	\
		else{																\
			if(m_pMouse->button[num] & 0x80){								\
				m_pMouse->button[num] = 0x01;								\
			}																\
			else{															\
				m_pMouse->button[num] = 0x00;								\
			}																\
		}
		GetCursorPos((LPPOINT)m_pMouse);
		ScreenToClient(Windows::GetSingleton()->Gethwnd(), (LPPOINT)m_pMouse);
		MOUSE_CLICK(VK_LBUTTON,0)
		MOUSE_CLICK(VK_RBUTTON,1)
		MOUSE_CLICK(VK_MBUTTON,2)
		MOUSE_CLICK(VK_XBUTTON1,3)
		MOUSE_CLICK(VK_XBUTTON2,4)
#undef MOUSE_CLICK
	}
};