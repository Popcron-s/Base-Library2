#pragma once

#include "Object_Base.h"

class Sound : public baseObject{
protected:

public:
	virtual _OBJECT::TYPE GetType(){return _OBJECT::Sound;}
};

class Animation : public baseObject{
protected:
	List<Animation_Graph>* m_List;

public:
	virtual _OBJECT::TYPE GetType(){return _OBJECT::Animation;}
};