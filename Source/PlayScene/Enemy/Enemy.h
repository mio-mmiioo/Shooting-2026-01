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

	struct E_DATA {
		float gravity;					// 重力
		float moveSpeed;				// 移動速度
		float rotateSpeed;				// 回転速度
		float distanceR;				// 当たり判定の半径
		float distanceCurrentAndGo;		// 現在地と目的地の距離 この距離より小さい場合、次の目的地を探す
		float distanceThisAndPlayer;	// 自身とプレイヤーの距離 この距離の範囲内の場合、攻撃状態などになる 
	};

	void Init(); // 初期化
	void SetEnemyData(std::string name, float* gravity, float* moveSpeed, float* rotateSpeed, float* distanceR); // dataの初期化

	void DevelopmentInput(Transform& t); // 開発時のみ使用する入力処理
	VECTOR3 GetMoveToPlayerPosition(VECTOR3 position); // プレイヤーの方へ移動する
	void CreateEnemy(int enemyNumber, const std::string& fileName, const Transform& t, int hp, int score);

	// 状態の更新処理
	void StayUpdate(int sortNumber, VECTOR3 ePosition, E_STATE* state, E_STATE nextState);
	void WalkUpdate(int sortNumber, bool* isArrive, 
		VECTOR3* goPosition, VECTOR3* ePosition, 
		E_STATE* state, E_STATE nextState);

};

