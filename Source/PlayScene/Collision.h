#pragma once
#include "../MyLibrary/Object3D.h"

namespace Collision
{
	void AddObject(Object3D* obj);
	bool CheckHitObject(VECTOR3 pos1, VECTOR3 pos2, VECTOR3* hit);
	void AttackedObject(int num);
	void SetOnGround(Object3D* obj, float* time);
}

