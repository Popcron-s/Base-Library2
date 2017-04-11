#pragma once

#include "variable.h"
#include "List.h"

#include <iostream>

enum DIR{
	LEFT = 0,
	RIGHT = 1
};

template <class T>
class BTree{
private:
	T data;
	UINT m_Number;

	BTree<T>* Parent;
	BTree<T>* LTree;
	BTree<T>* RTree;

private:
	void AddNumber(){++m_Number; if(Parent != nullptr){Parent->AddNumber();}}

public:
	BTree(T _data, BTree<T>* _Parent = nullptr) : 
		data(_data), Parent(_Parent), m_Number(1), LTree(nullptr), RTree(nullptr){
		if(Parent != nullptr){
			Parent->AddNumber();
		}
	}
	~BTree(){
		ReleaseLeftNode();
		ReleaseRightNode();
	}

	T& CreateLeftNode(T _data){LTree = new BTree<T>(_data, this); return LTree->GetData();}
	T& CreateRightNode(T _data){RTree = new BTree<T>(_data, this); return RTree->GetData();}
	bool ReleaseLeftNode(){if(LTree != nullptr){m_Number -= LTree->GetNumber(); delete LTree; LTree = nullptr;} return true;}
	bool ReleaseRightNode(){if(RTree != nullptr){m_Number -= RTree->GetNumber(); delete RTree; RTree = nullptr;} return true;}

	UINT GetNumber(){return m_Number;}
	T& GetData(){return data;}
	BTree<T>* GetLTree(){return LTree;}
	BTree<T>* GetRTree(){return RTree;}

	UINT Preorder(T* arr, UINT idx = 0){
		arr[idx++] = data;
		if(LTree != nullptr){idx = LTree->Preorder(arr, idx);}
		if(RTree != nullptr){idx = RTree->Preorder(arr, idx);}
		return idx;
	}	//VLR
	UINT Inorder(T* arr, UINT idx = 0){
		if(LTree != nullptr){idx = LTree->Inorder(arr, idx);}
		arr[idx++] = data;
		if(RTree != nullptr){idx = RTree->Inorder(arr, idx);}
		return idx;
	}	//LVR
	UINT Postorder(T* arr, UINT idx = 0){
		if(LTree != nullptr){idx = LTree->Postorder(arr, idx);}
		if(RTree != nullptr){idx = RTree->Postorder(arr, idx);}
		arr[idx++] = data;
		return idx;
	}	//LRV
};

template <class T>
class WLTree{
protected:
	struct node{
		T m_Data;

		node* m_pParent;
		List<node*> m_Child[2];
	}*m_pRoot;
	UINT m_Number;

public:

public:
	WLTree() : m_pRoot(nullptr), m_Number(0){}
	~WLTree(){Release(m_pRoot);}

	UINT GetNumber(){return m_Number;}

	bool CreateRoot(T data){
		if(m_pRoot != nullptr){return false;}
		m_pRoot = new node;
		m_pRoot->m_Data = data;
		m_pRoot->m_pParent = nullptr;

		m_Number = 1;
	}
	bool Create(void* prnt, DIR dir, T data, INT num = -1){
		if(prnt == nullptr){return false;}
		node* p_node = (node*)prnt;
		node* c_node = new node;
		c_node->m_Data = data;
		c_node->m_pParent = p_node;
		if(num == -1){p_node->m_Child[dir].CreateNode(c_node);}
		else{p_node->m_Child[dir].CreateNode(c_node, num);}
		++m_Number;
		return true;
	}
	bool Release(void* crnt){return false;}
	bool Release(void* prnt, DIR dir, UINT num){return false;}

	void* Begin(){return m_pRoot;}
	
	class iterator{
	private:
		node* point;
		enum{
			Pre,	//VLR
			In,		//LVR
			Post,	//LRV
			Level
		}order;
		List<node*> stack;

	public:
		iterator() : point(nullptr), order(Pre){}
		iterator(void* p) : point(nullptr), order(Pre){stack.CreateNode((node*)p);}
		~iterator(){stack.AllReleaseNode();}
		T& Data(){return point->m_Data;}

		bool isLast(){if(stack.GetNumber() == 0 && point == nullptr){return true;} else{return false;}}

		void SetPreOrder(){order = Pre;}
		void SetInOrder(){order = In;}
		void SetPostOrder(){order = Post;}
		void SetLevelOrder(){order = Level;}

		void operator =(const void*& p){this->point = p;}
		void operator ++(){
			if(stack.GetNumber() == 0){
				point = nullptr;
				return;
			}
			List<node*>::iterator iter;
			bool check = true;
			switch(order){
			case Pre:
				point = stack.GetData(0);
				stack.ReleaseNode((UINT)0);
				iter = point->m_Child[1].Begin();
				for(UINT i = 0 ; iter != point->m_Child[1].End() ; ++iter, ++i){
					stack.CreateNode(iter.Data(), i);
				}
				iter = point->m_Child[0].Begin();
				for(UINT i = 0 ; iter != point->m_Child[0].End() ; ++iter, ++i){
					stack.CreateNode(iter.Data(), i);
				}
				stack.CreateNode(point, 0);
				point = stack.GetData(0);
				stack.ReleaseNode((UINT)0);
				break;
			case In:
				check = true;
				if(point != nullptr && point->m_pParent != nullptr){
					iter = point->m_pParent->m_Child[0].Begin();
					for( ; iter != point->m_pParent->m_Child[0].End() ; ++iter){
						if(point == iter.Data()){
							check = false;
							break;
						}
					}
				}
				point = stack.GetData(0);
				stack.ReleaseNode((UINT)0);
				while(check){
					iter = point->m_Child[1].Begin();
					for(UINT i = 0 ; iter != point->m_Child[1].End() ; ++iter, ++i){
						stack.CreateNode(iter.Data(), i);
					}
					if(point->m_Child[0].GetNumber() == 0){break;}
					stack.CreateNode(point, 0);
					iter = point->m_Child[0].Begin();
					for(UINT i = 0 ; iter != point->m_Child[0].End() ; ++iter, ++i){
						stack.CreateNode(iter.Data(), i);
					}
					point = stack.GetData(0);
					stack.ReleaseNode((UINT)0);
				}
				break;
			case Post:
				break;
			case Level:
				break;
			}
		}
		//bool operator ==(const void* p){if(this->point == p){return true;} else{return false;}}
		//bool operator !=(const void* p){if(this->point != p){return true;} else{return false;}}
		operator void*(){return point;}
	};

	class searcher{
	private:
		node* point;
	public:
		searcher() : point(nullptr){}
		searcher(void* p) : point((node*)p){}
		~searcher(){}

		T& Data(){return point->m_Data;}

		void Prev(){if(point->m_pParent != nullptr){point = point->m_pParent;}}
		void Left(UINT num){if(point->m_Child[0].GetNumber() != 0){point = point->m_Child[0].GetData(num);}}
		void Right(UINT num){if(point->m_Child[1].GetNumber() != 0){point = point->m_Child[1].GetData(num);}}

		void operator =(const void*& p){this->point = p;}
		bool operator ==(const void* p){if(this->point == p){return true;} else{return false;}}
		bool operator !=(const void* p){if(this->point != p){return true;} else{return false;}}
		operator void*(){return point;}
	};
};	//Double List Tree