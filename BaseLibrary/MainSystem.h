#pragma once

#include "..\\Common\\Singleton.h"

#include "Renderer.h"
#include "..\\Interface\\Base_Timer.h"
#include "..\\Interface\\Base_Input.h"

class MainSystem : public Singleton<MainSystem>{
private:
	//Timer
	//Event Dispatcher
	//Physic
	//Renderer

	//ObjectManager
	//MapList
	//ScreenList
	UINT screen_x;
	UINT screen_y;

public:
	static void (*CommonUpdate)();

	static void MainLoop(){
		if(MainSystem::CommonUpdate != nullptr){(*MainSystem::CommonUpdate)();}
		if(_Timer::GetSingleton() != nullptr){_Timer::GetSingleton()->Update();}	//timer update
		if(_Input::GetSingleton() != nullptr){_Input::GetSingleton()->Update();}	//input check
		//event dispatch
		Renderer::GetSingleton()->Update();	//object update
		//physics update
		Renderer::GetSingleton()->Render(GetSingleton()->GetTick());	//render
	}

	UINT GetTick(){
		if(_Timer::GetSingleton() == nullptr){return 0;} 
		return _Timer::GetSingleton()->GetTick();
	}

	KEYBOARD* GetKeyboard(){
		if(_Input::GetSingleton() == nullptr){return nullptr;} 
		return _Input::GetSingleton()->GetKeyboard();
	}
	MOUSE* GetMouse(){
		if(_Input::GetSingleton() == nullptr){return nullptr;} 
		return _Input::GetSingleton()->GetMouse();
	}

	void SetScreen(UINT x, UINT y){screen_x = x; screen_y = y;}
	UINT GetScreenX(){return screen_x;}
	UINT GetScreenY(){return screen_y;}

	FLOAT3 Click(FLOAT x, FLOAT y, FLOAT z = 1.0f){
		SCREEN* s = Graphic_Renderer::GetSingleton()->GetScreen(0);
		MATRIX4x4 r = Graphic_Renderer::ReverseViewProjectionMatrix(s->view, s->proj);
		
		FLOAT3 v = {
			(((x*2.0f)/1280.0f)-1.0f)/(s->proj._11),
			(((y*2.0f)/720.0f)-1.0f)/(s->proj._22),
			1.0
		};

		v.z = ((v.x*r._13)+(v.y*r._23)+r._43)/r._33;

		return v;
	}

	FLOAT2 ClickOrtho(FLOAT x, FLOAT y){
		const SCREEN* s = Graphic_Renderer::GetSingleton()->GetScreen(0);
		
		//y += 10.0f;

		FLOAT2 v = {
			(((x*2.0f)/screen_x)-1.0f)/(s->proj._11),
			(((y*2.0f)/screen_y)-1.0f)/(s->proj._22)
		};

		v.x -= s->view._41;
		v.y += s->view._42;

		return v;
	}
};

void (*MainSystem::CommonUpdate)() = nullptr;