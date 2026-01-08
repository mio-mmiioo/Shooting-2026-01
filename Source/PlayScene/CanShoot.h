#pragma once
#include "../MyLibrary/Object3D.h"

namespace CanShoot
{
	void AddCanShootObject(Object3D* obj);
	bool CheckHitObject(VECTOR3 pos1, VECTOR3 pos2, VECTOR3* hit);
}

