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
	for (int x = 0; x < Field::kFieldX; x++)		//‰¼‚Å•Ç‚Ì’Ç‰Á
	{
		for (int y = 0; y < Field::kFieldY; y++)		//‰¼‚Å•Ç‚Ì’Ç‰Á
		{
			kStage[y][x] = 0;
		}
	}

}

int testField::test(int test[10][20])
{
	for (int i = 0; i < Field::kFieldX; i++)		//field‚Ì‰Šú‰»
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