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
	new Stage(8); // 建物だけのステージ

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
	if (CanShoot::CheckHitObject(startPosition, endPosition, &hit) == true)
	{
		return true;
	}
	return false;
}
