#pragma once

#include "..\\Common\\Enum.h"
#include "..\\Common\\variable.h"

class __declspec(dllexport) _Graph{
protected:
	_GRAPH::TYPE type;
	UINT time;
	bool Loop;
	bool Auto;

public:
	_Graph() : type(_GRAPH::TYPE::STOP), time(0), Loop(false), Auto(false){}
	~_Graph(){}

	void SetLoop(bool b){Loop = b;}
	bool IsLoop(){return Loop;}

	void SetAuto(bool b){Auto = b;}
	bool IsAuto(){return Auto;}

	void Play(){type = _GRAPH::TYPE::PLAY;}
	void Stop(){time = 0; Auto = false; type = _GRAPH::TYPE::STOP;}
	void Pause(){type = _GRAPH::TYPE::PAUSE;}

	virtual void update(UINT tick) = 0;
};

template <typename T>
class _Graph_template : public _Graph{
private:
	T& target;
	struct _node{
		T value;
		_GRAPH::INTERPOLATION inter;
		UINT time;
	}*arr;
	const UINT arr_num;
	UINT cur;

public:
	_Graph_template(T& t, UINT n) : _Graph(), target(t), arr(new _node[n]), arr_num(n), cur(0){}
	~_Graph_template(){delete [] arr;}

	//_node& operator [](UINT num){return arr[num];}

	void SetNode(UINT n, T v, _GRAPH::INTERPOLATION i, UINT t){
		arr[n] = {v,i,t};
	}

	void Interpolation(T prev, T next, FLOAT weight, _GRAPH::INTERPOLATION inter){
		switch(inter){
		case _GRAPH::INTERPOLATION::POINT:
			target = prev;
			return;
		case _GRAPH::INTERPOLATION::LINEAR:
			target = prev + ((next-prev)*weight);
			return;
		case _GRAPH::INTERPOLATION::SQUARED:
			target = prev + ((next-prev)*weight*weight);
			return;
		}
		return;
	}

	void update(UINT tick){
		if(type != _GRAPH::PLAY){
			if(Auto){
				type = _GRAPH::PLAY;
			}
			else{
				return;
			}
		}
		time += tick;
		while(true){
			if(cur == arr_num-1){
				if(Loop){
					time -= arr[cur].time;
					cur = 0;
				}
				else{
					time = 0;
					target = arr[cur].value;
					cur = 0;
					return;
				}
			}
			if(time < arr[cur+1].time){
				FLOAT w = (FLOAT)(time - arr[cur].time)/(FLOAT)(arr[cur+1].time - arr[cur].time);
				return Interpolation(arr[cur].value, arr[cur+1].value, w, arr[cur].inter);
			}
			++cur;
		}
	}
};

template <class T>
class _Graph_function : public _Graph{
private:
	T* target;
	struct _node{
		void (T::*func)();
		UINT time;
	}*arr;
	const UINT arr_num;
	UINT cur;

public:
	_Graph_function(T* t, UINT n) : _Graph(), target(t), arr(new _node[n]), arr_num(n), cur(0){}
	~_Graph_function(){delete [] arr;}

	//_node& operator [](UINT num){return arr[num];}

	void SetNode(UINT n, void (T::*f)(), UINT t){
		arr[n] = {f,t};
	}

	void update(UINT tick){
		if(type != _GRAPH::TYPE::PLAY){
			if(Auto){
				type = _GRAPH::TYPE::PLAY;
			}
			else{
				return;
			}
		}
		time += tick;
		if(cur == arr_num){
			if(Loop){
				time -= arr[cur-1].time;
				cur = 0;
			}
			else{
				time = 0;
				cur = 0;
				return;
			}
		}
		if(arr[cur].time > time){
			(target->*(arr[cur].func))();
			++cur;
			return;
		}
	}
};

class __declspec(dllexport) ANIMATION{
private:
	void*& m_Target;
	_Graph** m_Clip;
	UINT m_MaxClip;

public:
	ANIMATION(void*& target, UINT max_clip) : m_Target(target), m_Clip(new _Graph*[max_clip]), m_MaxClip(max_clip){
		for(UINT i = 0 ; i<m_MaxClip ; ++i){
			m_Clip[i] = nullptr;
		}
	}
	~ANIMATION(){
		for(UINT i = 0 ; i<m_MaxClip ; ++i){
			if(m_Clip[i] != nullptr){
				delete m_Clip[i];
				m_Clip = nullptr;
			}
		}
		delete [] m_Clip;
		m_Clip = nullptr;
	}

	_Graph*& operator [] (UINT i){return m_Clip[i];}
	UINT GetNumber(){return m_MaxClip;}
	void update(UINT tick){
		for(UINT i = 0 ; i<m_MaxClip ; ++i){
			if(m_Clip[i] != nullptr){(m_Clip[i])->update(tick);}
		}
	};
};
