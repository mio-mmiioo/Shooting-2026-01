#pragma once
#include "../MyLibrary/Object3D.h"
#include "Gun.h"

class Camera;
class HP;

struct image
{
	int hImage;		// 画像のハンドル
	int halfWidth;	// 画像の半分の横幅
	int halfHeight; // 画像の半分の縦幅
};

class Player : public Object3D
{
public:
	Player(const VECTOR3& position, int hp);
	~Player() override;
	void Update() override;
	void Draw() override;
	void AddHp(int add) override;

	bool GetIsAttack() { return isAttack_; } // プレイヤーが攻撃をしているか true→攻撃している
	int GetAttackPower(); // 銃弾一発の攻撃力を返す
	int GetHP() { return hp_; } // hpを返す
	HP* HP_;

private:
	void DevelopmentInput();					// 開発時のみ使用
	void SetAimingImage(image& i, std::string path);	// 画像のセット

	Camera* camera_;
	Gun* gun_;
	

	int mouseX_;				// マウスのx座標
	int mouseY_;				// マウスのy座標
	VECTOR3 wPointerPosition_;	// スクリーン座標の照準をワールド座標に変換したものを代入する変数
	VECTOR3 startPosition_;		// 銃の軌道の始点

	GUN::TYPE currentGun_; // 現在の銃の種類
	bool isHit_;	// 銃弾が当たるか true→当たる
	bool isAttack_; // 攻撃（発砲）しているか

	// 照準の画像関連
	image aiming_;		// 照準の画像
	image hitAiming_;	// 照準が何かにあたるときの画像
	image reload_;		// リロードの画像


};

