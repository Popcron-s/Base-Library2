#pragma once

#include "..\\Common\\Singleton.h"

#include "Renderer.h"
#include "..\\Interface\\Base_Timer.h"
#include "..\\Interface\\Base_Input.h"

#include <iostream>

class MainSystem : public Singleton<MainSystem>{
private:
	//Timer
	//Event Dispatcher
	//Physic
	//Renderer

	//ObjectManager
	//MapList
	//ScreenList

public:
	static void Render(){
		if(_Timer::GetSingleton() != nullptr){_Timer::GetSingleton()->Update();}	//timer update
		if(_Input::GetSingleton() != nullptr){_Input::GetSingleton()->Update();}	//input check
		//event dispatch
		Renderer::GetSingleton()->Update();	//object update
		//physics update
		Renderer::GetSingleton()->Render();	//render
	}

	UINT GetTick(){
		if(_Timer::GetSingleton() == nullptr){return 0;} 
		return _Timer::GetSingleton()->GetTick();
	}

	KEYBOARD* GetKeyboard(){
		if(_Input::GetSingleton() == nullptr){return 0;} 
		return _Input::GetSingleton()->GetKeyboard();
	}
	MOUSE* GetMouse(){
		if(_Input::GetSingleton() == nullptr){return 0;} 
		return _Input::GetSingleton()->GetMouse();
	}
};