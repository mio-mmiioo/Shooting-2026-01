#include "Player.h"
#include <assert.h>
#include "../MyLibrary/Input.h"
#include "../MyLibrary/Color.h"
#include "Camera.h"
#include "GameMaster.h"

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
	objectNumber_ = OBJECT_SORT::OBJ_PLAYER;
	transform_.position_ = position;
	hModel_ = MV1LoadModel("data/model/player.mv1");
	assert(hModel_ > 0);
	hitModel_ = MV1LoadModel("data/model/player_c.mv1");
	assert(hitModel_ > 0);
	
	transform_.MakeLocalMatrix();
	MV1SetupCollInfo(hModel_);

	// 照準(aiming)
	SetImage(aiming_, "data/image/pointer1.png");
	SetImage(hitAiming_, "data/image/pointer2.png");
	SetImage(reload_, "data/image/reload.png");

	rotateSpeed_ = PLAYER::ROTATE_SPEED;
	moveSpeed_ = PLAYER::MOVE_SPEED;
	camera_ = FindGameObject<Camera>();

	SetDrawOrder(-100);
}

Player::~Player()
{
}

void Player::Update()
{
	GetMousePoint(&mouseX_, &mouseY_);

	// 移動処理
	DevelopmentInput();

	// 銃弾の当たり判定
	{
		VECTOR ScreenPosition = { (float)mouseX_, (float)mouseY_, 1.0f };
		wPointerPosition_ = ConvScreenPosToWorldPos(ScreenPosition);
		startPosition_ = transform_.position_ + LOOK_HEIGHT;
		if (GameMaster::IsBulletHit(startPosition_, wPointerPosition_) == true)
		{
			isHit_ = true;
		}
		else
		{
			isHit_ = false;
		}
	}

	// 位置情報の更新
	transform_.MakeLocalMatrix();
	MV1SetMatrix(hModel_, transform_.GetLocalMatrix());
	MV1RefreshCollInfo(hModel_);

	camera_->SetPlayerPosition(transform_);
}

void Player::Draw()
{
	Object3D::Draw();

	// 向いてる方向を示す　これカメラ変更しなくなったら消すこと
	VECTOR3 addPlayerHeight = LOOK_HEIGHT * transform_.GetRotationMatrix();
	DrawLine3D(transform_.position_ + addPlayerHeight, transform_.position_ + addPlayerHeight + VECTOR3(0, 0, 1) * PLAYER::DIRECTION_LENGTH * transform_.GetRotationMatrix(), Color::WHITE);

	// 2Dの描画

	// 照準の描画
	if (isHit_ == true)
	{
		DrawGraph(mouseX_ - hitAiming_.halfWidth, mouseY_ - hitAiming_.halfHeight, hitAiming_.hImage, TRUE); // Actorに当たる
	}
	else
	{
		DrawGraph(mouseX_ - aiming_.halfWidth, mouseY_ - aiming_.halfHeight, aiming_.hImage, TRUE); // 標準
	}
}

// 開発時のみ使用
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

void Player::SetImage(image& i, std::string path)
{
	i.hImage = LoadGraph(path.c_str());
	assert(i.hImage > 0);
	GetGraphSize(i.hImage, &i.halfWidth, &i.halfHeight);
	i.halfWidth = i.halfWidth / 2;
	i.halfHeight = i.halfHeight / 2;
}
