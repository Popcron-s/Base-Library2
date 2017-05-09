#pragma once

#include "..\\Common\\variable.h"
#include "Object.h"

bool MeshReader(BYTE* buf, UINT& pos, MESH& mesh){
	mesh.vtx_num = (buf[pos+0]<<24) | (buf[pos+1]<<16) | (buf[pos+2]<<8) | buf[pos+3];
	if(mesh.vtx_num == 0){return false;}
	pos += 4;
	mesh.vtx = new VERTEX[mesh.vtx_num];
	for(UINT i = 0 ; i<mesh.vtx_num ; ++i){
		VERTEX* t_vtx = (VERTEX*)&(buf[pos]);
		mesh.vtx[i] = *t_vtx;
		pos += sizeof(VERTEX);
	}
	UINT idx_num = (buf[pos]<<24) | (buf[pos+1]<<16) | (buf[pos+2]<<8) | buf[pos+3];
	if(idx_num != 0){
		//additional request
	}
	else{mesh.indexed = nullptr;}
	mesh.material = nullptr;
	return true;
}

bool SkeletalReader(BYTE* buf, UINT& pos, SKELETAL& skel){
	UINT node_num = (buf[pos+0]<<24) | (buf[pos+1]<<16) | (buf[pos+2]<<8) | buf[pos+3];
	pos += 4;
	if(node_num == 0){return false;}
	
	for(UINT i = 0 ; i<node_num ; ++i){
		UINT dir_count = (buf[pos+0]<<24) | (buf[pos+1]<<16) | (buf[pos+2]<<8) | buf[pos+3];
		pos += 4;
		if(dir_count == 0){skel.skeletal.CreateRoot({});}
		WLTree<JOINT>::searcher scr = skel.skeletal.Begin();
		for(UINT j = 0 ; j<dir_count ; ++j){
			BYTE num = buf[pos++];
			bool dir = (num & 0x80)>>7;
			num &= 0x7F;
			if(j == (dir_count-1)){
				DIR d = LEFT;
				if(dir){d = RIGHT;}
				skel.skeletal.Create(scr, d, {}, num);
			}
			if(!dir){scr.Left(num);}
			else{scr.Right(num);}
		}
		VECTOR3* v3 = (VECTOR3*)&(buf[pos]);
		scr->pos = *v3; pos += 12;
		v3 = (VECTOR3*)&(buf[pos]);
		scr->rot = *v3; pos += 12;
		v3 = (VECTOR3*)&(buf[pos]);
		scr->scl = *v3; pos += 12;
		MeshReader(buf, pos, scr->mesh);
	}

	return true;
}

bool MeshDecoder(BYTE* buf, UINT size, OBJECT* target_obj){
	UINT pos = 0;
	if(buf == nullptr){return false;}
	if(buf[pos] != 'P' || buf[pos+1] != 'M'){return false;}
	pos += 2;
	UINT type = buf[pos++];
	if(type == 0){return false;}
	if(type & 0x01){
		if(target_obj->GetMesh() == nullptr){
			target_obj->SetMesh(new MESH);
		}
		if(!MeshReader(buf, pos, *(target_obj->GetMesh()))){
			delete target_obj->GetMesh();
			target_obj->SetMesh(nullptr);
			return false;
		}
	}
	if(type & 0x02){
		if(target_obj->GetSkeletal() == nullptr){
			target_obj->SetSkeletal(new SKELETAL);
		}
		if(!SkeletalReader(buf, pos, *(target_obj->GetSkeletal()))){
			delete target_obj->GetSkeletal();
			target_obj->SetSkeletal(nullptr);
			return false;
		}
	}

	return true;
}