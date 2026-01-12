#include "Enemy.h"
#include "../../../ImGui/imgui.h"
#include "../../MyLibrary/Observer.h"
#include "../GameMaster.h"
#include "../Collision.h"
#include <assert.h>

// 各敵のヘッダーファイル
#include "Touhu.h"

void Enemy::DevelopmentInput(Transform& t)
{
	//ImGui::Begin("Enemy");
	ImGui::Text("position");
	ImGui::InputFloat("position:x", &t.position_.x);
	ImGui::InputFloat("position:y", &t.position_.y);
	ImGui::InputFloat("position:z", &t.position_.z);

	ImGui::Text("rotation");
	ImGui::InputFloat("rotation:x", &t.rotation_.x);
	ImGui::InputFloat("rotation:y", &t.rotation_.y);
	ImGui::InputFloat("rotation:z", &t.rotation_.z);

	ImGui::Text("scale");
	ImGui::InputFloat("scale:x", &t.scale_.x);
	ImGui::InputFloat("scale:y", &t.scale_.y);
	ImGui::InputFloat("scale:z", &t.scale_.z);

	//ImGui::End();
}

void Enemy::CreateEnemy(int enemyNumber, const std::string& fileName, const Transform& t, int hp, int score)
{
	switch (enemyNumber)
	{
	case E_SORT::TOUHU_2:
		new Touhu(fileName, t, hp, score);
		break;
	}
}
