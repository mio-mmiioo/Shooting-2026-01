#include "GameMaster.h"
#include "Player.h"
#include "Stage/Stage.h"
#include "Stage/WayInfo.h"

#include "CanShoot.h"

namespace GameMaster
{
	Player* player = nullptr;
}

void GameMaster::Init()
{
	WayInfo::Init();
	new Stage(2); // 建物だけのステージ

}

void GameMaster::Update()
{
	player = FindGameObject<Player>();
}

void GameMaster::Draw()
{
	WayInfo::WayDraw();
}

void GameMaster::Release()
{
}

bool GameMaster::IsBulletHit(VECTOR3 startPosition, VECTOR3 endPosition)
{
	// 敵、破壊可能オブジェクトにあたるならtrueを返す
	VECTOR3 hit;
	Object3D obj;
	if (CanShoot::CheckHitObject(startPosition, endPosition, &hit, &obj) == false)
	{
		return false;
	}
	else
	{
		int checkNum = obj.GetObjectNumber();
		if (checkNum == OBJECT_SORT::OBJ_OBJECT || checkNum == OBJECT_SORT::OBJ_PLAYER)
		{
			return false;
		}
	}
	return true;
}
