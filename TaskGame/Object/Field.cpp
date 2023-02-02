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
Field::Field() :
	m_emptyHandle(0),
	m_boxHandle(0),
	m_wallHandle(0),
	m_pinHandle(0)
{
	for (int y = 0; y < kFieldY; y++)		//field�̏�����
	{
		for (int x = 0; x < kFieldX; x++)
		{
			m_field[y][x] = 0;
		}
	}

}

Field::~Field()
{
	DeleteGraph(m_emptyHandle);
	DeleteGraph(m_wallHandle);
	DeleteGraph(m_pinHandle);
	DeleteGraph(m_boxHandle);
}

//�t�B�[���h�N���X�̏�����
void Field::Init()
{
	for (int y = 0; y < kFieldY; y++)		//field�̏�����
	{
		for (int x = 0; x < kFieldX; x++)
		{
			m_field[y][x] = 0;
		}
	}
	m_emptyHandle = LoadGraph("../Date/floor.png");		//�摜�̓ǂݍ���
	m_wallHandle = LoadGraph("../Date/wall.png");		//�摜�̓ǂݍ���
	m_pinHandle = LoadGraph("../Date/pin.png");		//�摜�̓ǂݍ���
	m_boxHandle = LoadGraph("../Date/box.png");		//�摜�̓ǂݍ���
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

			DrawRectRotaGraph(posX + kWidth + (25),
				posY + kHeight + (25),			//�\�����W
				0, 0,							//�؂��荶��
				16, 16,							//���A����
				3.0f, 0.0f,						//�g�嗦�A��]�p�x
				m_emptyHandle, true);


			if (m_field[y][x] == wall)
			{

			DrawRectRotaGraph(posX + kWidth + (25),
				posY + kHeight + (25),			//�\�����W
				0, 0,							//�؂��荶��
				16, 16,							//���A����
				3.0f, 0.0f,						//�g�嗦�A��]�p�x
				m_wallHandle, true);
			}
			if (m_field[y][x] == storage)
			{
				DrawRectRotaGraph(posX + kWidth + (25),
					posY + kHeight + (25),			//�\�����W
					16 * 0, 0,						//�؂��荶��
					16, 16,							//���A����
					2.5f, 0.0f,						//�g�嗦�A��]�p�x
					m_pinHandle, true);
			}
			if (m_field[y][x] == box)
			{
				DrawRectRotaGraph(posX + kWidth + (25),
					posY + kHeight + (25),			//�\�����W
					0, 0,							//�؂��荶��
					16, 21,							//���A����
					2.5f, 0.0f,						//�g�嗦�A��]�p�x
					m_boxHandle, true);
			}
			if (m_field[y][x] == input)
			{
				DrawRectRotaGraph(posX + kWidth + (25),
					posY + kHeight + (25),			//�\�����W
					16, 0,							//�؂��荶��
					16, 21,							//���A����
					2.5f, 0.0f,						//�g�嗦�A��]�p�x
					m_boxHandle, true);
			}
		}
	}
	DrawFormatString(300, 0, GetColor(255, 255, 255), "�c��:%d", kRemaining);
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