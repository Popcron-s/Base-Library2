#include <iostream>
#include "..\\Win32\\Win32_API.h"
#include "..\\Win32\\Win32_API.cpp"

#include "..\\Coder\\BMPDecoder.h"
#include "..\\Coder\\BMPEncoder.h"

#include <io.h>
#include <fcntl.h>
#include <share.h>
#include <sys\\stat.h>

#include "..\\BaseLibrary\\MainSystem.h"
#include "..\\BaseLibrary\\Map.h"
#include "..\\BaseLibrary\\Object.h"

class arm : public OBJECT{
private:

public:
	arm(FLOAT3 _pos, OBJECT* parent) : OBJECT(parent){
		init(); 
		SetPosition(_pos); 
		SetWorld();
	}
	~arm(){Destroy();}
	void init(){
		SetPosition({0.0f, 0.0f, 0.0f});
		SetRotation({0.0f, 0.0f, 0.0f});
		SetScale({0.5f, 1.0f, 1.0f});
		SetWorld();

		SetMesh(new MESH({new VERTEX[4], 4, nullptr, nullptr}));
		GetMesh()->vtx[0] = {{-1.0f,  0.0f, 0.0f, 1.0f},{0.0f, 1.0f, 1.0f, 1.0f},{0.0f, 0.0f, 0.0f},{0.0f, 0.0f}};
		GetMesh()->vtx[1] = {{ 1.0f,  0.0f, 0.0f, 1.0f},{1.0f, 0.0f, 1.0f, 1.0f},{0.0f, 0.0f, 0.0f},{1.0f, 0.0f}};
		GetMesh()->vtx[2] = {{-1.0f,  2.0f, 0.0f, 1.0f},{1.0f, 1.0f, 0.0f, 1.0f},{0.0f, 0.0f, 0.0f},{0.0f, 1.0f}};
		GetMesh()->vtx[3] = {{ 1.0f,  2.0f, 0.0f, 1.0f},{1.0f, 1.0f, 1.0f, 0.0f},{0.0f, 0.0f, 0.0f},{1.0f, 1.0f}};	
	}

	void Destroy(){
		Map::GetSingleton()->RemoveObject(this, 0);
		MESH* t_mesh = GetMesh();
		if(t_mesh != nullptr){
			if(t_mesh->vtx != nullptr){
				delete [] t_mesh->vtx; 
				t_mesh->vtx = nullptr; 
				t_mesh->vtx_num = 0;
			}
			delete t_mesh; 
			SetMesh(nullptr);
		}
	}

	void update(){}
};

class testWalker : public OBJECT{
private:
	arm *l_arm, *r_arm;
	const FLOAT pi;
	INT i;
	bool swi;

public:
	testWalker() : pi(3.141592f), i(0), swi(false){
		l_arm = nullptr; r_arm = nullptr;
		init();
	}/*
	testWalker(FLOAT3 pos = {}) : pi(3.141592f), i(0), swi(false){
		init(pos);
	}*/
	~testWalker(){Destroy();}
	void init(FLOAT3 pos = {}){
		Map::GetSingleton()->RegistObject(this, 0);
		//SetPosition(pos);
		//SetRotation({0.0f, 0.0f, 0.0f});
		//SetScale({1.0f, 1.0f, 1.0f});
		SetPosition({(FLOAT)(rand()%12)-6.0f, (FLOAT)(rand()%6)-3.0f, (FLOAT)(rand()%10)});
		SetRotation({0.0f, 0.0f, (FLOAT)(rand()%6283184)/1000000.0f});
		SetScale({(FLOAT)(rand()%5)-2.5f, (FLOAT)(rand()%5)-2.5f, 1.0f});
		SetWorld();

		SetMesh(new MESH({new VERTEX[4], 4, nullptr, nullptr}));
		GetMesh()->vtx[0] = {{-1.0f, -1.0f, 0.0f, 1.0f},{0.0f, 1.0f, 1.0f, 1.0f},{0.0f, 0.0f, 0.0f},{0.0f, 0.0f}};
		GetMesh()->vtx[1] = {{ 1.0f, -1.0f, 0.0f, 1.0f},{1.0f, 0.0f, 1.0f, 1.0f},{0.0f, 0.0f, 0.0f},{1.0f, 0.0f}};
		GetMesh()->vtx[2] = {{-1.0f,  1.0f, 0.0f, 1.0f},{1.0f, 1.0f, 0.0f, 1.0f},{0.0f, 0.0f, 0.0f},{0.0f, 1.0f}};
		GetMesh()->vtx[3] = {{ 1.0f,  1.0f, 0.0f, 1.0f},{1.0f, 1.0f, 1.0f, 0.0f},{0.0f, 0.0f, 0.0f},{1.0f, 1.0f}};	
		
		l_arm = new arm({-1.0f, -0.5f, 0.0f}, this);
		r_arm = new arm({ 1.0f, -0.5f, 0.0f}, this);
		//CreateLeftNode((OBJECT*)l_arm);
		//CreateRightNode((OBJECT*)r_arm);
	}

