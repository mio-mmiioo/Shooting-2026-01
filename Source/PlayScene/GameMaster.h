#pragma once
#include "../MyLibrary/Object3D.h"

namespace GameMaster
{
	void Init();
	void Update();
	void Draw();
	void Release();

	bool IsBulletHit(VECTOR3 startPosition, VECTOR3 endPosition);
	void CheckSetPosition(Object3D* obj, float* velocityY, float distanceR);
}
