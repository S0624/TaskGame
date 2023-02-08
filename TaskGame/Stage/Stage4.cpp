#include "Stage4.h"
#include"../Object/Field.h"
#include"../Object/FieldInformation.h"

namespace
{
	int kStage[10][20];

	int kStartingX = 4;
	int kStartingY = 2;
	int kEndX = 10;
	int kEndY = 8;
}


Stage4::Stage4()
{
	int Stage[10][20] = {
	{0,0,0,0,2,2,2,2,2,2,2,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,2,1,1,1,1,1,2,2,2,0,0,0,0,0,0,0},
	{0,0,0,2,2,4,2,2,2,1,1,1,2,0,0,0,0,0,0,0},
	{0,0,0,2,1,1,1,4,1,1,4,1,2,0,0,0,0,0,0,0},
	{0,0,0,2,1,3,3,2,1,4,1,2,2,0,0,0,0,0,0,0},
	{0,0,0,2,2,3,3,2,1,1,1,2,0,0,0,0,0,0,0,0},
	{0,0,0,0,2,2,2,2,2,2,2,2,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	};
	

	for (int x = 0; x < Field::kFieldX; x++)		//‰¼‚Å•Ç‚Ì’Ç‰Á
	{
		for (int y = 0; y < Field::kFieldY; y++)		//‰¼‚Å•Ç‚Ì’Ç‰Á
		{
			kStage[y][x] = Stage[y][x];
		}
	}


	FieldInit();
}

void Stage4::FieldInit()
{
	m_Information->FieldInfo(kStage);
}
