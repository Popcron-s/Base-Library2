#pragma once

#include "..\\Common\\variable.h"
#include "..\\Common\\Tree.h"

#include "..\\BaseLibrary\\Map.h"
#include "..\\BaseLibrary\\Object.h"
#include "..\\BaseLibrary\\Renderer.h"

void MatrixWriter(MATRIX4x4 mat){
	std::cout<< mat._11 << " / " << mat._12 << " / " << mat._13 << " / " << mat._14 <<std::endl;
	std::cout<< mat._21 << " / " << mat._22 << " / " << mat._23 << " / " << mat._24 <<std::endl;
	std::cout<< mat._31 << " / " << mat._32 << " / " << mat._33 << " / " << mat._34 <<std::endl;
	std::cout<< mat._41 << " / " << mat._42 << " / " << mat._43 << " / " << mat._44 <<std::endl;
}

class objWalker{
private:
	ROOT_OBJECT* m_pRoot;
	bool m_alter;
	INT m_count;

public:
	objWalker() : m_alter(false), m_count(50){
		//init();
	}
	objWalker(FLOAT3 rot){
		init();
		m_pRoot->rotation = rot;
		m_pRoot->world = Graphic_Renderer::SetWorldMatrix(m_pRoot->position, m_pRoot->rotation, m_pRoot->scale);

		RENDER_OBJECT& temp = ((BTree<RENDER_OBJECT>*)m_pRoot->graphic_root)->GetData();
		temp.world = Graphic_Renderer::SetWorldMatrix(temp.position, temp.rotation, temp.scale, m_pRoot->world);

		MatrixWriter(m_pRoot->world);
	}
	~objWalker(){
		if(m_pRoot != nullptr){
			delete m_pRoot;
			m_pRoot = nullptr;
		}
	}

	void init(){
		m_pRoot = new ROOT_OBJECT;
		Map::GetSingleton()->RegistObject(m_pRoot, 0);

		m_pRoot->position = {0.0f, 0.0f, 0.0f};
		m_pRoot->rotation = {0.0f, 0.0f, 0.0f};
		m_pRoot->scale = {1.0f, 1.0f, 1.0f};
		m_pRoot->world = Graphic_Renderer::SetWorldMatrix(m_pRoot->position, m_pRoot->rotation, m_pRoot->scale);

		m_pRoot->graphic_root = new BTree<RENDER_OBJECT>({});
		RENDER_OBJECT& temp = ((BTree<RENDER_OBJECT>*)m_pRoot->graphic_root)->GetData();
		temp.position = {};
		temp.rotation = {};
		temp.scale = {1.0f, 1.0f, 1.0f};
		temp.world = Graphic_Renderer::SetWorldMatrix(temp.position, temp.rotation, temp.scale, m_pRoot->world);

		temp.vtx_num = 4;
		temp.vtx = new VERTEX[4];
		temp.vtx[0] = {{-1.0f,-1.0f,0.0f,1.0f},{1.0f,1.0f,1.0f,1.0f},{0.0f,0.0f,1.0f},{0.0f,0.0f}};
		temp.vtx[1] = {{ 1.0f,-1.0f,0.0f,1.0f},{0.0f,1.0f,1.0f,1.0f},{0.0f,0.0f,1.0f},{1.0f,0.0f}};
		temp.vtx[2] = {{-1.0f, 1.0f,0.0f,1.0f},{1.0f,0.0f,1.0f,1.0f},{0.0f,0.0f,1.0f},{0.0f,1.0f}};
		temp.vtx[3] = {{ 1.0f, 1.0f,0.0f,1.0f},{1.0f,1.0f,0.0f,1.0f},{0.0f,0.0f,1.0f},{1.0f,1.0f}};

		temp.indexed = nullptr;
		temp.material = (MATERIAL*)1;

		((BTree<RENDER_OBJECT>*)m_pRoot->graphic_root)->CreateLeftNode({});
		((BTree<RENDER_OBJECT>*)m_pRoot->graphic_root)->CreateRightNode({});

		RENDER_OBJECT& temp2 = ((BTree<RENDER_OBJECT>*)m_pRoot->graphic_root)->GetLTree()->GetData();
		
		temp2.position = {-1.0f, -1.0f, 0.0f};
		temp2.rotation = {};
		temp2.scale = {0.5f, 1.0f, 1.0f};
		temp2.world = Graphic_Renderer::SetWorldMatrix(temp2.position, temp2.rotation, temp2.scale, temp.world);

		temp2.vtx_num = 4;
		temp2.vtx = new VERTEX[4];
		temp2.vtx[0] = {{-1.0f, 0.0f,0.0f,1.0f},{1.0f,1.0f,1.0f,1.0f},{0.0f,0.0f,1.0f},{0.0f,0.0f}};
		temp2.vtx[1] = {{ 1.0f, 0.0f,0.0f,1.0f},{0.0f,1.0f,1.0f,1.0f},{0.0f,0.0f,1.0f},{1.0f,0.0f}};
		temp2.vtx[2] = {{-1.0f, 2.0f,0.0f,1.0f},{1.0f,0.0f,1.0f,1.0f},{0.0f,0.0f,1.0f},{0.0f,1.0f}};
		temp2.vtx[3] = {{ 1.0f, 2.0f,0.0f,1.0f},{1.0f,1.0f,0.0f,1.0f},{0.0f,0.0f,1.0f},{1.0f,1.0f}};

		temp2.indexed = nullptr;
		temp2.material = (MATERIAL*)1;

		RENDER_OBJECT& temp3 = ((BTree<RENDER_OBJECT>*)m_pRoot->graphic_root)->GetRTree()->GetData();

		temp3.position = {1.0f, -1.0f, 0.0f};
		temp3.rotation = {};
		temp3.scale = {0.5f, 1.0f, 1.0f};
		temp3.world = Graphic_Renderer::SetWorldMatrix(temp3.position, temp3.rotation, temp3.scale, temp.world);

		temp3.vtx_num = 4;
		temp3.vtx = new VERTEX[4];
		temp3.vtx[0] = {{-1.0f, 0.0f,0.0f,1.0f},{1.0f,1.0f,1.0f,1.0f},{0.0f,0.0f,1.0f},{0.0f,0.0f}};
		temp3.vtx[1] = {{ 1.0f, 0.0f,0.0f,1.0f},{0.0f,1.0f,1.0f,1.0f},{0.0f,0.0f,1.0f},{1.0f,0.0f}};
		temp3.vtx[2] = {{-1.0f, 2.0f,0.0f,1.0f},{1.0f,0.0f,1.0f,1.0f},{0.0f,0.0f,1.0f},{0.0f,1.0f}};
		temp3.vtx[3] = {{ 1.0f, 2.0f,0.0f,1.0f},{1.0f,1.0f,0.0f,1.0f},{0.0f,0.0f,1.0f},{1.0f,1.0f}};

		temp3.indexed = nullptr;
		temp3.material = (MATERIAL*)1;
	}
	
