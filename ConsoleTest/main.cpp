#include <iostream>
#include "..\\Win32\\Win32_API.h"
#include "..\\Win32\\Win32_API.cpp"

#include "..\\Coder\\Coder.h"

#include "..\\BaseLibrary\\MainSystem.h"
#include "..\\BaseLibrary\\Map.h"
#include "..\\BaseLibrary\\Object.h"

#include "..\\Common\\Tree.h"

#include "..\\BaseLibrary\\Collision2D.h"

class testWalker : public OBJECT{
private:

public:
	testWalker(){
		Map::GetSingleton()->RegistObject(this, 0);

		//SetPosition({1.0f, 2.0f, 3.0f});

		JOINT t_joint = {
			JOINT_NAME::NONE, 
			{10.0f, 22.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {10.0f, 10.0f, 1.0f}, 
			MATRIX4x4::Initialize()
		};

		GetSkeletal().CreateRoot(t_joint);

		Tree<JOINT>::searcher scr = GetSkeletal().Begin();

		MESH t_mesh = {&(*scr), new VERTEX[4], 4, nullptr, nullptr};
		t_mesh.vtx[0] = {{-1.0f, -1.0f, 0.0f},{1.0f, 0.0f, 0.0f, 1.0f},{},{0.0f, 0.0f}};
		t_mesh.vtx[1] = {{ 1.0f, -1.0f, 0.0f},{1.0f, 0.0f, 0.0f, 1.0f},{},{1.0f, 0.0f}};
		t_mesh.vtx[2] = {{-1.0f,  1.0f, 0.0f},{1.0f, 0.0f, 0.0f, 1.0f},{},{0.0f, 1.0f}};
		t_mesh.vtx[3] = {{ 1.0f,  1.0f, 0.0f},{1.0f, 0.0f, 0.0f, 1.0f},{},{1.0f, 1.0f}};

		GetMesh().CreateNode(t_mesh);

		BOX* t_col = new BOX;
		t_col->joint = &(*scr);
		t_col->_1 = {-1.0f, -1.0f, 0.0f};
		t_col->_2 = { 1.0f, -1.0f, 0.0f};
		t_col->_3 = { 1.0f,  1.0f, 0.0f};
		t_col->_4 = {-1.0f,  1.0f, 0.0f};
		GetCollider2D().CreateNode(t_col);
	}
	~testWalker(){}

	void update(){
		BOX target_box = {};
		target_box.joint = nullptr;
		target_box._1 = {-100.0f, -10.0f, 0.0f};
		target_box._2 = { 100.0f, -10.0f, 0.0f};
		target_box._3 = { 100.0f,  10.0f, 0.0f};
		target_box._4 = {-100.0f,  10.0f, 0.0f};

		if(Collision2D::GetSingleton()->Collision(*(GetCollider2D().GetData(0)), target_box)){
			GetMesh().GetData(0).vtx[0].diffuse.x = 0.0f;
			GetMesh().GetData(0).vtx[1].diffuse.x = 0.0f;
			GetMesh().GetData(0).vtx[2].diffuse.x = 0.0f;
			GetMesh().GetData(0).vtx[3].diffuse.x = 0.0f;

			GetMesh().GetData(0).vtx[0].diffuse.y = 1.0f;
			GetMesh().GetData(0).vtx[1].diffuse.y = 1.0f;
			GetMesh().GetData(0).vtx[2].diffuse.y = 1.0f;
			GetMesh().GetData(0).vtx[3].diffuse.y = 1.0f;
		}
		else{
			GetMesh().GetData(0).vtx[0].diffuse.y = 0.0f;
			GetMesh().GetData(0).vtx[1].diffuse.y = 0.0f;
			GetMesh().GetData(0).vtx[2].diffuse.y = 0.0f;
			GetMesh().GetData(0).vtx[3].diffuse.y = 0.0f;

			GetMesh().GetData(0).vtx[0].diffuse.x = 1.0f;
			GetMesh().GetData(0).vtx[1].diffuse.x = 1.0f;
			GetMesh().GetData(0).vtx[2].diffuse.x = 1.0f;
			GetMesh().GetData(0).vtx[3].diffuse.x = 1.0f;
		}

		Tree<JOINT>::searcher scr = GetSkeletal().Begin();
		FLOAT3& pos = scr->pos;
		FLOAT3& rot = scr->rot;
		/*if(MainSystem::GetSingleton()->GetKeyboard()->KEY['W'] & 0x81){pos.y-=1.0f;}
		if(MainSystem::GetSingleton()->GetKeyboard()->KEY['S'] & 0x81){pos.y+=1.0f;}
		if(MainSystem::GetSingleton()->GetKeyboard()->KEY['A'] & 0x81){pos.x-=1.0f;}
		if(MainSystem::GetSingleton()->GetKeyboard()->KEY['D'] & 0x81){pos.x+=1.0f;}
		if(MainSystem::GetSingleton()->GetKeyboard()->KEY['Q'] & 0x81){rot.z+=1.0f;}
		if(MainSystem::GetSingleton()->GetKeyboard()->KEY['E'] & 0x81){rot.z-=1.0f;}*/
		FLOAT f = DEGREE(rot.z);
		if(f > 360.0f){f = 0.0f;}
		else{f += 1.0f;}
		rot.z = RADIAN(f);
		//SetPosition(pos);
		//SetRotation(rot);

		if(MainSystem::GetSingleton()->GetKeyboard()->KEY[VK_SPACE] & 0x81){
			SetPosition({});
			SetRotation({});
		}
	}
};

class Selecter : public OBJECT{
private:
	MESH* s_mesh;
public:
	Selecter(){
		Map::GetSingleton()->RegistObject(this, 0);

		SetPosition({0.0f, 0.0f, 0.0f});

		JOINT t_joint = {
			JOINT_NAME::NONE, 
			{0.0f, 0.0f, 10.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f, 1.0f}, 
			MATRIX4x4::Initialize()
		};

		GetSkeletal().CreateRoot(t_joint);

		Tree<JOINT>::searcher scr = GetSkeletal().Begin();

		GetSkeletal().Create(scr, t_joint);

		MESH t_mesh = {&(*scr), new VERTEX[4], 4, nullptr, nullptr};
		t_mesh.vtx[0] = {{-10.0f, -10.0f, 0.0f},{0.0f, 1.0f, 0.0f, 1.0f},{},{0.0f, 0.0f}};
		t_mesh.vtx[1] = {{ 10.0f, -10.0f, 0.0f},{0.0f, 1.0f, 0.0f, 1.0f},{},{1.0f, 0.0f}};
		t_mesh.vtx[2] = {{-10.0f,  10.0f, 0.0f},{0.0f, 1.0f, 0.0f, 1.0f},{},{0.0f, 1.0f}};
		t_mesh.vtx[3] = {{ 10.0f,  10.0f, 0.0f},{0.0f, 1.0f, 0.0f, 1.0f},{},{1.0f, 1.0f}};
		GetMesh().CreateNode(t_mesh);

		BOX* t_col = new BOX;
		t_col->joint = &(*scr);
		t_col->_1 = {-10.0f, -10.0f, 0.0f};
		t_col->_2 = { 10.0f, -10.0f, 0.0f};
		t_col->_3 = { 10.0f,  10.0f, 0.0f};
		t_col->_4 = {-10.0f,  10.0f, 0.0f};
		GetCollider2D().CreateNode((BOX*)t_col);
	}
	~Selecter(){
		
	}

