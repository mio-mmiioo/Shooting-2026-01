#pragma once
#include "../../MyLibrary/Object3D.h"
#include "Enemy.h"

class Touhu : public Object3D
{
public:
	Touhu(const std::string& fileName, const Transform& t, int hp, int score);
	~Touhu();
	void Update() override;
	void Draw() override;

private:
	void DevelopmentInput(); // 開発時のみ使用する処理
	void UpdateStay(); // Stay状態の時の更新処理
	void UpdateWalk(); // Move状態の時の更新処理
	Enemy::E_STATE state_; // 状態
	bool isArrive_; // 到着したか true→到着した
	VECTOR3 goPosition_; // 次に向かう場所
};
