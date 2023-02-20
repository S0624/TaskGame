#include "Stage10.h"
#include"../Object/Field.h"
#include"../Object/FieldInformation.h"

namespace
{
	int kStage[Field::kFieldY][Field::kFieldX];

	constexpr int kIndexX = 4;
	constexpr int kIndexY = 9;
}


Stage10::Stage10()
{
	int Stage[Field::kFieldY][Field::kFieldX] = {
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,2,2,2,2,2,2,0,0,2,2,2,2,2,0,0,0,0,0},
		{0,0,2,1,1,1,1,2,2,2,2,1,1,1,2,0,0,0,0,0},
		{0,0,2,1,4,1,1,1,4,1,1,1,2,1,2,0,0,0,0,0},
		{0,0,2,2,1,1,2,1,2,2,2,1,4,1,2,0,0,0,0,0},
		{0,0,0,2,4,4,1,1,2,2,2,4,2,1,2,0,0,0,0,0},
		{0,0,2,2,1,1,1,2,1,1,3,3,3,1,2,0,0,0,0,0},
		{0,0,2,1,1,2,1,4,1,1,4,3,3,3,2,0,0,0,0,0},
		{0,0,2,1,1,2,2,2,2,2,3,3,2,2,2,0,0,0,0,0},
		{0,0,2,1,1,2,0,0,0,2,2,2,2,0,0,0,0,0,0,0},
		{0,0,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
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

void Stage10::FieldInit()
{
	m_Information->FieldInfo(kStage);
	m_Information->PlayerInfo(kIndexX, kIndexY);
}
