#include"DxLib.h"
#include "Field.h"
#include"FieldInformation.h"
#include<cassert>
#include"../UI/game.h"
#include"../GameManager.h"

namespace
{
	FieldInformation m_Information;
}

//�t�B�[���h�N���X�̃R���X�g���N�^
Field::Field() :
	m_groundHandle(0),
	m_boxHandle(0),
	m_wallHandle(0),
	m_pinHandle(0),
	m_storageNum(0),
	m_drawFlag(false),
	m_boxMoveSpeed(0),
	m_pos(0, 0),
	m_boxNextPos(0, 0),
	m_boxType(0)
{
	for (int y = 0; y < kFieldY; y++)		//field�̏�����
	{
		for (int x = 0; x < kFieldX; x++)
		{
			m_field[y][x] = 0;
		}
	}

	m_groundHandle = my::MyLoadGraph(L"../Date/floor.png");		//�摜�̓ǂݍ���
	m_wallHandle = my::MyLoadGraph(L"../Date/wall.png");		//�摜�̓ǂݍ���
	m_pinHandle = my::MyLoadGraph(L"../Date/pin.png");		//�摜�̓ǂݍ���
	m_boxHandle = my::MyLoadGraph(L"../Date/box.png");		//�摜�̓ǂݍ���
}

Field::~Field()
{
	DeleteGraph(m_groundHandle);
	DeleteGraph(m_wallHandle);
	DeleteGraph(m_pinHandle);
	DeleteGraph(m_boxHandle);
}

//�t�B�[���h�N���X�̍X�V����
void Field::Update()
{
	//���̈ړ�����
	MoveFrame();

	int remaining = 0;
	for (int y = 0; y < kFieldY; y++)		//field�ɂ���u���ꏊ�̃J�E���g
	{
		for (int x = 0; x < kFieldX; x++)
		{
			if (m_field[y][x] == storage)
			{
				remaining++;
			}
		}
	}
	m_storageNum = remaining;
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

			if (m_field[y][x] != empty)
			{
				my::MyDrawRectRotaGraph(posX + kWidth + (25),
					posY + kHeight + (25),			//�\�����W
					0, 0,							//�؂��荶��
					16, 16,							//���A����
					3.0f, 0.0f,						//�g�嗦�A��]�p�x
					m_groundHandle, true);
			}

			if (m_field[y][x] == wall)
			{

				my::MyDrawRectRotaGraph(posX + kWidth + (25),
					posY + kHeight + (25),			//�\�����W
					0, 0,							//�؂��荶��
					16, 16,							//���A����
					3.0f, 0.0f,						//�g�嗦�A��]�p�x
					m_wallHandle, true);
			}
			if (m_field[y][x] == storage)
			{
				my::MyDrawRectRotaGraph(posX + kWidth + (25),
					posY + kHeight + (25),			//�\�����W
					0, 0,						//�؂��荶��
					16, 16,							//���A����
					2.5f, 0.0f,						//�g�嗦�A��]�p�x
					m_pinHandle, true);
			}
			if (m_field[y][x] == box)
			{
				my::MyDrawRectRotaGraph(posX + kWidth + (25),
					posY + kHeight + (25),			//�\�����W
					0, 0,							//�؂��荶��
					16, 21,							//���A����
					2.5f, 0.0f,						//�g�嗦�A��]�p�x
					m_boxHandle, true);
			}
			if (m_field[y][x] == input)
			{
				my::MyDrawRectRotaGraph(posX + kWidth + (25),
					posY + kHeight + (25),			//�\�����W
					16, 0,							//�؂��荶��
					16, 21,							//���A����
					2.5f, 0.0f,						//�g�嗦�A��]�p�x
					m_boxHandle, true);
			}
			if (m_field[y][x] == nextPos)
			{
				my::MyDrawRectRotaGraph(posX + kWidth + (25),
					posY + kHeight + (25),			//�\�����W
					0, 0,						//�؂��荶��
					16, 16,							//���A����
					2.5f, 0.0f,						//�g�嗦�A��]�p�x
					m_pinHandle, true);
			}
		}
	}

	//�t���O�������Ă����甠��\��������
	if (m_drawFlag == true)
	{
		int index = 0;
		if (m_boxType == box)
		{
			index = 0;
		}
		else
		{
			index = 16;
		}
		my::MyDrawRectRotaGraph(static_cast<int>(m_pos.x) + kWidth + (25),
			static_cast<int>(m_pos.y) + kHeight + (25),			//�\�����W
			index, 0,							//�؂��荶��
			16, 21,							//���A����
			2.5f, 0.0f,						//�g�嗦�A��]�p�x
			m_boxHandle, true);
	}
}