	void update(){
		BOX& t_col = (BOX&)*(GetCollider2D().GetData(0));
		UINT x = MainSystem::GetSingleton()->GetMouse()->x;
		UINT y = MainSystem::GetSingleton()->GetMouse()->y;
		FLOAT2 v = MainSystem::GetSingleton()->ClickOrtho(x,y);
		//std::cout<< v.x << " / " << v.y <<std::endl;
		if(Collision2D::GetSingleton()->Raycast(v.x, v.y, t_col)){
			GetMesh().GetData(0).vtx[0].diffuse.y = 1.0f;
			GetMesh().GetData(0).vtx[1].diffuse.y = 1.0f;
			GetMesh().GetData(0).vtx[2].diffuse.y = 1.0f;
			GetMesh().GetData(0).vtx[3].diffuse.y = 1.0f;

			GetMesh().GetData(0).vtx[0].diffuse.x = 0.0f;
			GetMesh().GetData(0).vtx[1].diffuse.x = 0.0f;
			GetMesh().GetData(0).vtx[2].diffuse.x = 0.0f;
			GetMesh().GetData(0).vtx[3].diffuse.x = 0.0f;
		}
		else{
			GetMesh().GetData(0).vtx[0].diffuse.x = 1.0f;
			GetMesh().GetData(0).vtx[1].diffuse.x = 1.0f;
			GetMesh().GetData(0).vtx[2].diffuse.x = 1.0f;
			GetMesh().GetData(0).vtx[3].diffuse.x = 1.0f;

			GetMesh().GetData(0).vtx[0].diffuse.y = 0.0f;
			GetMesh().GetData(0).vtx[1].diffuse.y = 0.0f;
			GetMesh().GetData(0).vtx[2].diffuse.y = 0.0f;
			GetMesh().GetData(0).vtx[3].diffuse.y = 0.0f;
		}
	}
};

class FPS : public OBJECT{
private:
	//SCREEN* s;
	FLOAT pos_x;
	FLOAT pos_y;