	void Destroy(){
		Map::GetSingleton()->RemoveObject(this, 0);
		MESH* t_mesh = GetMesh();
		if(t_mesh != nullptr){
			if(t_mesh->vtx != nullptr){
				delete [] t_mesh->vtx; 
				t_mesh->vtx = nullptr; 
				t_mesh->vtx_num = 0;
			}
			delete t_mesh; 
			SetMesh(nullptr);
		}
	}

	void update(){
		l_arm->SetRotation({0.0f, 0.0f, (pi*i)/180.0f});
		l_arm->SetWorld();

		r_arm->SetRotation({0.0f, 0.0f, (pi*(-i))/180.0f});
		r_arm->SetWorld();

		if(swi){++i;}
		else{--i;}

		if(i>45){swi = false;}
		else if(i<-45){swi = true;}
	}
};

class overloadtest : public OBJECT{
private:

public:
	overloadtest(){init();}
	~overloadtest(){Destroy();}
	void init(){
		Map::GetSingleton()->RegistObject(this, 0);
		SetPosition({0.0f, 0.0f, 0.0f});
		SetRotation({0.0f, 0.0f, 0.0f});
		SetScale({1.0f, 1.0f, 1.0f});
		SetWorld();

		UINT vtx = 5000;
		SetMesh(new MESH({new VERTEX[vtx], vtx, nullptr, nullptr}));
		for(UINT i = 0 ; i<vtx ; ++i){
			GetMesh()->vtx[i].pos = {(FLOAT)(rand()%12)-6.0f,(FLOAT)(rand()%3)-1.5f,(FLOAT)(rand()%50),1.0f};
			GetMesh()->vtx[i].diffuse = {(rand()%100)/100.0f, (rand()%100)/100.0f, (rand()%100)/100.0f, (rand()%100)/100.0f};
			GetMesh()->vtx[i].normal = {};
			GetMesh()->vtx[i].tex = {};
		}
	}
	void Destroy(){
		Map::GetSingleton()->RemoveObject(this, 0);
		MESH* t_mesh = GetMesh();
		if(t_mesh != nullptr){
			if(t_mesh->vtx != nullptr){
				delete [] t_mesh->vtx; 
				t_mesh->vtx = nullptr; 
				t_mesh->vtx_num = 0;
			}
			delete t_mesh; 
			SetMesh(nullptr);
		}
	}
	void update(){

	}
};

