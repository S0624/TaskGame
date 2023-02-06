#include "testField.h"
#include"Field.h"
#include"test2.h"

namespace
{
	int kStage[Field::kFieldY][Field::kFieldX];
}

testField::testField() :
	m_pField(nullptr)
{
	Init();
	
	int num = 0;
	if (num == 0)
	{
		ktest = new test2;
	}
}

void testField::Init()
{
	for (int x = 0; x < Field::kFieldX; x++)		//仮で壁の追加
	{
		for (int y = 0; y < Field::kFieldY; y++)		//仮で壁の追加
		{
			kStage[y][x] = Field::empty;
		}
	}
	for (int x = 4; x < Field::kFieldX - 10; x++)		//仮で壁の追加
	{
		for (int y = 2; y < Field::kFieldY - 2; y++)		//仮で壁の追加
		{
			kStage[y][x] = Field::ground;
		}
	}
}

int testField::test(int test[10][20])
{
	for (int i = 0; i < Field::kFieldX; i++)		//fieldの初期化
	{
		for (int j = 0; j < Field::kFieldY; j++)
		{
			kStage[j][i] = test[j][i];
		}
	}
	return 0;
}



void testField::FieldInit()
{
	m_pField->test(kStage);
}