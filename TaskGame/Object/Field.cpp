#include"DxLib.h"
#include "Field.h"
#include<cassert>
#include"../UI/game.h"

namespace
{
	enum
	{
		empty,		//�����u����Ă��Ȃ�
		wall,		//��
		storage,	//�u���ꏊ�i����u���ꏊ�j
		box,		//��
		input,		//�u���ꂽ
	};

	int kRemaining = 0;
}

//�t�B�[���h�N���X�̃R���X�g���N�^
Field::Field()
{
	for (int y = 0; y < kFieldY; y++)		//field�̏�����
	{
		for (int x = 0; x < kFieldX; x++)
		{
			m_field[y][x] = 0;
		}
	}

}

//�t�B�[���h�N���X�̏�����
void Field::Init()
{
	//for (int y = 0; y < kFieldY; y++)		//field�̏�����
	//{
	//	for (int x = 0; x < kFieldX; x++)
	//	{
	//		m_field[y][x] = 0;
	//	}
	//}

	for (int x = 0; x < kFieldX; x++)		//���ŕǂ̒ǉ�
	{
		m_field[0][x] = 1;
		m_field[kFieldY - 1][x] = 1;
	}
	for (int y = 0; y < kFieldY; y++)		//���ŕǂ̒ǉ�
	{
		m_field[y][0] = 1;
		m_field[y][kFieldX - 1] = 1;
	}
	m_field[4][4] = 2;	//���̒u���ꏊ
	m_field[1][3] = 2;	//���̒u���ꏊ
	
	m_field[3][3] = 3;	//���̒u���ꏊ
	m_field[4][3] = 3;	//���̒u���ꏊ
}

//�t�B�[���h�N���X�̍X�V����
void Field::Update()
{
	kRemaining = 0;
	for (int y = 0; y < kFieldY; y++)		//field�ɂ���u���ꏊ�̃J�E���g
	{
		for (int x = 0; x < kFieldX; x++)
		{
			if (m_field[y][x] == 2)
			{
				kRemaining++;
			}
		}
	}
	
}

//�t�B�[���h�N���X�̕`�揈��
void Field::Draw()
{
	for (int y = 0; y < kFieldY; y++)		//field�̏�����
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
			if (m_field[y][x] == 3)
			{
				DrawBox(posX + kWidth + 5, posY + kHeight + 5,			//�\�����W
					(posX + kSize) + kWidth - 5, (posY +kSize) + kHeight - 5,
					GetColor(100, 255, 0), false);
			}
			if (m_field[y][x] == 4)
			{
				DrawBox(posX + kWidth + 5, posY + kHeight + 5,			//�\�����W
					(posX + kSize) + kWidth - 5, (posY +kSize) + kHeight - 5,
					GetColor(100, 255, 0), true );
			}
			DrawBox(posX + kWidth, posY + kHeight,
				posX + kSize + kWidth, posY + kSize + kHeight, GetColor(255, 255, 255), false);
		}
	}
	DrawFormatString(300, 0, GetColor(255, 255, 255), "�c��:%d", kRemaining);

	//DrawBox(m_width, m_height,
		//m_width * kFieldX,  m_height * kFieldY, GetColor(255, 255, 255), false);
}

//�t�B�[���h�̒��g�����ē����邩��Ԃ�����
bool Field::IsMovable(int x, int y, int posX, int posY)
{
	assert((x >= 0) && (x <= kFieldX - 1));		//�A�T�[�g
	assert((y >= 0) && (y <= kFieldY - 1));		//�͈͊O���Ə������~�߂�

	if (m_field[y][x] == 1)	return true;		//�ǂ��Ƃ��̐�ɍs���Ȃ�����
	
	if (m_field[y][x] == 3)						//�����������Ƃ��̏���
	{
		if (m_field[y + posY][x + posX] == 0)	//���������Ă��̐�ɉ����Ȃ����̏���
		{
			m_field[y][x] = 0;					//���ݒn�ɋ󔒂�����
			m_field[y + posY][x + posX] = 3;	//�������炷
			return false;
		}
		if (m_field[y + posY][x + posX] == 2)	//���������Ă��̐悪�u���ꏊ�������ꍇ�̏���
		{
			m_field[y][x] = 0;					//���ݒn�ɋ󔒂�����
			m_field[y + posY][x + posX] = 4;	//������ꂽ���̏���
			return false;
		}
		return true;							//����ȊO��true��Ԃ�
	}
	if (m_field[y][x] == 4)						//�u����Ă��锠�𓮂����Ƃ��̏���
	{
		if (m_field[y + posY][x + posX] == 0)
		{
			m_field[y][x] = 2;
			m_field[y + posY][x + posX] = 3;
			return false;
		}
		return true;
	}
	return false;
}

//�Q�[���N���A���ǂ�����Ԃ�����
bool Field::GameClear()const
{
	if (kRemaining == 0) return true;
	return false;
}