class mainsys : public OBJECT{
private:
	UINT i;
	overloadtest* test;
	testWalker* walker;
	UINT tick;
	const UINT rag;

public:
	mainsys() : rag(3000){
		test = nullptr;
		walker = nullptr;
		i = 0; 
		tick = rag;
		Map::GetSingleton()->RegistObject(this, 0);
	}
	~mainsys(){
		Map::GetSingleton()->RemoveObject(this, 0);
	}
	void update(){
		UINT frame = 0;
		if(MainSystem::GetSingleton()->GetTick() != 0){
			frame = 1000/MainSystem::GetSingleton()->GetTick();
		}
		tick += MainSystem::GetSingleton()->GetTick();

		/*if(test != nullptr){
			test->Destroy();
			delete [] test;
			test = nullptr;
		}
		test = new overloadtest[rand()%100+1];*/
		
		if(tick >= rag){
			if(walker != nullptr){
				walker->Destroy();
				delete [] walker;
				walker = nullptr;
			}
			walker = new testWalker[rand()%10+1];
			tick -= rag;
		}

		std::cout<< frame << " / " << i++ 
			<< " / " << Map::GetSingleton()->GetLayer(0).GetAllObjectNumber() <<std::endl;
	}
};

void main(){
	HINSTANCE hInst=GetModuleHandle(NULL);
	int CmdShow = SW_SHOW;
	WindowCreate(hInst, L"Console In Test", &CmdShow);
	Init(_INTERFACE::GRAPHIC::OpenGL);

	Graphic_Renderer::SetOrthoProjectionMatrix(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f);
	Graphic_Renderer::GetSingleton()->CreateScreen(
		{0,0,1280,720,
		Graphic_Renderer::SetViewMatrix({0.0f, 0.0f, -10.0f},{0.0f, 0.0f, 0.0f},{0.0f, -1.0f, 0.0f}),
		Graphic_Renderer::SetPerspectiveProjectionMatrix(1280.0f/720.0f, 3.141592f/4.0f, 1.0f, 10000.0f)});
	//Graphic_Renderer::GetSingleton()->CreateScreen({100,100,1000,400,{1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1},{1,0,0,0,0,1,0,0,0,0,-1,0,0,0,0,1}});
	Map::GetSingleton()->CreateLayer(1);

	mainsys m_sys;
	//testWalker* test = new testWalker;
	//overloadtest olt;
	/*
	testWalker test000 = testWalker({0.0f, 0.0f, 0.0f});
	//testWalker test001;
	testWalker test001 = testWalker({(FLOAT)(rand()%12)-6.0f,(FLOAT)(rand()%3)-1.5f,(FLOAT)(rand()%50)});
	testWalker test002 = testWalker({(FLOAT)(rand()%12)-6.0f,(FLOAT)(rand()%3)-1.5f,(FLOAT)(rand()%50)});
	testWalker test003 = testWalker({(FLOAT)(rand()%12)-6.0f,(FLOAT)(rand()%3)-1.5f,(FLOAT)(rand()%50)});
	testWalker test004 = testWalker({(FLOAT)(rand()%12)-6.0f,(FLOAT)(rand()%3)-1.5f,(FLOAT)(rand()%50)});
	testWalker test005 = testWalker({(FLOAT)(rand()%12)-6.0f,(FLOAT)(rand()%3)-1.5f,(FLOAT)(rand()%50)});
	testWalker test006 = testWalker({(FLOAT)(rand()%12)-6.0f,(FLOAT)(rand()%3)-1.5f,(FLOAT)(rand()%50)});
	testWalker test007 = testWalker({(FLOAT)(rand()%12)-6.0f,(FLOAT)(rand()%3)-1.5f,(FLOAT)(rand()%50)});
	testWalker test008 = testWalker({(FLOAT)(rand()%12)-6.0f,(FLOAT)(rand()%3)-1.5f,(FLOAT)(rand()%50)});
	testWalker test009 = testWalker({(FLOAT)(rand()%12)-6.0f,(FLOAT)(rand()%3)-1.5f,(FLOAT)(rand()%50)});
	*/
	MainLoop(&(MainSystem::Render));
	Render();

	return;
}