	void update(){
		if(GetAsyncKeyState('Q') & 0x8001){m_pRoot->rotation.z -= 0.05f;}
		if(GetAsyncKeyState('E') & 0x8001){m_pRoot->rotation.z += 0.05f;}
		if(GetAsyncKeyState('W') & 0x8001){m_pRoot->position.y -= 0.5f;}
		if(GetAsyncKeyState('S') & 0x8001){m_pRoot->position.y += 0.5f;}
		if(GetAsyncKeyState('A') & 0x8001){m_pRoot->position.x -= 0.5f;}
		if(GetAsyncKeyState('D') & 0x8001){m_pRoot->position.x += 0.5f;}
		m_pRoot->world = Graphic_Renderer::SetWorldMatrix(m_pRoot->position, m_pRoot->rotation, m_pRoot->scale);

		RENDER_OBJECT& temp = ((BTree<RENDER_OBJECT>*)m_pRoot->graphic_root)->GetData();
		temp.world = Graphic_Renderer::SetWorldMatrix(temp.position, temp.rotation, temp.scale, m_pRoot->world);

		RENDER_OBJECT& temp2 = ((BTree<RENDER_OBJECT>*)m_pRoot->graphic_root)->GetLTree()->GetData();
		/*temp2.position = {-1.0f, 0.0f, 0.0f};
		temp2.rotation = {};
		temp2.scale = {0.5f, 1.0f, 1.0f};*/
		if(m_alter){temp2.rotation.z += 0.01f;}
		else{temp2.rotation.z -= 0.01f;}
		temp2.world = Graphic_Renderer::SetWorldMatrix(temp2.position, temp2.rotation, temp2.scale, temp.world);

		RENDER_OBJECT& temp3 = ((BTree<RENDER_OBJECT>*)m_pRoot->graphic_root)->GetRTree()->GetData();
		/*temp3.position = {1.0f, 0.0f, 0.0f};
		temp3.rotation = {};
		temp3.scale = {0.5f, 1.0f, 1.0f};*/
		if(m_alter){temp3.rotation.z -= 0.01f;}
		else{temp3.rotation.z += 0.01f;}
		temp3.world = Graphic_Renderer::SetWorldMatrix(temp3.position, temp3.rotation, temp3.scale, temp.world);

		if(m_count > 100){m_alter = !m_alter; m_count -= 100;}
		else{++m_count;}
	}
};