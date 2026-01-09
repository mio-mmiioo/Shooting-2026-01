#include "GameMaster.h"
#include "Player.h"
#include "Stage/Stage.h"
#include "Stage/WayInfo.h"

#include "../MyLibrary/Light.h"
//#include "../MyLibrary/Shadow.h"

#include "CanShoot.h"

namespace GameMaster
{
	// 開発時のみ仕様
	const float CHECK_FRONT_LENGTH = 100.0f;
	const float CHECK_BACK_LENGTH = 100.0f;


	Player* player = nullptr;
	Stage* stage = nullptr;
}

void GameMaster::Init()
{
	WayInfo::Init();
	new Stage(8); // 建物だけのステージ
	Light::Init();
	//Shadow::Init(); // Stageの後に処理する
}

void GameMaster::Update()
{
	Light::Update();
	player = FindGameObject<Player>();
	stage = FindGameObject<Stage>();

	if (player->GetIsAttack() == true)
	{
		CanShoot::AttackedObject(-player->GetAttackPower());
	}
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

// 現在地が地面や壁にめり込んでいる場合、押し返す
void GameMaster::CheckSetPosition(Transform& transform, float time, VECTOR3 gravity, float distanceR)
{
	stage->SetOnGround(transform.position_, time, gravity); // ステージの位置を確認し、空中に浮いていないか確認する 浮いていたら重力をかける
	VECTOR3 front = transform.position_ + VECTOR3(0, 0, 1) * CHECK_FRONT_LENGTH * MGetRotY(transform.rotation_.y);
	VECTOR3 back = transform.position_ + VECTOR3(0, 0, 1) * -CHECK_BACK_LENGTH * MGetRotY(transform.rotation_.y);
	stage->CheckPush(transform.position_, front, distanceR); // ステージへのめり込みを確認する(前方)
	stage->CheckPush(transform.position_, back, distanceR);  // ステージへのめり込みを確認する(後方)
}
