#pragma once

#include "..\\Common\\variable.h"
#include "..\\Common\\Singleton.h"

#include "Collider2D.h"

#include <iostream>

class Collision2D : public Singleton<Collision2D>{
private:
	BOX SetupBox(BOX& b){
		if(b.joint == nullptr){return b;}
		BOX check_box = {};
		check_box._1.x = (b.joint->world._11*b._1.x) + (b.joint->world._21*b._1.y) + (b.joint->world._31*b._1.z) + b.joint->world._41;
		check_box._1.y = (b.joint->world._12*b._1.x) + (b.joint->world._22*b._1.y) + (b.joint->world._32*b._1.z) + b.joint->world._42;
		check_box._1.z = (b.joint->world._13*b._1.x) + (b.joint->world._23*b._1.y) + (b.joint->world._33*b._1.z) + b.joint->world._43;
		check_box._2.x = (b.joint->world._11*b._2.x) + (b.joint->world._21*b._2.y) + (b.joint->world._31*b._2.z) + b.joint->world._41;
		check_box._2.y = (b.joint->world._12*b._2.x) + (b.joint->world._22*b._2.y) + (b.joint->world._32*b._2.z) + b.joint->world._42;
		check_box._2.z = (b.joint->world._13*b._2.x) + (b.joint->world._23*b._2.y) + (b.joint->world._33*b._2.z) + b.joint->world._43;
		check_box._3.x = (b.joint->world._11*b._3.x) + (b.joint->world._21*b._3.y) + (b.joint->world._31*b._3.z) + b.joint->world._41;
		check_box._3.y = (b.joint->world._12*b._3.x) + (b.joint->world._22*b._3.y) + (b.joint->world._32*b._3.z) + b.joint->world._42;
		check_box._3.z = (b.joint->world._13*b._3.x) + (b.joint->world._23*b._3.y) + (b.joint->world._33*b._3.z) + b.joint->world._43;
		check_box._4.x = (b.joint->world._11*b._4.x) + (b.joint->world._21*b._4.y) + (b.joint->world._31*b._4.z) + b.joint->world._41;
		check_box._4.y = (b.joint->world._12*b._4.x) + (b.joint->world._22*b._4.y) + (b.joint->world._32*b._4.z) + b.joint->world._42;
		check_box._4.z = (b.joint->world._13*b._4.x) + (b.joint->world._23*b._4.y) + (b.joint->world._33*b._4.z) + b.joint->world._43;
		return check_box;
	}
	CIRCLE SetupCircle(CIRCLE& c){
		CIRCLE check_circle = {};
		check_circle.o = {c.o.x+c.joint->world._41, c.o.y+c.joint->world._42, c.o.z+c.joint->world._43};
		check_circle.r = c.r*c.joint->scl.x;
		return check_circle;
	}
	bool OBB(BOX& base, BOX& target){	//Axis Aligned Boundary Box
		FLOAT lthSq = 0.0f;
		FLOAT lthF = 0.0f;
		FLOAT lthIn1 = 0.0f;
		FLOAT lthIn2 = 0.0f;
		LINE line = {};
		VECTOR3 CTC = {};
		VECTOR3 INN = {};
		VECTOR3 SAT = {};

		line.st = {
			base._1.x + ((base._3.x-base._1.x)/2),
			base._1.y + ((base._3.y-base._1.y)/2),
			base._1.z + ((base._3.z-base._1.z)/2)};
		line.ed = {
			target._1.x + ((target._3.x-target._1.x)/2),
			target._1.y + ((target._3.y-target._1.y)/2),
			target._1.z + ((target._3.z-target._1.z)/2)};
		CTC = {line.ed.x-line.st.x, line.ed.y-line.st.y, line.ed.z-line.st.z};

		line = {base._1, base._2}; lthSq = line.LengthSq();
		SAT = {line.ed.x-line.st.x, line.ed.y-line.st.y, line.ed.z-line.st.z};
		INN = {target._2.x-target._1.x, target._2.y-target._1.y, target._2.z-target._1.z};
		lthIn1 = (SAT.x*INN.x) + (SAT.y*INN.y) + (SAT.z*INN.z);
		INN = {target._3.x-target._2.x, target._3.y-target._2.y, target._3.z-target._2.z};
		lthIn2 = (SAT.x*INN.x) + (SAT.y*INN.y) + (SAT.z*INN.z);
		lthF = (SAT.x*CTC.x) + (SAT.y*CTC.y) + (SAT.z*CTC.z);
		lthF = (lthF>=0.0f)?lthF:-lthF;
		lthIn1 = (lthIn1>=0.0f)?lthIn1:-lthIn1;
		lthIn2 = (lthIn2>=0.0f)?lthIn2:-lthIn2;

		if(((lthSq+lthIn1+lthIn2)/2) < lthF){return false;}

		line = {base._2, base._3}; lthSq = line.LengthSq();
		SAT = {line.ed.x-line.st.x, line.ed.y-line.st.y, line.ed.z-line.st.z};
		INN = {target._2.x-target._1.x, target._2.y-target._1.y, target._2.z-target._1.z};
		lthIn1 = (SAT.x*INN.x) + (SAT.y*INN.y) + (SAT.z*INN.z);
		INN = {target._3.x-target._2.x, target._3.y-target._2.y, target._3.z-target._2.z};
		lthIn2 = (SAT.x*INN.x) + (SAT.y*INN.y) + (SAT.z*INN.z);
		lthF = (SAT.x*CTC.x) + (SAT.y*CTC.y) + (SAT.z*CTC.z);
		lthF = (lthF>=0.0f)?lthF:-lthF;
		lthIn1 = (lthIn1>=0.0f)?lthIn1:-lthIn1;
		lthIn2 = (lthIn2>=0.0f)?lthIn2:-lthIn2;

		if(((lthSq+lthIn1+lthIn2)/2) < lthF){return false;}

		line = {target._1, target._2}; lthSq = line.LengthSq();
		SAT = {line.ed.x-line.st.x, line.ed.y-line.st.y, line.ed.z-line.st.z};
		INN = {base._2.x-base._1.x, base._2.y-base._1.y, base._2.z-base._1.z};
		lthIn1 = (SAT.x*INN.x) + (SAT.y*INN.y) + (SAT.z*INN.z);
		INN = {base._3.x-base._2.x, base._3.y-base._2.y, base._3.z-base._2.z};
		lthIn2 = (SAT.x*INN.x) + (SAT.y*INN.y) + (SAT.z*INN.z);
		lthF = (SAT.x*CTC.x) + (SAT.y*CTC.y) + (SAT.z*CTC.z);
		lthF = (lthF>=0.0f)?lthF:-lthF;
		lthIn1 = (lthIn1>=0.0f)?lthIn1:-lthIn1;
		lthIn2 = (lthIn2>=0.0f)?lthIn2:-lthIn2;

		if(((lthSq+lthIn1+lthIn2)/2) < lthF){return false;}

		line = {target._2, target._3}; lthSq = line.LengthSq();
		SAT = {line.ed.x-line.st.x, line.ed.y-line.st.y, line.ed.z-line.st.z};
		INN = {base._2.x-base._1.x, base._2.y-base._1.y, base._2.z-base._1.z};
		lthIn1 = (SAT.x*INN.x) + (SAT.y*INN.y) + (SAT.z*INN.z);
		INN = {base._3.x-base._2.x, base._3.y-base._2.y, base._3.z-base._2.z};
		lthIn2 = (SAT.x*INN.x) + (SAT.y*INN.y) + (SAT.z*INN.z);
		lthF = (SAT.x*CTC.x) + (SAT.y*CTC.y) + (SAT.z*CTC.z);
		lthF = (lthF>=0.0f)?lthF:-lthF;
		lthIn1 = (lthIn1>=0.0f)?lthIn1:-lthIn1;
		lthIn2 = (lthIn2>=0.0f)?lthIn2:-lthIn2;

		if(((lthSq+lthIn1+lthIn2)/2) < lthF){return false;}

		return true;
	}

