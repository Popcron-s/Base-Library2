#pragma once

#include "..\\Common\\Enum.h"
#include "..\\Common\\List.h"
#include "..\\Common\\variable.h"

enum class JOINT_NAME : UINT{
	NONE = 0x00000000,
	SKEL = 0x01000000,
	SKEL_HEAD = 0x01000001,
	SKEL_NECK,
	SKEL_BODY1,
	SKEL_BODY2,
	SKEL_LARM1,
	SKEL_LARM2,
	SKEL_LHAND,
	SKEL_RARM1,
	SKEL_RARM2,
	SKEL_RHAND,
	SKEL_LLEG1,
	SKEL_LLEG2,
	SKEL_LFOOT,
	SKEL_RLEG1,
	SKEL_RLEG2,
	SKEL_RFOOT,
	SKEL_WEAPONE,
	SKIN,
	SKIN_HAIR,
	SKIN_FACE,
	SKIN_TWEAR,
	SKIN_BWEAR,
	SKIN_GLOVE,
	SKIN_SHOES,
	SKIN_WEAPONE
};

struct JOINT{
	JOINT_NAME name;
	//축, 위치, 방향, 크기
	VECTOR3 pos, rot, scl;
	MATRIX4x4 world;
	//JOINT* parent;
};
