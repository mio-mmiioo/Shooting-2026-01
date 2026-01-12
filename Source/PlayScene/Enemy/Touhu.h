#pragma once
#include "../../MyLibrary/Object3D.h"
#include "Enemy.h"

class Touhu : public Object3D
{
public:
	Touhu(const std::string& fileName, const VECTOR3& position, const VECTOR3& rotation, const VECTOR3& scale, int hp, int score);
	~Touhu();
	void Update() override;
	void Draw() override;

private:
	Enemy::E_STATE state_; // ó‘Ô
	bool isArrive_; // “’…‚µ‚½‚© true¨“’…‚µ‚½
};
