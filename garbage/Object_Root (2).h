#pragma once

#include "..\\Common\\Enum.h"
#include "..\\Common\\Tree.h"
#include "..\\Common\\List.h"
#include "..\\Common\\variable.h"

#include "Object_Base.h"
#include "Object_Graphic.h"
#include "Object_Physics.h"
#include "Object_Sound.h"

class Root : public baseObject{
private:
	BTree<RENDER_OBJECT>* m_g_root;	//Graphic Root
	//Collision Box Root
	//Sound List
	List<Animation_Graph>* m_a_List;//Animation Set

public:
	_OBJECT::TYPE GetType(){return _OBJECT::Root;}
	void render(){}

	void GetObjectArray(_OBJECT::TYPE type, void** arr, UINT& range){
		if(arr == nullptr){return;}
		if((*arr) != nullptr){
			delete [] (*arr);
			(*arr) = nullptr;
		}
		switch(type){
		case _OBJECT::Mesh:
			range = m_g_root->GetNumber();
			(*arr) = new RENDER_OBJECT[range];
			m_g_root->Inorder((RENDER_OBJECT*)(*arr));
			return;
		default:
			return;
		}
	}
	UINT GetNumber(_OBJECT::TYPE type){
		switch(type){
		case _OBJECT::Mesh:
			return m_g_root->GetNumber();
		default:
			return 0;
		}
	}
};