#include "Enemy.h"
#include "../../../ImGui/imgui.h"
#include "../../MyLibrary/Observer.h"
#include "../GameMaster.h"
#include "../Collision.h"
#include <assert.h>

namespace ENEMY
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
	const int ADD_SCORE = 100;

	// 開発時のみ使用
	const float DIRECTION_LENGTH = 100.0f;
	const float POS_LIST_R = 50.0f;
	const int POS_LIST_DIV_NUM = 50;
}

Enemy::Enemy(const VECTOR3& position, float ang, int hp)
{
	objectNumber_ = OBJECT_SORT::OBJ_CHARA;
	transform_.position_ = position;
	hModel_ = MV1LoadModel("data/model/enemy.mv1");
	assert(hModel_ > 0);
	hitModel_ = MV1LoadModel("data/model/enemy_c.mv1");
	assert(hitModel_ > 0);

	hp_ = hp;

	time_ = 0.0f;
	gravity_ = ENEMY::G;
	distanceR_ = ENEMY::DISTANCE_R;

	transform_.scale_ = transform_.scale_ * 100.0f;

	transform_.MakeLocalMatrix();
	MV1SetMatrix(hitModel_, transform_.GetLocalMatrix());
	MV1SetupCollInfo(hitModel_);

	rotateSpeed_ = ENEMY::ROTATE_SPEED;
	moveSpeed_ = ENEMY::MOVE_SPEED;
	
	Collision::AddObject(this);
}

Enemy::~Enemy()
{
}

void Enemy::Update()
{
	if (hp_ <= 0)
	{
		DestroyMe();
		Observer::AddScore(ENEMY::ADD_SCORE);
		return;
	}

	DevelopmentInput();

	GameMaster::CheckSetPosition(this, &velocityY_, distanceR_);

	// 位置情報の更新
	transform_.MakeLocalMatrix();
	MV1SetMatrix(hModel_, transform_.GetLocalMatrix());
	MV1RefreshCollInfo(hModel_);
}

void Enemy::Draw()
{
	Object3D::Draw();
}

void Enemy::DevelopmentInput()
{
	{
		Transform t = transform_;

		ImGui::Begin("Enemy");
		ImGui::Text("position");
		float p[3] = { t.position_.x, t.position_.y, t.position_.z };
		ImGui::SliderFloat3("position", p, 0.0f, 10000.0f);

		ImGui::Text("rotation");
		float r[3] = { t.rotation_.x, t.rotation_.y, t.rotation_.z };
		ImGui::SliderFloat3("rotation", r, -DX_PI_F, DX_PI_F);

		ImGui::Text("scale");
		float s[3] = { t.scale_.x, t.scale_.y, t.scale_.z };
		ImGui::SliderFloat3("scale", s, -DX_PI_F, DX_PI_F);

		ImGui::End();

		transform_.position_ = VECTOR3(p[0], p[1], p[2]);
		transform_.rotation_ = VECTOR3(r[0], r[1], r[2]);
		transform_.scale_ = VECTOR3(s[0], s[1], s[2]);
	}
}
