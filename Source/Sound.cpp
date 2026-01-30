#include "Sound.h"
#include "DxLib.h"

namespace Sound
{
	void InitSE(); // se‰¹Œ¹‚Ì‰Šú‰»

	std::map <std::string, int> se; // se‰¹Œ¹‚Ìƒf[ƒ^

}

void Sound::Init()
{
	InitSE();
}

void Sound::InitSE()
{
	se["OutBullet1"] = LoadSoundMem("data/sound/outBullet1.mp3");
	se["Reload"] = LoadSoundMem("data/sound/reload.mp3");
	se["CanNotOutBullet"] = LoadSoundMem("data/sound/canNotOutBullet.mp3");
	se["AttackEnemy"] = LoadSoundMem("data/sound/attackEnemy.mp3");
	se["BreakEnemy"] = LoadSoundMem("data/sound/breakEnemy.mp3");
}
