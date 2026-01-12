#pragma once
#include "../../MyLibrary/Object3D.h"

class Enemy : public Object3D
{
public:
	Enemy(const VECTOR3& position, float ang, int hp);
	~Enemy();
	void Update() override;
	void Draw() override;

private:
	void DevelopmentInput(); // ŠJ”­‚Ì‚İg—p‚·‚é“ü—Íˆ—
	
};