	bool BC(CIRCLE& base, CIRCLE& target){	//Boundary Circle
		LINE l = {base.o, target.o};
		FLOAT r = (base.r + target.r) * (base.r + target.r);

		if(l.LengthSq() <= r){return true;}
		else{return false;}
	}

	bool BL(FLOAT3& base, LINE& target){ //Boundary line
		return false;
	}

public:
	bool Collision(COL2D& base, COL2D& target){
		if(base.GetType() == COLLIDER2D::BOX && target.GetType() == COLLIDER2D::BOX){
			BOX b = SetupBox((BOX&)base);
			BOX t = SetupBox((BOX&)target);
			return OBB(b, t);
		}
		else if(base.GetType() == COLLIDER2D::CIRCLE && target.GetType() == COLLIDER2D::CIRCLE){
			CIRCLE b = SetupCircle((CIRCLE&)base);
			CIRCLE t = SetupCircle((CIRCLE&)target);
			return BC(b, t);
		}
		else{return false;}
	}

	bool Raycast(FLOAT x, FLOAT y, COL2D& target){	//update AABB
		if(target.GetType() == COLLIDER2D::BOX){
			BOX t = SetupBox((BOX&)target);

			LINE line = {};
			VECTOR3 CTC = {};
			FLOAT lthF = 0.0f;
			VECTOR3 SAT = {};
			FLOAT lthSq = 0.0f;

			line.st = {x, y, 0.0f};
			line.ed = {
				t._1.x + ((t._3.x-t._1.x)/2),
				t._1.y + ((t._3.y-t._1.y)/2),
				t._1.z + ((t._3.z-t._1.z)/2)};
			CTC = {line.ed.x-line.st.x, line.ed.y-line.st.y, line.ed.z-line.st.z};

			line = {t._1, t._2}; lthSq = line.LengthSq();
			SAT = {line.ed.x-line.st.x, line.ed.y-line.st.y, line.ed.z-line.st.z};
			lthF = (SAT.x*CTC.x) + (SAT.y*CTC.y) + (SAT.z*CTC.z);
			lthF = (lthF>=0.0f)?lthF:-lthF;
			if((lthSq/2) < lthF){return false;}

			line = {t._2, t._3}; lthSq = line.LengthSq();
			SAT = {line.ed.x-line.st.x, line.ed.y-line.st.y, line.ed.z-line.st.z};
			lthF = (SAT.x*CTC.x) + (SAT.y*CTC.y) + (SAT.z*CTC.z);
			lthF = (lthF>=0.0f)?lthF:-lthF;
			if((lthSq/2) < lthF){return false;}

			return true;
		}
		else if(target.GetType() == COLLIDER2D::CIRCLE){
			CIRCLE t = SetupCircle((CIRCLE&)target);
			FLOAT length = ((t.o.x-x)*(t.o.x-x)) + ((t.o.y-y)*(t.o.y-y));
			length = (length>=0.0f)?length:-length;
			if(length > (t.r*t.r)){return false;}
			else{return true;}
		}
		else{return false;}
	}

};