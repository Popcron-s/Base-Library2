#pragma once

#include "..\\Common\\variable.h"
#include "Object.h"

bool MeshWriter(BYTE*& buf, UINT& size, MESH mesh){
	size = 0;
	if(buf != nullptr){
		delete [] buf;
		buf = nullptr;
	}

	size += 4; //vtx_num;
	size += 52*(mesh.vtx_num);	//vtx
	if(mesh.indexed != nullptr){
		size += 4;
		size += 12*(mesh.indexed->m_num);
	}

	buf = new BYTE[size];

	UINT pos = 0;

	buf[pos++] = (mesh.vtx_num>>24) & 0xFF;
	buf[pos++] = (mesh.vtx_num>>16) & 0xFF;
	buf[pos++] = (mesh.vtx_num>>8) & 0xFF;
	buf[pos++] = mesh.vtx_num & 0xFF;

	for(UINT i = 0 ; i<mesh.vtx_num ; ++i){
		BYTE* t = (BYTE*)&(mesh.vtx[i]);
		for(UINT j = 0 ; j<52 ; ++j){buf[pos++] = t[j];}
	}

	if(mesh.indexed != nullptr){
		buf[pos++] = (mesh.indexed->m_num>>24) & 0xFF;
		buf[pos++] = (mesh.indexed->m_num>>16) & 0xFF;
		buf[pos++] = (mesh.indexed->m_num>>8) & 0xFF;
		buf[pos++] = mesh.indexed->m_num & 0xFF;
		for(UINT i = 0 ; i<mesh.indexed->m_num ; ++i){
			BYTE* t = (BYTE*)&(mesh.indexed->node[i]);
			for(UINT j = 0 ; j<12 ; ++j){buf[pos++] = t[j];}
		}
	}

	return true;
}

bool SkeletalWriter(BYTE*& buf, UINT& size, SKELETAL skel){
	size = 0;
	if(buf != nullptr){
		delete [] buf;
		buf = nullptr;
	}

	UINT node_num = skel.skeletal.GetNumber();
	size += node_num;
	WLTree<JOINT>::iterator iter = skel.skeletal.Begin();
	for(++iter ; !iter.isLast() ; ++iter){
		WLTree<JOINT>::searcher scr = iter;
		size += 4;
		while(true){
			void* tp = scr;
			scr.Prev(); 
			if(tp == scr){break;}
			++size;
		}
		BYTE* t = nullptr;
		UINT ts = 0;
		MeshWriter(t, ts, iter->mesh);
		size += ts+36;
		if(t != nullptr){delete [] t;}
	}

	buf = new BYTE[size];

	UINT pos = 0;

	buf[pos++] = (node_num>>24) & 0xFF;
	buf[pos++] = (node_num>>16) & 0xFF;
	buf[pos++] = (node_num>>8) & 0xFF;
	buf[pos++] = node_num & 0xFF;
	WLTree<JOINT>::iterator iter2 = skel.skeletal.Begin();
	for(++iter2 ; !iter2.isLast() ; ++iter2){
		WLTree<JOINT>::searcher scr = iter2;
		UINT level = scr.GetLevel();
		buf[pos++] = (level>>24) & 0xFF;
		buf[pos++] = (level>>16) & 0xFF;
		buf[pos++] = (level>>8) & 0xFF;
		buf[pos++] = level & 0xFF;
		for(UINT i = 0 ; i<level ; ++i){
			void* tp = scr;
			scr.Prev();
			UINT num = 0;
			for(UINT j = 0 ; j<scr.GetRightNum() ; ++j){
				scr.Right(j);
				if(tp == scr){num = j; num |= 0x80; break;}
				scr.Prev();
			}
			if(num == 0){
				for(UINT j = 0 ; j<scr.GetLeftNum() ; ++j){
					scr.Left(j);
					if(tp == scr){num = j; break;}
					scr.Prev();
				}
			}
			scr.Prev();
			buf[pos+(scr.GetLevel())] = num;
		}
		pos += level;

		
		BYTE* t = (BYTE*)&(iter2->pos);
		for(UINT i = 0 ; i<12 ; ++i){buf[pos++] = t[i];}
		t = (BYTE*)&(iter2->rot);
		for(UINT i = 0 ; i<12 ; ++i){buf[pos++] = t[i];}
		t = (BYTE*)&(iter2->scl);
		for(UINT i = 0 ; i<12 ; ++i){buf[pos++] = t[i];}
		
		t = nullptr;
		UINT ts = 0;
		MeshWriter(t, ts, iter2->mesh);
		for(UINT i = 0 ; i<ts ; ++i){
			buf[pos++] = t[i];
		}
		if(t != nullptr){delete [] t;}
	}

	return true;
}

bool MeshEncoder(BYTE*& buf, UINT& size, OBJECT* obj){
	if(buf != nullptr){
		delete [] buf;
		buf = nullptr;
	}
	size = 0;
	if(obj->GetMesh() == nullptr && obj->GetSkeletal() == nullptr){
		return false;
	}

	//Mesh buf
	BYTE* mbuf = nullptr;
	UINT msize = 0;

	//skel buf
	BYTE* sbuf = nullptr;
	UINT ssize = 0;

	if(obj->GetMesh() != nullptr){
		if(!MeshWriter(mbuf, msize, *(obj->GetMesh()))){
			if(mbuf != nullptr){delete [] mbuf;}
			return false;
		}
	}
	if(obj->GetSkeletal() != nullptr){
		if(!SkeletalWriter(sbuf, ssize, *(obj->GetSkeletal()))){
			if(mbuf != nullptr){delete [] mbuf;}
			if(sbuf != nullptr){delete [] sbuf;}
			return false;
		}
	}

	size = 3+msize+ssize;
	if(size == 3){
		size = 0; 
		if(mbuf != nullptr){delete [] mbuf;}
		if(sbuf != nullptr){delete [] sbuf;}
		return false;
	}

	buf = new BYTE[size];
	buf[0] = 'P'; buf[1] = 'M';
	buf[2] = 0;

	UINT pos = 3;
	if(mbuf != nullptr){
		buf[2] |= 0x01;
		for(UINT i = 0 ; i<msize ; ++i){buf[pos++] = mbuf[i];}
	}
	if(sbuf != nullptr){
		buf[2] |= 0x02;
		for(UINT i = 0 ; i<ssize ; ++i){buf[pos++] = sbuf[i];}
	}

	if(mbuf != nullptr){delete [] mbuf;}
	if(sbuf != nullptr){delete [] sbuf;}

	if(pos != size){
		delete [] buf;
		buf = nullptr;
		size = 0;
		return false;
	}

	return true;
}