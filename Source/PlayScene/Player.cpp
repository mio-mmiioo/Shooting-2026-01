#include "Player.h"
#include <assert.h>
#include "../../ImGui/imgui.h"
#include "../MyLibrary/Input.h"
#include "../MyLibrary/Light.h"
#include "../MyLibrary/Color.h"
#include "Camera.h"
#include "GameMaster.h"

namespace PLAYER
{
	const float G = 0.05;	// 重力
	float ROTATE_SPEED = 3.0f;	// 回転速度
	float MOVE_SPEED = 5.0f;	// 移動速度

	const VECTOR3 CAPSULE_POS1 = { 0.0f,  50.0f, 0.0f };
	const VECTOR3 CAPSULE_POS2 = { 0.0f, 150.0f, 0.0f };
	const float DISTANCE_R = 100.0f;

	// 開発時のみ
	const float DIRECTION_LENGTH = 100.0f;
}

Player::Player(const VECTOR3& position, int hp)
{
	objectNumber_ = OBJECT_SORT::OBJ_PLAYER;
	transform_.position_ = position;
	hp_ = hp;
	hModel_ = MV1LoadModel("data/model/player.mv1");
	assert(hModel_ > 0);
	hitModel_ = MV1LoadModel("data/model/player_c.mv1");
	assert(hitModel_ > 0);

	time_ = 0.0f;
	gravity_ = PLAYER::G;
	distanceR_ = PLAYER::DISTANCE_R;
	
	transform_.MakeLocalMatrix();
	MV1SetupCollInfo(hModel_);

	// 照準(aiming)
	SetImage(aiming_, "data/image/pointer1.png");
	SetImage(hitAiming_, "data/image/pointer2.png");
	SetImage(reload_, "data/image/reload.png");

	rotateSpeed_ = PLAYER::ROTATE_SPEED;
	moveSpeed_ = PLAYER::MOVE_SPEED;
	
	camera_ = FindGameObject<Camera>();
	gun_ = new Gun();
	currentGun_ = GUN::TYPE::HAND; 
	gun_->SetGunType(currentGun_); // 使用する銃の種類をセット

	isHit_ = false;
	isAttack_ = false;

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

	// 銃弾関連
	{
		// リロード
		if (Input::IsKeyDown("reload"))
		{
			gun_->ReloadBullet();
		}

		// 発砲
		if (Input::IsKeyDown("outBullet"))
		{
			if (gun_->OutBullet() == true)
			{
				isAttack_ = true;
			}
		}
		else
		{
			isAttack_ = false;
		}
	}

	// 照準の当たり判定
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

	GameMaster::CheckSetPosition(this, &velocityY_, distanceR_, gravity_);

	camera_->SetPlayerPosition(transform_);
	Light::SetPosition(transform_.position_);

	// 位置情報の更新
	transform_.MakeLocalMatrix();
	MV1SetMatrix(hModel_, transform_.GetLocalMatrix());
	MV1RefreshCollInfo(hModel_);
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

	if (gun_->GetReloadTimer() > 0)
	{
		float rate = (gun_->GetReloadTime() - gun_->GetReloadTimer()) / gun_->GetReloadTime() * 100; // (maxの時間 - 残り時間) / maxの時間 * 100 = 〇〇%
		DrawCircleGauge(mouseX_, mouseY_, 100.0, reload_.hImage, rate);
	}
}

int Player::GetAttackPower()
{
	if (isAttack_ == true)
	{
		return gun_->GetAttack();
	}

	return 0; // ±ゼロを返す
}

// 開発時のみ使用
void Player::DevelopmentInput()
{
	{
		Transform t = transform_;

		ImGui::Begin("Player");
		ImGui::Text("position");
		float p[3] = { t.position_.x, t.position_.y, t.position_.z };
		ImGui::SliderFloat3("position", p, 0.0f, 10000.0f);

		ImGui::Text("rotation");
		float r[3] = { t.rotation_.x, t.rotation_.y, t.rotation_.z };
		ImGui::SliderFloat3("rotation", r, -DX_PI_F, DX_PI_F);

		ImGui::Text("HP:%d", hp_);

		ImGui::End();

		transform_.position_ = VECTOR3(p[0], p[1], p[2]);
		transform_.rotation_ = VECTOR3(r[0], r[1], r[2]);
	}


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
