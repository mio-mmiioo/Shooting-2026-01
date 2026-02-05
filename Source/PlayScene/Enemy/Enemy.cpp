#include "Enemy.h"
#include "../../../ImGui/imgui.h"
#include "../../MyLibrary/Observer.h"
#include "../../MyLibrary/Object3D.h"
#include "../../MyLibrary/CsvReader.h"
#include "../Stage/WayInfo.h"
#include "../GameMaster.h"
#include "../Collision.h"
#include <assert.h>
#include <map>
#include <string>
// 各敵のヘッダーファイル
#include "Stone.h"
#include "Touhu.h"

namespace Enemy
{
	// csvに書かれているデータ
	enum E_DATA_NUM {
		NAME,			// 名前
		SORT,			// 種類
		GRAVITY,		// 重力
		MOVE_SPEED,		// 移動速度
		ROTATE_SPEED,	// 回転速度
		DISTANCE_R,		// 当たり判定の半径
		DISTANCE1,		// 現在地と目的地の距離
		DISTANCE2,		// 自身とプレイヤーの距離
		MAX_E_DATA_NUM
	};

	void ReadEnemyData();
	std::string SetCurrentEnemySort(int sortNumber);

	std::map<std::string, E_DATA> data;
}

void Enemy::Init()
{
	ReadEnemyData();
}

void Enemy::SetEnemyData(std::string name, float* gravity, float* moveSpeed, float* rotateSpeed, float* distanceR)
{
	E_DATA d = data[name];
	*gravity = d.gravity;
	*moveSpeed = d.moveSpeed;
	*rotateSpeed = d.rotateSpeed;
	*distanceR = d.distanceR;
}

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

VECTOR3 Enemy::GetMoveToPlayerPosition(VECTOR3 position)
{
	VECTOR3 playerPosition = GameMaster::GetPlayerPosition();
	VECTOR3 ret = WayInfo::GetShortestWayPosition(position, playerPosition);
	return ret;
}

void Enemy::CreateEnemy(int enemyNumber, const std::string& fileName, const Transform& t, int hp, int score)
{
	switch (enemyNumber)
	{
	case E_SORT::STONE:
		new Stone(fileName, t, hp, score);
		break;
	case E_SORT::TOUHU:
		new Touhu(fileName, t, hp, score);
		break;
	}
}

// プレイヤーとの距離が開きすぎると、状態が遷移する
void Enemy::StayUpdate(int sortNumber, VECTOR3 ePosition, E_STATE* state, E_STATE nextState)
{
	std::string str = SetCurrentEnemySort(sortNumber);
	VECTOR3 pPosition = GameMaster::GetPlayerPosition();
	float distance = data[str].distanceThisAndPlayer;
	if (Collision::CheckDistanceVertexAndVertex(ePosition, pPosition, distance) == false)
	{
		*state = nextState;
	}
}

// プレイヤーまでを最短経路で移動する
void Enemy::WalkUpdate(int sortNumber, bool* isArrive, VECTOR3* goPosition, VECTOR3* ePosition, E_STATE* state, E_STATE nextState)
{
	std::string name = SetCurrentEnemySort(sortNumber);

	if (*isArrive == true)
	{
		*goPosition = Enemy::GetMoveToPlayerPosition(*ePosition);
		*isArrive = false;
	}
	else
	{
		if (Collision::CheckDistanceVertexAndVertex(*ePosition, *goPosition, data[name].distanceCurrentAndGo) == true)
		{
			*isArrive = true;
		}
	}

	if (Collision::CheckDistanceVertexAndVertex(*ePosition, GameMaster::GetPlayerPosition(), data[name].distanceThisAndPlayer))
	{
		*state = nextState;
	}
}

void Enemy::ReadEnemyData()
{
	CsvReader* csv = new CsvReader("data/enemy.csv");
	for (int line = 1; line < csv->GetLines(); line++)
	{
		std::string name = csv->GetString(line, E_DATA_NUM::NAME);
		int sortNumber = csv->GetInt(line, E_DATA_NUM::SORT);
		E_DATA enemy;
		enemy.gravity = csv->GetFloat(line, E_DATA_NUM::GRAVITY);
		enemy.moveSpeed = csv->GetFloat(line, E_DATA_NUM::MOVE_SPEED);
		enemy.rotateSpeed = csv->GetFloat(line, E_DATA_NUM::ROTATE_SPEED);
		enemy.distanceR = csv->GetFloat(line, E_DATA_NUM::DISTANCE_R);
		enemy.distanceCurrentAndGo = csv->GetFloat(line, E_DATA_NUM::DISTANCE1);
		enemy.distanceThisAndPlayer = csv->GetFloat(line, E_DATA_NUM::DISTANCE2);
		
		data[name] = enemy;
	}
}

std::string Enemy::SetCurrentEnemySort(int sortNumber)
{
	std::string ret;
	switch (sortNumber)
	{
	case E_SORT::STONE:
		ret = "stone";
		break;
	case E_SORT::TOUHU:
		ret = "touhu";
		break;
	}
	return ret;
}
