#pragma once
#include "../../MyLibrary/Object3D.h"

class StageObject : public Object3D
{
public:
	StageObject(const std::string& fileName, const VECTOR3& position, const VECTOR3& rotation, const VECTOR3& scale, int hp);
	~StageObject();

	void Update() override;

private:
	bool isDestructible_; // âÛÇÍÇÈÇ‡ÇÃÇ© trueÅ®âÛÇÍÇÈ
};
