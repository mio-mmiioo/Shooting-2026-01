#pragma once
#include "../../MyLibrary/Object3D.h"

namespace Enemy
{
	enum E_SORT {
		TOUHU_1,
		TOUHU_2,
		MAX_E_SORT
	};

	enum E_STATE {
		STAY,
		WALK,
		ATTACK,
		MAX_STATE
	};

	void DevelopmentInput(Transform& t); // ŠJ”­‚Ì‚İg—p‚·‚é“ü—Íˆ—
	void CreateEnemy(int enemyNumber, const std::string& fileName, const Transform& t, int hp, int score);
};