	SOUND s1;

public:
	FPS(){
		Map::GetSingleton()->RegistObject(this, 0);
		//s = Graphic_Renderer::GetSingleton()->GetScreen(0);
		pos_x = 0.0f; pos_y = 0.0f;
		SCREEN* s = Graphic_Renderer::GetSingleton()->GetScreen(0);
		s->view = Graphic_Renderer::SetViewMatrix({pos_x, pos_y, -10.0f},{pos_x, pos_y, 0.0f},{0.0f, -1.0f, 0.0f});

		JOINT t_joint = {
			JOINT_NAME::NONE, 
			{0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, 
			MATRIX4x4::Initialize()
		};

		GetSkeletal().CreateRoot(t_joint);

		Tree<JOINT>::searcher scr = GetSkeletal().Begin();

		MESH t_mesh = {&(*scr), new VERTEX[4], 4, nullptr, nullptr};
		t_mesh.vtx[0] = {{-100.0f, -10.0f, 0.0f},{1.0f, 1.0f, 1.0f, 0.5f},{},{0.0f, 0.0f}};
		t_mesh.vtx[1] = {{ 100.0f, -10.0f, 0.0f},{1.0f, 1.0f, 1.0f, 0.5f},{},{1.0f, 0.0f}};
		t_mesh.vtx[2] = {{-100.0f,  10.0f, 0.0f},{1.0f, 1.0f, 1.0f, 0.5f},{},{0.0f, 1.0f}};
		t_mesh.vtx[3] = {{ 100.0f,  10.0f, 0.0f},{1.0f, 1.0f, 1.0f, 0.5f},{},{1.0f, 1.0f}};

		GetMesh().CreateNode(t_mesh);

		GetSkeletal().Create(scr, t_joint);
		scr.Child(0);
		t_mesh.joint = &(*scr);
		t_mesh.vtx = new VERTEX[4];
		t_mesh.vtx[0] = {{-10.0f, -10.0f, 0.0f},{1.0f, 1.0f, 1.0f, 0.5f},{},{0.0f, 0.0f}};
		t_mesh.vtx[1] = {{ 10.0f, -10.0f, 0.0f},{1.0f, 1.0f, 1.0f, 0.5f},{},{1.0f, 0.0f}};
		t_mesh.vtx[2] = {{-10.0f,  10.0f, 0.0f},{1.0f, 1.0f, 1.0f, 0.5f},{},{0.0f, 1.0f}};
		t_mesh.vtx[3] = {{ 10.0f,  10.0f, 0.0f},{1.0f, 1.0f, 1.0f, 0.5f},{},{1.0f, 1.0f}};

		GetMesh().CreateNode(t_mesh);
		
		CreateAnimation(1);
		GetAnimation()[0] = new _Graph_function<FPS>(this, 1);
		((_Graph_function<FPS>*)GetAnimation()[0])->SetNode(0, &FPS::sound, 4000);
		GetAnimation()[0]->SetAuto(true);
		GetAnimation()[0]->SetLoop(true);
		/*
		void (FPS::*func)() = nullptr;

		func = &FPS::sound;
		(this->*func)();*/

		BYTE* buf = nullptr;
		UINT buf_size = 0;
		_FileIO::GetSingleton()->FileRead("Alert.wav", buf_size, buf);
		WAVDecoder(buf, buf_size, s1);
		delete [] buf;
	}
	~FPS(){Map::GetSingleton()->RemoveObject(this, 0);}

	void sound(){
		std::cout<< MainSystem::GetSingleton()->GetTick() << " : act function" <<std::endl;
		_O_Sounds::GetSingleton()->RegistGraph(s1);
	}

	void update(){
		UINT frame = 0;
		if(MainSystem::GetSingleton()->GetTick() != 0){
			frame = 1000/MainSystem::GetSingleton()->GetTick();
		}
		//std::cout<< frame << "f/s" <<std::endl;

		if(MainSystem::GetSingleton()->GetMouse()->button[0] & 0x81){
			INT x = MainSystem::GetSingleton()->GetMouse()->x;
			INT y = MainSystem::GetSingleton()->GetMouse()->y;

			FLOAT2 t = {};/*
			for(UINT z = 0 ; z<10000 ; ++z){
				if(t.z <= 0.0f){std::cout<< z <<std::endl; break;}
			}*/
			t = MainSystem::GetSingleton()->ClickOrtho(x, y);
			//std::cout<< t.x << " / " << t.y <<std::endl;
			/*
			GetMesh().GetData(1).vtx[0].pos = {t.x-5.0f, t.y-5.0f, 0.0f};
			GetMesh().GetData(1).vtx[1].pos = {t.x+5.0f, t.y-5.0f, 0.0f};
			GetMesh().GetData(1).vtx[2].pos = {t.x-5.0f, t.y+5.0f, 0.0f};
			GetMesh().GetData(1).vtx[3].pos = {t.x+5.0f, t.y+5.0f, 0.0f};*/
			SKEL_SEARCHER(scr);
			scr.Child(0);
			scr->pos = {t.x, t.y, 0.0f};
		}

		if(MainSystem::GetSingleton()->GetKeyboard()->KEY[VK_NUMPAD1] == 0x81){
			SOUND s = {};
			BYTE* buf = nullptr;
			UINT buf_size = 0;
			_FileIO::GetSingleton()->FileRead("Alert.wav", buf_size, buf);
			WAVDecoder(buf, buf_size, s);
			delete [] buf;

			_O_Sounds::GetSingleton()->RegistGraph(s,1);
		}
		if(MainSystem::GetSingleton()->GetKeyboard()->KEY[VK_NUMPAD2] == 0x81){
			SOUND s = {};
			BYTE* buf = nullptr;
			UINT buf_size = 0;
			_FileIO::GetSingleton()->FileRead("test_bgm2.wav", buf_size, buf);
			WAVDecoder(buf, buf_size, s);
			delete [] buf;

			_O_Sounds::GetSingleton()->RegistGraph(s);
		}

		if(MainSystem::GetSingleton()->GetKeyboard()->KEY['W'] & 0x81){pos_y -= 0.5f;}
		if(MainSystem::GetSingleton()->GetKeyboard()->KEY['S'] & 0x81){pos_y += 0.5f;}
		if(MainSystem::GetSingleton()->GetKeyboard()->KEY['A'] & 0x81){pos_x -= 0.5f;}
		if(MainSystem::GetSingleton()->GetKeyboard()->KEY['D'] & 0x81){pos_x += 0.5f;}
		Graphic_Renderer::GetSingleton()->GetScreen(0)->view = Graphic_Renderer::SetViewMatrix({pos_x, pos_y, -10.0f},{pos_x, pos_y, 0.0f},{0.0f, -1.0f, 0.0f});
	}
};

void main(){
	CoInitializeEx(NULL, COINIT_MULTITHREADED);
	HINSTANCE hInst=GetModuleHandle(NULL);
	int CmdShow = SW_SHOW;
	WindowCreate(hInst, L"Console In Test", &CmdShow);
	Init(_INTERFACE::GRAPHIC::OpenGL);
	MainSystem::GetSingleton()->SetScreen(1280, 720);
	Graphic_Renderer::GetSingleton()->CreateScreen(
		{0,0,1280,720,
		Graphic_Renderer::SetViewMatrix({0.0f, 0.0f, -10.0f},{0.0f, 0.0f, 0.0f},{0.0f, -1.0f, 0.0f}),
		Graphic_Renderer::SetOrthoProjectionMatrix(-640.0f, 640.0f, -360.0f, 360.0f, -50.0f, 50.0f)
		//Graphic_Renderer::SetPerspectiveProjectionMatrix(1280.0f/720.0f, 3.141592f/4.0f, 1.0f, 10000.0f)
	});
	Map::GetSingleton()->CreateLayer(1);

	testWalker test;
	FPS fps;
	Selecter sel;

	MainLoop(&(MainSystem::MainLoop));
	Run();

	CoUninitialize();
	return;
}