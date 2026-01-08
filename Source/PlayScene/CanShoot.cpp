#include "CanShoot.h"

namespace CanShoot
{
	std::list<Object3D*> canShootObjectList;
	Object3D* checkObject;
}

void CanShoot::AddCanShootObject(Object3D* obj)
{
	if (obj != nullptr)
	{
		canShootObjectList.push_back(obj);
	}
}

bool CanShoot::CheckHitObject(VECTOR3 pos1, VECTOR3 pos2, VECTOR3* hit)
{
	bool found = false;
	VECTOR3 now;
	float nowVal = ((VECTOR3)(pos2 - pos1)).Size();

	for (Object3D* obj : canShootObjectList)
	{
		if (obj->GetObjectNumber() != OBJECT_SORT::OBJ_PLAYER)
		{
			VECTOR3 ret;
			if (obj->Object3D::CollideLine(pos1, pos2, &ret))
			{
				found = true;
				VECTOR3 v = pos1 - ret;
				float len = v.Size();
				if (len < nowVal)
				{
					nowVal = len;
					now = ret;
					checkObject = obj;
				}
			}
		}
	}
	if (hit != nullptr)
	{
		*hit = now;
	}

	// 当たったオブジェクトの種類から、判別
	if (checkObject != nullptr)
	{
		if (checkObject->GetObjectNumber() == OBJECT_SORT::OBJ_OBJECT)
		{
			found = false;
		}
	}
	return found;
}

void CanShoot::AttackedObject(int num)
{
	checkObject->ADD_HP(num);
}
