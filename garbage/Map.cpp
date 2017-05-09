#include "Map.h"

//Layer
/*void Layer::RegistObject(Root* obj){m_List.CreateNode(obj);}
void Layer::RemoveObject(Root* obj){m_List.ReleaseNode(obj);}
void Layer::AllRemoveObject(){m_List.AllReleaseNode();}
void Layer::GetObjectArray(_OBJECT::TYPE type, void* arr, UINT& range){
	if(arr != nullptr){
		delete [] arr;
		arr = nullptr;
	}
	UINT list_num = m_List.GetNumber();
	range = 0;
	switch(type){
	case _OBJECT::Mesh:
		//get all object mesh num
		for(UINT i = 0 ; i<list_num ; ++i){
			range += m_List.GetData(i)->GetNumber(_OBJECT::Mesh);
		}
		arr = new RENDER_OBJECT[range];
		for(UINT i = 0, j = 0 ; i<list_num ; ++i){	//added mesh
			UINT t_num = 0;
			RENDER_OBJECT* t_arr = nullptr;
			m_List.GetData(i)->GetObjectArray(_OBJECT::Mesh, t_arr, t_num);
			for(UINT k = 0 ; k<t_num ; ++k){
				((RENDER_OBJECT*)arr)[j+k] = t_arr[k];
			}
			j += t_num;
		}
		return;
	default:
		return;
	}
}
UINT Layer::GetObjectNumber(_OBJECT::TYPE type = _OBJECT::Root){
	UINT list_num = m_List.GetNumber();
	UINT sum = 0;
	switch(type){
	case _OBJECT::Mesh:
		//get all object mesh num
		for(UINT i = 0 ; i<list_num ; ++i){
			sum += m_List.GetData(i)->GetNumber(_OBJECT::Mesh);
		}
		return sum;
	case _OBJECT::Root:
		return list_num;
	default:
		return 0;
	}
}*/

//Map
/*void Map::CreateLayer(UINT num){
	if(layer_array != nullptr){
		delete [] layer_array;
	}
	layer_array = new Layer[num];
	layer_num = num;
}
void Map::DestroyLayer(){
	if(layer_array != nullptr){
		delete [] layer_array;
		layer_array = nullptr;
		layer_num = 0;
	}
}

void Map::RegistObject(Root* obj, UINT layer){
	if(layer >= layer_num){return;}
	layer_array[layer].RegistObject(obj);
}
void Map::RemoveObject(Root* obj, UINT layer){
	if(layer >= layer_num){return;}
	layer_array[layer].RemoveObject(obj);
}
void Map::AllRemoveobject(UINT layer){
	if(layer >= layer_num){return;}
	layer_array[layer].AllRemoveObject();
}
void Map::GetObjectArray(_OBJECT::TYPE type, void* arr){
	if(arr != nullptr){
		delete [] arr;
		arr = nullptr;
	}
	UINT sum = 0;
	switch(type){
	case _OBJECT::Mesh:
		for(UINT layer = 0 ; layer<layer_num ; ++layer){
			sum += layer_array[layer].GetObjectNumber(_OBJECT::Mesh);
		}
		arr = new RENDER_OBJECT[sum];
		for(UINT layer = 0, idx = 0 ; layer<layer_num ; ++layer){
			RENDER_OBJECT* t_arr = nullptr;
			UINT t_num = 0;
			layer_array[layer].GetObjectArray(_OBJECT::Mesh, t_arr, t_num);
			for(UINT i = 0 ; i<t_num ; ++i){
				((RENDER_OBJECT*)arr)[idx+i] = t_arr[i];
			}
			delete [] t_arr;
			idx += t_num;
		}
		return;
	default:
		return;
	}
}
UINT Map::GetObjectNumber(UINT layer){
	return layer_array[layer].GetObjectNumber();
}
UINT Map::GetAllObjectNumber(){
	UINT sum = 0;
	for(UINT i = 0 ; i<layer_num ; ++i){
		sum += layer_array[i].GetObjectNumber();
	}
	return sum;
}*/