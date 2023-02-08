#include"DxLib.h"
#include "Field.h"
#include"FieldInformation.h"
#include<cassert>
#include"../UI/game.h"

namespace
{
	int kRemaining = 0;
	FieldInformation m_Information;
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

	m_emptyHandle = LoadGraph("../Date/floor.png");		//�摜�̓ǂݍ���
	m_wallHandle = LoadGraph("../Date/wall.png");		//�摜�̓ǂݍ���
	m_pinHandle = LoadGraph("../Date/pin.png");		//�摜�̓ǂݍ���
	m_boxHandle = LoadGraph("../Date/box.png");		//�摜�̓ǂݍ���

}

Field::~Field()
{
	DeleteGraph(m_emptyHandle);
	DeleteGraph(m_wallHandle);
	DeleteGraph(m_pinHandle);
	DeleteGraph(m_boxHandle);
}

//�t�B�[���h�N���X�̍X�V����
void Field::Update()
{
	kRemaining = 0;
	for (int y = 0; y < kFieldY; y++)		//field�ɂ���u���ꏊ�̃J�E���g
	{
		for (int x = 0; x < kFieldX; x++)
		{
			if (m_field[y][x] == storage)
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

			//if (m_field[y][x] == empty)
			//{
			//	DrawRectRotaGraph(posX + kWidth + (25),
			//		posY + kHeight + (25),			//�\�����W
			//		0, 0,							//�؂��荶��
			//		16, 16,							//���A����
			//		3.0f, 0.0f,						//�g�嗦�A��]�p�x
			//		m_emptyHandle, true);
			//}

			if (m_field[y][x] != empty)
			{
				DrawRectRotaGraph(posX + kWidth + (25),
					posY + kHeight + (25),			//�\�����W
					0, 0,							//�؂��荶��
					16, 16,							//���A����
					3.0f, 0.0f,						//�g�嗦�A��]�p�x
					m_emptyHandle, true);
			}

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

	if (m_field[y][x] == empty)	return true;		//�����Ȃ��Ƃ��̐�ɍs���Ȃ�����
	if (m_field[y][x] == wall)	return true;		//�ǂ��Ƃ��̐�ɍs���Ȃ�����
	
	if (m_field[y][x] == box)						//�����������Ƃ��̏���
	{
		if (m_field[y + posY][x + posX] == ground)	//���������Ă��̐�ɉ����Ȃ����̏���
		{
			m_field[y][x] = ground;					//���ݒn�ɋ󔒂�����
			m_field[y + posY][x + posX] = box;	//�������炷
			return false;
		}
		if (m_field[y + posY][x + posX] == storage)	//���������Ă��̐悪�u���ꏊ�������ꍇ�̏���
		{
			m_field[y][x] = ground;					//���ݒn�ɋ󔒂�����
			m_field[y + posY][x + posX] = input;	//������ꂽ���̏���
			return false;
		}
		return true;							//����ȊO��true��Ԃ�
	}

	if (m_field[y][x] == input)						//�u����Ă��锠�𓮂����Ƃ��̏���
	{
		if (m_field[y + posY][x + posX] == ground)
		{
			m_field[y][x] = storage;
			m_field[y + posY][x + posX] = box;
			return false;
		}
		if (m_field[y + posY][x + posX] == storage)
		{
			m_field[y][x] = storage;
			m_field[y + posY][x + posX] = input;
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

int Field::FieldInfo(int field[kFieldY][kFieldX])
{
	for (int i = 0; i < kFieldX; i++)		//field�ɐ��l������
	{
		for (int j = 0; j < kFieldY; j++)
		{
			m_field[j][i] = field[j][i];
		}
	}
	return 0;
}