#include "Stage.h"
#include <assert.h>
#include "../../MyLibrary/CsvReader.h"
#include "../Player.h"

namespace STAGE
{
	const float CHECK_ONGROUND_LENGTH = 500.0f;
	const int DATA_SIZE = 16;

	enum SORT_NUM
	{
		PLAYER,
		CHARA,
		OBJ,
		OBJ_D,
		MAX_OBJ
	};
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

void Stage::SetOnGround(VECTOR3& pos, float& time, VECTOR3 Gravity)
{
	VECTOR3 hit;
	VECTOR3 pos1 = pos + VECTOR3(0,  STAGE::CHECK_ONGROUND_LENGTH, 0);
	VECTOR3 pos2 = pos - VECTOR3(0, -STAGE::CHECK_ONGROUND_LENGTH, 0);
	if (CollideLine(pos1, pos2, &hit))
	{
		pos = hit;
		if (time != 0)
		{
			time = 0;
		}
		else
		{
			// 空中だから、落下処理
			time += Time::DeltaTime();
			pos -= Gravity * time * time;
		}
	}
}

void Stage::CheckPush(VECTOR3& pos1, VECTOR3 pos2, float minDistance)
{
	VECTOR3 hit;
	VECTOR3 direction; 
	if (CollideLine(pos1, pos2, &hit)) // 正面にオブジェクトがある
	{
		if (VSize(pos1 - hit) < minDistance) // めり込んでいる→めり込んでいる距離押し返す
		{
			direction = VNorm(hit - pos1); // 押し返す方向のベクトル
			pos1 -= direction * (minDistance - VSize(pos1 - hit)); // ( 押し返す方向 ) * ( 押し返したい距離 )
		}
	}
}

void Stage::ReadMappingData(std::string filename)
{
	const std::string folder = "data/stage/";
	CsvReader* csv = new CsvReader(folder + filename + ".csv");
	for (int line = 0; line < csv->GetLines(); line++) {
		int sortNumber = csv->GetInt(line, 0);
		//if (sortNumber == STAGE::SORT_NUM::PLAYER) {
		//	VECTOR pos = VECTOR3(csv->GetFloat(line, 2), csv->GetFloat(line, 3), csv->GetFloat(line, 4));
		//	float ang = csv->GetFloat(line, 5);
		//	int hp = csv->GetInt(line, 6);
		//	new Player(pos, ang, hp);
		//}
		if (sortNumber == STAGE::SORT_NUM::CHARA) {
			VECTOR pos = VECTOR3(csv->GetFloat(line, 2), csv->GetFloat(line, 3), csv->GetFloat(line, 4));
			float ang = csv->GetFloat(line, 5);
			int hp = csv->GetInt(line, 6);
			switch (csv->GetInt(line, 1)) {
			case 0:
				new Player(pos, ang, hp);
				break;
			case 1:
				//new Enemy(pos, ang, hp);
				break;
			}
		}
		else if (sortNumber == STAGE::SORT_NUM::OBJ) {
			VECTOR pos = VECTOR3(csv->GetFloat(line, 2), csv->GetFloat(line, 3), csv->GetFloat(line, 4));
			VECTOR rot = VECTOR3(csv->GetFloat(line, 5), csv->GetFloat(line, 6), csv->GetFloat(line, 7));
			VECTOR sca = VECTOR3(csv->GetFloat(line, 8), csv->GetFloat(line, 9), csv->GetFloat(line, 10));
			char file[STAGE::DATA_SIZE];
			sprintf_s<STAGE::DATA_SIZE>(file, "Stage_Obj%03d", csv->GetInt(line, 1));
			//StageObject* obj = new StageObject(file, pos, rot, sca);
		}
		else if (sortNumber == STAGE::SORT_NUM::OBJ_D) {
			VECTOR pos = VECTOR3(csv->GetFloat(line, 2), csv->GetFloat(line, 3), csv->GetFloat(line, 4));
			VECTOR rot = VECTOR3(csv->GetFloat(line, 5), csv->GetFloat(line, 6), csv->GetFloat(line, 7));
			VECTOR sca = VECTOR3(csv->GetFloat(line, 8), csv->GetFloat(line, 9), csv->GetFloat(line, 10));
			int hp = csv->GetInt(line, 11);
			char file[STAGE::DATA_SIZE];
			sprintf_s<STAGE::DATA_SIZE>(file, "Stage_Obj%03d", csv->GetInt(line, 1));
			//DestructibleObject* obj = new DestructibleObject(file, pos, rot, sca, hp);
		}
	}
	delete csv;
}
