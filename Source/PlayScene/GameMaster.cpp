#include "GameMaster.h"
#include "Player.h"
#include "Stage/Stage.h"
#include "Stage/WayInfo.h"

namespace GameMaster
{
	Player* player = nullptr;
}

void GameMaster::Init()
{
	WayInfo::Init();
	new Stage(0); // 建物だけのステージ

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
