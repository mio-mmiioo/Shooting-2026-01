#pragma once
#include "../MyLibrary/Object3D.h"

class Camera;

class Player : public Object3D
{
public:
	Player(const VECTOR3& position, float ang, int hp);
	~Player() override;
	void Update() override;
	void Draw() override;

private:
	void DevelopmentInput();

	Camera* camera_;
};

