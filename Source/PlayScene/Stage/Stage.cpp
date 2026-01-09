#include "Stage.h"
#include <assert.h>
#include "../../MyLibrary/CsvReader.h"
#include "../Player.h"
#include "StageObject.h"

namespace STAGE
{
	const float CHECK_ONGROUND_LENGTH = 500.0f;
	const int DATA_SIZE = 16;
}

Stage::Stage(int number)
{
	char filename[STAGE::DATA_SIZE];
	sprintf_s<STAGE::DATA_SIZE>(filename, "Stage%02d", number);
	ReadMappingData(filename);
}

Stage::~Stage()
{
}

void Stage::ReadMappingData(std::string filename)
{
	const std::string folder = "data/stage/";
	CsvReader* csv = new CsvReader(folder + filename + ".csv");
	for (int line = 0; line < csv->GetLines(); line++) {
		int sortNumber = csv->GetInt(line, 0);
		if (sortNumber == OBJECT_SORT::OBJ_PLAYER) {
			VECTOR pos = VECTOR3(csv->GetFloat(line, 2), csv->GetFloat(line, 3), csv->GetFloat(line, 4));
			float ang = csv->GetFloat(line, 5);
			int hp = csv->GetInt(line, 6);
			new Player(pos, ang, hp);
		}
		if (sortNumber == OBJECT_SORT::OBJ_CHARA) {
			VECTOR pos = VECTOR3(csv->GetFloat(line, 2), csv->GetFloat(line, 3), csv->GetFloat(line, 4));
			float ang = csv->GetFloat(line, 5);
			int hp = csv->GetInt(line, 6);
			switch (csv->GetInt(line, 1)) {
			case 0:
				//new Player(pos, ang, hp);
				break;
			case 1:
				//new Enemy(pos, ang, hp);
				break;
			}
		}
		else if (sortNumber == OBJECT_SORT::OBJ_OBJECT) {
			VECTOR pos = VECTOR3(csv->GetFloat(line, 2), csv->GetFloat(line, 3), csv->GetFloat(line, 4));
			VECTOR rot = VECTOR3(csv->GetFloat(line, 5), csv->GetFloat(line, 6), csv->GetFloat(line, 7));
			VECTOR sca = VECTOR3(csv->GetFloat(line, 8), csv->GetFloat(line, 9), csv->GetFloat(line, 10));
			int hp = csv->GetInt(line, 11);
			char file[STAGE::DATA_SIZE];
			sprintf_s<STAGE::DATA_SIZE>(file, "Stage_Obj%03d", csv->GetInt(line, 1));
			StageObject* obj = new StageObject(file, pos, rot, sca, hp);
		}
	}
	delete csv;
}
