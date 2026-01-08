#include "Player.h"
#include <assert.h>
#include "../MyLibrary/Input.h"

namespace PLAYER
{
	VECTOR3 G = { 0, 9.8, 0 };	// 重力
	float ROTATE_SPEED = 3.0f;	// 回転速度
	float MOVE_SPEED = 5.0f;	// 移動速度

	const VECTOR3 CAPSULE_POS1 = { 0.0f,  50.0f, 0.0f };
	const VECTOR3 CAPSULE_POS2 = { 0.0f, 150.0f, 0.0f };
	const float DISTANCE_R = 50.0f;

	// 開発時のみ
	const float DIRECTION_LENGTH = 100.0f;
}

Player::Player(const VECTOR3& position, float ang, int hp)
{
	transform_.position_ = position;
	hModel_ = MV1LoadModel("data/model/player.mv1");
	assert(hModel_ > 0);
	hitModel_ = MV1LoadModel("data/model/player_c.mv1");
	assert(hitModel_ > 0);

	MV1SetupCollInfo(hModel_);
	MV1SetMatrix(hModel_, transform_.GetLocalMatrix());
	MV1RefreshCollInfo(hModel_);

	rotateSpeed_ = PLAYER::ROTATE_SPEED;
	moveSpeed_ = PLAYER::MOVE_SPEED;
}

Player::~Player()
{
}

void Player::Update()
{
	DevelopmentInput();
}

void Player::Draw()
{
	Object3D::Draw();
}

void Player::DevelopmentInput()
{
	// 入力回転
	{
		if (Input::IsKeyKeepDown("rotateRight"))
		{
			transform_.rotation_.y += rotateSpeed_ * DegToRad;
		}
		if (Input::IsKeyKeepDown("rotateLeft"))
		{
			transform_.rotation_.y -= rotateSpeed_ * DegToRad;
		}
	}

	// 入力移動
	{
		VECTOR3 velocity;// 移動ベクトル　velocity→進行方向
		velocity = VECTOR3(0, 0, 1) * moveSpeed_ * MGetRotY(transform_.rotation_.y);//移動方向書いた後、移動距離、回転行列

		if (Input::IsKeyKeepDown("moveFront"))
		{
			transform_.position_ += velocity;
		}
		else if (Input::IsKeyKeepDown("moveBack"))
		{
			transform_.position_ -= velocity;
		}
	}
}
