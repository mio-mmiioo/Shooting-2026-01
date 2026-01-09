#pragma once
#include "../../MyLibrary/Object3D.h"

class Stage : public Object3D
{
public:
	Stage(int number = 0);
	~Stage();

private:
	void ReadMappingData(std::string filename);
};


