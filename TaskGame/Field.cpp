#include"DxLib.h"
#include "Field.h"
#include<cassert>
#include"game.h"
namespace
{
	enum
	{
		empty,		//何も置かれていない
		wall,		//壁
		storage		//置き場所（箱を置く場所）
	};
}
Field::Field()

{
	for (int y = 0; y < kFieldY; y++)		//fieldの初期化
	{
		for (int x = 0; x < kFieldX; x++)
		{
			m_field[y][x] = 0;
		}
	}

}
void Field::Init()
{
	for (int y = 0; y < kFieldY; y++)		//fieldの初期化
	{
		for (int x = 0; x < kFieldX; x++)
		{
			m_field[y][x] = 0;
		}
	}

	for (int x = 0; x < kFieldX; x++)		//仮で壁の追加
	{
		m_field[0][x] = 1;
		m_field[kFieldY - 1][x] = 1;
	}
	for (int y = 0; y < kFieldY; y++)		//仮で壁の追加
	{
		m_field[y][0] = 1;
		m_field[y][kFieldX - 1] = 1;
	}
	m_field[4][4] = 2;	//仮の置き場所
	m_field[1][3] = 2;	//仮の置き場所
}

void Field::Update()
{

}

void Field::Draw()
{
	for (int y = 0; y < kFieldY; y++)		//fieldの初期化
	{
		for (int x = 0; x < kFieldX; x++)
		{
			int posX = kSize * x;
			int posY = kSize * y;

			if (m_field[y][x] == 0)
			{
				//DrawBox(posX + m_width, posY + m_height,
					//posX + kSize + m_width, posY + kSize + m_height, GetColor(255, 255, 255), false);
			}
			if (m_field[y][x] == 1)
			{
				DrawBox(posX + kWidth, posY + kHeight,
					posX + kSize + kWidth, posY + kSize + kHeight, GetColor(255, 0, 0), true);
			}
			if (m_field[y][x] == 2)
			{
				DrawCircle(posX + kWidth + kSize / 2,
					posY + kHeight + kSize / 2,
					kSize / 4,
					0xfff000, false);
			}
			DrawBox(posX + kWidth, posY + kHeight,
				posX + kSize + kWidth, posY + kSize + kHeight, GetColor(255, 255, 255), false);
		}
	}
	//DrawBox(m_width, m_height,
	//	m_width * kFieldX,  m_height * kFieldY, GetColor(255, 255, 255), false);
}

bool Field::IsMovable(int x, int y)
{
	assert((x >= 0) && (x <= kFieldX - 1));
	assert((y >= 0) && (y <= kFieldY - 1));

	if (m_field[y][x] == 1)	return true;
	return false;
}

bool Field::IsPlaced(int x, int y)
{
	assert((x >= 0) && (x <= kFieldX - 1));
	assert((y >= 0) && (y <= kFieldY - 1));

	if (m_field[y][x] == 2)	return true;
	return false;
}