//�t�B�[���h�̒��g�����ē����邩��Ԃ�����
bool Field::IsMovable(int posX, int posY, int x, int y)
{
	assert((x >= 0) || (x <= kFieldX - 1));		//�A�T�[�g
	assert((y >= 0) || (y <= kFieldY - 1));		//�͈͊O���Ə������~�߂�

	if (m_field[posY][posX] == empty)	return true;		//�����Ȃ��Ƃ��̐�ɍs���Ȃ�����
	if (m_field[posY][posX] == wall)	return true;		//�ǂ��Ƃ��̐�ɍs���Ȃ�����

	m_moveBox = true;
	if (m_field[posY][posX] == box)						//�����������Ƃ��̏���
	{
		if (m_field[posY + y][posX + x] == ground)	//���������Ă��̐�ɉ����Ȃ����̏���
		{
			m_drawFlag = true;
			m_field[posY][posX] = ground;					//���ݒn�ɋ󔒂�����
			//m_field[y + posY][x + posX] = ground;			//���ɔ�������ꏊ�̊m��
			m_field[y + posY][x + posX] = ground;			//���ɔ�������ꏊ�̊m��
			MoveFrame(posX, posY, x, y, box);

			return false;
		}
		if (m_field[posY + y][posX + x] == storage)	//���������Ă��̐悪�u���ꏊ�������ꍇ�̏���
		{
			m_drawFlag = true;
			m_field[posY][posX] = ground;					//���ݒn�ɋ󔒂�����
			m_field[y + posY][x + posX] = nextPos;			//���ɔ�������ꏊ�̊m��
			MoveFrame(posX, posY, x, y, input);
			return false;
		}
		return true;							//����ȊO��true��Ԃ�
	}

	if (m_field[posY][posX] == input)						//�u����Ă��锠�𓮂����Ƃ��̏���
	{
		if (m_field[posY + y][posX + x] == ground)
		{
			m_drawFlag = true;
			m_field[posY][posX] = storage;
			m_field[y + posY][x + posX] = ground;			//���ɔ�������ꏊ�̊m��
			MoveFrame(posX, posY, x, y, box);
			return false;
		}
		if (m_field[posY + y][posX + x] == nextPos)
		{
			m_drawFlag = true;
			m_field[posY][posX] = storage;
			m_field[y + posY][x + posX] = nextPos;			//���ɔ�������ꏊ�̊m��
			MoveFrame(posX, posY, x, y, input);
			return false;
		}
		return true;
	}
	return false;
}

//�t�B�[���h�̒��g�����ē����邩��Ԃ�����
bool Field::IsMovablePos(int x, int y)
{
	if (m_field[y][x] == ground)	return false;		//�n�ʂ��ƈړ��ł���
	if (m_field[y][x] == storage)	return false;		//�u���ꏊ���ƈړ��ł���
	return true;										//���̐�ɍs���Ȃ�����
}

//�Q�[���N���A���ǂ�����Ԃ�����
bool Field::GameClear()const
{
	//�u���ꏊ���[���ɂȂ�����@true��Ԃ�
	if (m_storageNum == 0) return true;
	return false;
}

//�t�B�[���h�̏��������Ă���֐�
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

//�����ړ������邽�߂̏������֐�
void Field::MoveFrame(int posX, int posY, int x, int y, int type)
{
	int vec = x + y;			//�ړ��x�N�g�����}�C�i�X���v���X�����ׂ�
	m_drawFlag = true;			//�t���O��true�ɂ���
	m_pos.x = static_cast<float>(posX * kSize);	//���̌��ݒn���v�Z����
	m_pos.y = static_cast<float>(posY * kSize);	//���̌��ݒn���v�Z����
	m_boxMoveSpeed = static_cast <float>(3.0 * vec);	//�ړ��X�s�[�h�̐ݒ�
	m_boxNextPos.x = static_cast<float>(posX * kSize) + (x * kSize);	//���̎��̏ꏊ�̌v�Z
	m_boxNextPos.y = static_cast<float>(posY * kSize) + (y * kSize);	//���̎��̏ꏊ�̌v�Z
	m_boxType = type;			//���̃^�C�v
}

//�����ړ������鏈��
void Field::MoveFrame()
{
	//���̏ꏊ
	int x = static_cast<int>(m_boxNextPos.x) / kSize;
	int y = static_cast<int>(m_boxNextPos.y) / kSize;
	// ���t���[���ɂ₩�ɖڕW�ɋ߂Â�
	if (m_pos.y != m_boxNextPos.y)
	{
		m_pos.y += m_boxMoveSpeed;
		//	// �ڕW�ɍ��v������~�߂�
		if (m_boxMoveSpeed == 3.0)
		{
			if (m_pos.y >= m_boxNextPos.y)
			{
				if (m_boxType == box)
				{
					m_field[y][x] = box;
				}
				else
				{
					m_field[y][x] = input;
				}
				m_pos.y = m_boxNextPos.y;
				m_drawFlag = false;
			}
		}
		else
		{
			if (m_pos.y <= m_boxNextPos.y)
			{
				if (m_boxType == box)
				{
					m_field[y][x] = box;
				}
				else
				{
					m_field[y][x] = input;
				}
				m_pos.y = m_boxNextPos.y;
				m_drawFlag = false;
			}
		}
	}

	// ���t���[���ɂ₩�ɖڕW�ɋ߂Â�
	if (m_pos.x != m_boxNextPos.x)
	{
		m_pos.x += m_boxMoveSpeed;
		//	// �ڕW�ɍ��v������~�߂�
		if (m_boxMoveSpeed == 3.0)
		{
			if (m_pos.x >= m_boxNextPos.x)
			{
				if (m_boxType == box)
				{
					m_field[y][x] = box;
				}
				else
				{
					m_field[y][x] = input;
				}
				m_pos.x = m_boxNextPos.x;
				m_drawFlag = false;
			}
		}
		else
		{
			if (m_pos.x <= m_boxNextPos.x)
			{
				if (m_boxType == box)
				{
					m_field[y][x] = box;
				}
				else
				{
					m_field[y][x] = input;
				}
				m_pos.x = m_boxNextPos.x;
				m_drawFlag = false;
			}
		}
	}
	m_moveBox = false;
}

bool Field::MoveBox() const
{
	if (m_moveBox == true)return true;
	return false;
}
