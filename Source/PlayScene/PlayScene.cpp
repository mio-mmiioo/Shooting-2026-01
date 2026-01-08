#include "PlayScene.h"
#include "../MyLibrary/Input.h"
#include "../MyLibrary/Color.h"

#include "Camera.h"
#include "Player.h"
#include "Stage/WayInfo.h"

PlayScene::PlayScene()
{
	new Player(VECTOR3(0, 0, 0), 0, 10);
	new Camera();
	WayInfo::Init();
}

PlayScene::~PlayScene()
{
}

void PlayScene::Update()
{
	if (Input::IsKeyDown("next")) {
		SceneManager::ChangeScene("RESULT");
	}
}

void PlayScene::Draw()
{
	WayInfo::WayDraw();
	DrawString(0, 0, "PLAY SCENE", Color::TEXT);
}
