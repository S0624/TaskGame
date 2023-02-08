#include "Stage2.h"
#include"../Object/Field.h"
#include"../Object/FieldInformation.h"

namespace
{
	int kStage[10][20];

	int kStartingX = 4;
	int kStartingY = 2;
	constexpr int kIndexX = 9;
	constexpr int kIndexY = 2;
}


Stage2::Stage2()
{
	int Stage[10][20] = {
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,2,2,2,2,2,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,2,1,1,1,2,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,2,1,4,4,2,0,2,2,2,0,0,0,0,0},
		{0,0,0,0,0,0,2,1,4,1,2,0,2,3,2,0,0,0,0,0},
		{0,0,0,0,0,0,2,2,2,1,2,2,2,3,2,0,0,0,0,0},
		{0,0,0,0,0,0,0,2,2,1,1,1,1,3,2,0,0,0,0,0},
		{0,0,0,0,0,0,0,2,1,1,1,2,1,1,2,0,0,0,0,0},
		{0,0,0,0,0,0,0,2,1,1,1,2,2,2,2,0,0,0,0,0},
		{0,0,0,0,0,0,0,2,2,2,2,2,0,0,0,0,0,0,0,0},
	};


	for (int x = 0; x < Field::kFieldX; x++)		//���ŕǂ̒ǉ�
	{
		for (int y = 0; y < Field::kFieldY; y++)		//���ŕǂ̒ǉ�
		{
			kStage[y][x] = Stage[y][x];
		}
	}

	FieldInit();
}

void Stage2::FieldInit()
{
	m_Information->FieldInfo(kStage);
	m_Information->PlayerInfo(kIndexX, kIndexY);
}
