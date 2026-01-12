#pragma once
#include "../../MyLibrary/Object3D.h"

namespace Enemy
{
	enum E_SORT {
		TOUHU,
		MAX_E_SORT
	};

	enum E_STATE {
		STAY,
		WALK,
		ATTACK,
		MAX_STATE
	};

	void DevelopmentInput(Transform& t); // ŠJ”­‚Ì‚İg—p‚·‚é“ü—Íˆ—
	void CreateEnemy(int enemyNumber, const std::string& fileName, 
		const VECTOR3& position, const VECTOR3& rotation, const VECTOR3& scale, int hp, int score);
};

