#pragma once

#include "Object_Base.h"

class Collider : public baseObject{
protected:
	//COLLISION::TYPE col_type;

public:
	virtual _OBJECT::TYPE GetType(){return _OBJECT::Collider;}
};