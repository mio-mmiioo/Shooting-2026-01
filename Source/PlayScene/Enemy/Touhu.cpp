#include "Touhu.h"
#include "../../MyLibrary/Observer.h"
#include "../GameMaster.h"
#include "../Collision.h"
#include <assert.h>

namespace TOUHU
{
	const float G = 9.8f;
	VECTOR3 SIZE = { 50.0f, 200.0f, 50.0f }; // hitModelのサイズ

	const float MOVE_SPEED = 3.0f;
	const float ROTATE_SPEED = 3.0f;
	const float DISTANCE_R = 50.0f;

	VECTOR3 headshotPos = { 0.0f, 170.0f, 0.0f };
	float headshotR = 25.0f;
	int headshotBonus = 2;

	// 攻撃関連
	const float ATTACK_TIME = 6.0f;
	const int ATTACK_POWER = 2;
	
	// 開発時のみ使用
	const float DIRECTION_LENGTH = 100.0f;
	const float POS_LIST_R = 50.0f;
	const int POS_LIST_DIV_NUM = 50;
}

Touhu::Touhu(const std::string& fileName, const VECTOR3& position, const VECTOR3& rotation, const VECTOR3& scale, int hp, int score)
{
	const std::string folder = "data/model/";
	hModel_ = MV1LoadModel((folder + fileName + ".mv1").c_str());
	assert(hModel_ > 0);
	hitModel_ = MV1LoadModel((folder + fileName + "_c.mv1").c_str());
	assert(hitModel_ > 0);

	transform_.position_ = position;
	transform_.rotation_ = rotation;
	transform_.scale_ = scale;
	hp_ = hp;
	score_ = score;

	time_ = 0.0f;
	gravity_ = TOUHU::G;
	distanceR_ = TOUHU::DISTANCE_R;


	transform_.MakeLocalMatrix();
	MV1SetMatrix(hitModel_, transform_.GetLocalMatrix());
	MV1SetupCollInfo(hitModel_);

	rotateSpeed_ = TOUHU::ROTATE_SPEED;
	moveSpeed_ = TOUHU::MOVE_SPEED;

	Collision::AddObject(this);

	objectNumber_ = OBJECT_SORT::OBJ_CHARA;
}

Touhu::~Touhu()
{
}

void Touhu::Update()
{
	// 体力が0の場合の処理
	if (hp_ <= 0)
	{
		DestroyMe();
		Observer::AddScore(score_);
		return;
	}

	Enemy::DevelopmentInput(transform_);

	GameMaster::CheckSetPosition(this, &velocityY_, distanceR_);

	// 位置情報の更新
	transform_.MakeLocalMatrix();
	MV1SetMatrix(hitModel_, transform_.GetLocalMatrix());
	MV1RefreshCollInfo(hitModel_);
}

void Touhu::Draw()
{
	Object3D::Draw();
}
