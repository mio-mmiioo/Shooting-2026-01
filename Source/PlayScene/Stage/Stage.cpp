#include "Stage.h"
#include <assert.h>
#include "../../MyLibrary/CsvReader.h"
#include "../Player.h"
#include "../Enemy/Enemy.h"
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
	VECTOR3 position;
	VECTOR3 rotation;
	VECTOR3 scale;
	int hp;
	int score;
	char file[STAGE::DATA_SIZE];

	for (int line = 0; line < csv->GetLines(); line++) {
		int sortNumber = csv->GetInt(line, DATA_NUM::OBJECT);
		
		position.x = csv->GetFloat(line, DATA_NUM::POSITION_X);
		position.y = csv->GetFloat(line, DATA_NUM::POSITION_Y);
		position.z = csv->GetFloat(line, DATA_NUM::POSITION_Z);
		hp = csv->GetInt(line, DATA_NUM::HP);

		if (sortNumber == OBJECT_SORT::OBJ_PLAYER) {
			new Player(position, hp);
		}
		else
		{
			rotation.x = csv->GetFloat(line, DATA_NUM::ROTATION_X);
			rotation.y = csv->GetFloat(line, DATA_NUM::ROTATION_Y);
			rotation.z = csv->GetFloat(line, DATA_NUM::ROTATION_Z);
			scale.x = csv->GetFloat(line, DATA_NUM::SCALE_X);
			scale.y = csv->GetFloat(line, DATA_NUM::SCALE_Y);
			scale.z = csv->GetFloat(line, DATA_NUM::SCALE_Z);
			score = csv->GetInt(line, DATA_NUM::SCORE);

			if (sortNumber == OBJECT_SORT::OBJ_CHARA) {
				int enemyNumber = csv->GetInt(line, DATA_NUM::NUMBER);
				sprintf_s<STAGE::DATA_SIZE>(file, "Enemy%03d", csv->GetInt(line, DATA_NUM::NUMBER));
				Enemy::CreateEnemy(enemyNumber, file, position, rotation, scale, hp, score);
			}
			else if (sortNumber == OBJECT_SORT::OBJ_OBJECT) {
				sprintf_s<STAGE::DATA_SIZE>(file, "Stage_Obj%03d", csv->GetInt(line, DATA_NUM::NUMBER));
				StageObject* obj = new StageObject(file, position, rotation, scale, hp, score);
			}
		}
	}
	delete csv;
}
