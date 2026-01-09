#pragma once

namespace Observer
{
	void Init();
	void Release();

	void AddScore(int addScore);
	void EnemyKilled();
	int GetEnemyKillled();
	int GetScore();
}
