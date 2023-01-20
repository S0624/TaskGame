#include"DxLib.h"
#include "Field.h"
#include"game.h"
namespace
{
	constexpr int kVertical = 8;		//�c
	constexpr int kHorizontal = 5;	//��
	int kField[kVertical][kHorizontal];		//field�̃f�[�^���������߂̔z��
}
Field::Field() :
 m_height(),
 m_width()

{
	for (int y = 0; y < kVertical; y++)		//field�̏�����
	{
		for (int x = 0; x < kHorizontal; x++)
		{
			kField[y][x] =  0;
		}
	}
}
void Field::Init()
{
	m_height = 50;
	m_width = 100;
}

void Field::Update()
{

}

void Field::Draw()
{
	for (int y = 0; y < kVertical; y++)		//field�̏�����
	{
		for (int x = 0; x < kHorizontal; x++)
		{
			int posX = 50 * x;
			int posY = 50 * y;

			DrawBox(posX + m_width, posY + m_height, 
				posX + 50 + m_width, posY + 50 + m_height, GetColor(255, 0, 0), false);
		}
	}
	//DrawBox(m_width, m_height,
	//	m_width * kHorizontal,  m_height * kVertical, GetColor(255, 255, 255), false);


}