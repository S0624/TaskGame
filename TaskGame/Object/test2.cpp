#include "test2.h"
#include"testField.h"
#include"Field.h"

namespace
{
	int kStage[10][20];
}

test2::test2()
{
	for (int x = 0; x < Field::kFieldX; x++)		//仮で壁の追加
	{
		for (int y = 0; y < Field::kFieldY; y++)		//仮で壁の追加
		{
			kStage[y][x] = Field::empty;
		}
	}
	for (int x = 4; x < 10; x++)		//仮で壁の追加
	{
		for (int y = 2; y < 8; y++)		//仮で壁の追加
		{
			kStage[y][x] = Field::ground;
		}
	}


	//for (int x = 0; x < 20; x++)		//仮で壁の追加
	//{
	//	m_stage[0][x] = Field::wall;
	//	m_stage[10 - 1][x] = Field::wall;
	//}
	//for (int y = 0; y < 10; y++)		//仮で壁の追加
	//{
	//	m_stage[y][0] = Field::wall;
	//	m_stage[y][6 - 1] = Field::wall;
	//}

	kStage[5][5] = Field::storage;	//仮の置き場所
	kStage[5][6] = Field::box;	//仮の置き場所

	
	FieldInit();
}

void test2::FieldInit()
{
	m_test->test(kStage);
}
