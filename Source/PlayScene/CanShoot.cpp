#include "CanShoot.h"

namespace CanShoot
{
	std::list<Object3D*> canShootObjectList_;
}

void CanShoot::AddCanShootObject(Object3D* obj)
{
	canShootObjectList_.push_back(obj);
}

bool CanShoot::CheckHitObject(VECTOR3 pos1, VECTOR3 pos2, VECTOR3* hit, Object3D* object)
{
	bool found = false;
	VECTOR3 now;
	float nowVal = ((VECTOR3)(pos2 - pos1)).Size();

	for (Object3D* obj : canShootObjectList_)
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
				object = obj;
			}
		}
	}
	if (hit != nullptr)
	{
		*hit = now;
	}
	return found;
}
