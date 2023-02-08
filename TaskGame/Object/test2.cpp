#include "test2.h"
#include"FieldInformation.h"
#include"Field.h"

namespace
{
	int kStage[10][20];
	
	int kStartingX = 4;
	int kStartingY = 2;
	int kEndX = 10;
	int kEndY = 8;
}

test2::test2()
{
	int Stage[10][20] = {
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,2,2,2,2,2,2,2,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,2,1,1,3,3,3,2,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,2,1,1,1,2,2,2,2,0,0,0,0,0,0,0,0,0},
		{0,0,2,2,2,4,1,1,1,1,2,0,0,0,0,0,0,0,0,0},
		{0,0,2,1,1,1,2,4,2,1,2,0,0,0,0,0,0,0,0,0},
		{0,0,2,1,4,1,2,1,1,1,2,0,0,0,0,0,0,0,0,0},
		{0,0,2,1,1,1,2,1,1,1,2,0,0,0,0,0,0,0,0,0},
		{0,0,2,2,2,2,2,2,2,2,2,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	};


	for (int x = 0; x < Field::kFieldX; x++)		//仮で壁の追加
	{
		for (int y = 0; y < Field::kFieldY; y++)		//仮で壁の追加
		{
			kStage[y][x] = Stage[y][x];
		}
	}
	//for (int x = 0; x < Field::kFieldX; x++)		//仮で壁の追加
	//{
	//	for (int y = 0; y < Field::kFieldY; y++)		//仮で壁の追加
	//	{
	//		kStage[y][x] = Field::empty;
	//	}
	//}
	//for (int x = kStartingX; x < kEndX; x++)		//仮で壁の追加
	//{
	//	for (int y = kStartingY; y < kEndY; y++)		//仮で壁の追加
	//	{
	//		kStage[y][x] = Field::ground;
	//	}
	//}
	//for (int x = kStartingX - 1; x < kEndX + 1; x++)		//仮で壁の追加
	//{
	//		kStage[kStartingY - 1][x] = Field::wall;
	//		kStage[kEndY][x] = Field::wall;
	//}
	//for (int y = kStartingY - 1; y < kEndY; y++)		//仮で壁の追加
	//{
	//		kStage[y][kStartingX - 1] = Field::wall;
	//		kStage[y][kEndX] = Field::wall;
	//}
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
	//kStage[5][5] = Field::storage;	//仮の置き場所
	//kStage[5][6] = Field::box;	//仮の置き場所

	FieldInit();
}

void test2::FieldInit()
{
	m_Information->FieldInfo(kStage);
}