#pragma once

#include "..\\Common\\variable.h"
#include "..\\Common\\Singleton.h"
#include "..\\Common\\List.h"

#include "Object.h"

class Layer{
private:
	List<OBJECT*> m_List;

public:
	void RegistObject(OBJECT* obj){m_List.CreateNode(obj);}
	void RemoveObject(OBJECT* obj){m_List.ReleaseNode(obj);}
	void AllRemoveObject(){m_List.AllReleaseNode();}
	
	UINT GetObjectNumber(){
		return m_List.GetNumber();
	}
	UINT GetAllObjectNumber(){
		UINT sum = 0;
		List<OBJECT*>::iterator iter = m_List.Begin();
		for( ; iter != m_List.End() ; iter.Next()){
			//sum += iter.Data()->GetNumber();
		}
		return sum;
	}

	void ObjectUpdate(){	//SetPreOrder
		List<OBJECT*>::iterator iter = m_List.Begin();
		for( ; iter != m_List.End() ; iter.Next()){
			iter.Data()->update();
		}
	}
	void GraphicRender(){	//SerPostOrder
		List<OBJECT*>::iterator iter = m_List.Begin();
		for( ; iter != m_List.End() ; iter.Next()){
			OBJECT* obj = iter.Data();
			if(obj->GetMesh() != nullptr){
				_O_Graphics::GetSingleton()->RenderObject(&(obj->GetGraphics()));
			}
			if(obj->GetSkeletal() != nullptr){
				WLTree<JOINT>::iterator t_iter = obj->GetSkeletal()->skeletal.Begin();
				t_iter.SetInOrder();
				for(++t_iter ; !t_iter.isLast() ; ++t_iter){
					_O_Graphics::GetSingleton()->RenderObject(&obj->GetGraphics(t_iter));
				}
			}
		}
	}
	void SoundRender(){

	}
	void Animation(){

	}
};

class Map : public Singleton<Map>{
private:
	Layer* layer_array;
	UINT layer_num;

public:
	Map() : layer_array(nullptr), layer_num(0){}
	~Map(){DestroyLayer();}

	void CreateLayer(UINT num){
		if(layer_array != nullptr){
			delete [] layer_array;
		}
		layer_array = new Layer[num];
		layer_num = num;
	}
	void DestroyLayer(){
		if(layer_array != nullptr){
			delete [] layer_array;
			layer_array = nullptr;
			layer_num = 0;
		}
	}

	Layer& GetLayer(UINT i){return layer_array[i];}
	UINT GetLayerNumber(){return layer_num;}

	void RegistObject(OBJECT* obj, UINT layer){
		if(layer >= layer_num){return;}
		layer_array[layer].RegistObject(obj);
	}
	void RemoveObject(OBJECT* obj, UINT layer){
		if(layer >= layer_num){return;}
		layer_array[layer].RemoveObject(obj);
	}
	void AllRemoveobject(UINT layer){
		if(layer >= layer_num){return;}
		layer_array[layer].AllRemoveObject();
	}
	
	UINT GetObjectNumber(UINT layer){
		return layer_array[layer].GetObjectNumber();
	}
	UINT GetObjectNumber(){
		UINT sum = 0;
		for(UINT i = 0 ; i<layer_num ; ++i){
			sum += layer_array[i].GetObjectNumber();
		}
		return sum;
	}
	UINT GetAllObjectNumber(UINT layer){
		return layer_array[layer].GetObjectNumber();
	}
	UINT GetAllObjectNumber(){
		UINT sum = 0;
		for(UINT i = 0 ; i<layer_num ; ++i){
			sum += layer_array[i].GetAllObjectNumber();
		}
		return sum;
	}
};