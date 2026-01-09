#include "Observer.h"

namespace Observer {
	int enemyKilledCounter = 0;
	int score = 0;
}

void Observer::Init()
{
}

void Observer::Release()
{
	enemyKilledCounter = 0;
	score = 0;
}

void Observer::AddScore(int addScore)
{
	score += addScore;
}

void Observer::EnemyKilled()
{
	enemyKilledCounter += 1;
}

int Observer::GetEnemyKillled()
{
	return enemyKilledCounter;
}

int Observer::GetScore()
{
	return score;
}