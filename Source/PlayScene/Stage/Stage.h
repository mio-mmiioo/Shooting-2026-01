#pragma once
#include "../../MyLibrary/Object3D.h"

class Stage : public Object3D
{
public:
	Stage(int number = 0);
	~Stage();
	struct ColliderRet
	{
		VECTOR3 VPush; // 垂直方向の押し出し
		VECTOR3 HPush; // 水平方向の押し出し
	};

	void SetOnGround(VECTOR3& pos, float& time, VECTOR3 Gravity); // 地面にモデルがめり込んでいるか確認後、正しい位置にセットする
	void CheckPush(VECTOR3& pos1, VECTOR3 pos2, float minDistance); // 最小の距離よりも2つの地点の距離が近い場合押し返す

private:
	void ReadMappingData(std::string filename);
};


