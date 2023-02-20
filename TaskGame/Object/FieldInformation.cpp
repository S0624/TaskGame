#include "FieldInformation.h"
#include"Field.h"
#include"../Object/Player.h"
#include"../Stage/Stage1.h"
#include"../Stage/Stage2.h"
#include"../Stage/Stage3.h"
#include"../Stage/Stage4.h"
#include"../Stage/Stage5.h"
#include"../Stage/Stage6.h"
#include"../Stage/Stage7.h"
#include"../Stage/Stage8.h"
#include"../Stage/Stage9.h"
#include"../Stage/Stage10.h"

namespace
{
	int kStage[Field::kFieldY][Field::kFieldX];
	int kIndexX = 0;
	int kIndexY = 0;

	int knum = 0;
}

FieldInformation::FieldInformation() :
	m_pField(nullptr),
	m_pPlayer(nullptr),
	m_pStage1(nullptr),
	m_pStage2(nullptr),
	m_pStage3(nullptr),
	m_pStage4(nullptr),
	m_pStage5(nullptr),
	m_pStage6(nullptr),
	m_pStage7(nullptr),
	m_pStage8(nullptr),
	m_pStage9(nullptr),
	m_pStage10(nullptr)
{
	for (int x = 0; x < Field::kFieldX; x++)		//���ŕǂ̒ǉ�
	{
		for (int y = 0; y < Field::kFieldY; y++)		//���ŕǂ̒ǉ�
		{
			kStage[y][x] = 0;
		}
	}
}

FieldInformation::~FieldInformation()
{
	/*delete m_pField;
	delete m_pPlayer;*/
	delete m_pStage1;
	delete m_pStage2;
	delete m_pStage3;
	delete m_pStage4;
	delete m_pStage5;
	delete m_pStage6;
	delete m_pStage7;
	delete m_pStage8;
	delete m_pStage9;
	delete m_pStage10;
}

void FieldInformation::StageNum(int num)
{
	knum = num;
}

void FieldInformation::Init()
{
	/*int num = 2;*/
	if (knum == 1)
	{
		m_pStage1 = new Stage1;
	}
	if (knum == 2)
	{
		m_pStage2 = new Stage2;
	}
	if (knum == 3)
	{
		m_pStage3 = new Stage3;
	}
	if (knum == 4)
	{
		m_pStage4 = new Stage4;
	}
	if (knum == 5)
	{
		m_pStage5 = new Stage5;
	}
	if (knum == 6)
	{
		m_pStage6 = new Stage6;
	}
	if (knum == 7)
	{
		m_pStage7 = new Stage7;
	}
	if (knum == 8)
	{
		m_pStage8 = new Stage8;
	}
	if (knum == 9)
	{
		m_pStage9 = new Stage9;
	}
	if (knum == 10)
	{
		m_pStage10 = new Stage10;
	}
}

void FieldInformation::FieldInfo(int field[10][20])
{
	for (int i = 0; i < Field::kFieldX; i++)		//field�̏�����
	{
		for (int j = 0; j < Field::kFieldY; j++)
		{
			kStage[j][i] = field[j][i];
		}
	}
}

void FieldInformation::PlayerInfo(int x, int y)
{
	kIndexX = x;
	kIndexY = y;
}



void FieldInformation::FieldInit()
{
	m_pField->FieldInfo(kStage);
	m_pPlayer->PosInit(kIndexX, kIndexY);
}