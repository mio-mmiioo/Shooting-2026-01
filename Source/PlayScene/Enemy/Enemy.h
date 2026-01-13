#pragma once
#include "../../MyLibrary/Object3D.h"

namespace Enemy
{
	enum E_SORT {
		STONE,
		TOUHU,
		MAX_E_SORT
	};

	enum E_STATE {
		STAY,
		WALK,
		ATTACK,
		MAX_STATE
	};

	void DevelopmentInput(Transform& t); // 開発時のみ使用する入力処理
	VECTOR3 GetMoveToPlayerPosition(VECTOR3 position); // プレイヤーの方へ移動する
	void CreateEnemy(int enemyNumber, const std::string& fileName, const Transform& t, int hp, int score);
};

