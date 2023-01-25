#include "Box.h"
#include"DxLib.h"
#include "Player.h"
#include"Field.h"
#include"Pad.h"

namespace
{
	bool kIsflag = false;
	int kIscolor = 0;
}

Box::Box() :
	m_pField(nullptr),
	m_pPlayer(nullptr),
	m_pos(3,3)
{

}
Box::~Box()
{
	//DeleteGraph(m_handle);		//�摜�̃f���[�g
}
void Box::Init()
{

}

void Box::Update()
{
	MoveBox();				//�v���C���[�̈ړ��������Ăяo��
}

void Box::MoveBox()
{
	Vec2 vec = { 0.0f,0.0f };	//���x�x�N�g��
	

	//if (m_pos.x == m_pPlayer->GetPos().x)
	//if (IsTouchBox())
	if (m_pos.x == 3)
	{
		kIscolor = 255;
	}
	else
	{
		kIscolor = 0;
	}
	if (!IsPut())
	{
		kIsflag = true;
	}
	else
	{
		kIsflag = false;
	}
	if (Pad::isTrigger(PAD_INPUT_DOWN))		//���������ꂽ���̏���
	{
		if (IsMoveDown())
		{
			vec.y = +1.0f;
		}
		//m_imgidx = 0;						//�摜�̏ꏊ�̎w��
	}
	else if (Pad::isTrigger(PAD_INPUT_UP))	//��������ꂽ���̏���
	{
		if (IsMoveUp())
		{
			vec.y = -1.0f;
		}
		//m_imgidx = 1;						//�摜�̏ꏊ�̎w��
	}
	if (Pad::isTrigger(PAD_INPUT_LEFT))		//���������ꂽ���̏���
	{
		if (IsMoveLeft())
		{
			vec.x = -1.0f;
		}
		//m_imgidx = 2;						//�摜�̏ꏊ�̎w��
	}
	else if (Pad::isTrigger(PAD_INPUT_RIGHT))	//�E�������ꂽ���̏���
	{
		if (IsMoveRight())
		{
			vec.x = +1.0f;
		}
		//m_imgidx = 3;						//�摜�̏ꏊ�̎w��
	}

	m_pos += vec;
}

bool Box::IsMoveUp()
{
	int indexX = m_pos.x;
	int indexY = m_pos.y;
	
	// ���łɈ�ԉ��ɂ���ꍇ
	if (indexY >= (Field::kFieldY + 1)) return false;

	// ����Ƀu���b�N���u����Ă���ꍇ
	if (m_pField->IsMovable(indexX, indexY - 1)) return false;

	return true;
}

bool Box::IsMoveDown()
{
	int indexX = m_pos.x;
	int indexY = m_pos.y;
	// ���łɈ�ԉ��ɂ���ꍇ
	if (indexY >= (Field::kFieldY - 1)) return false;

	// ����Ƀu���b�N���u����Ă���ꍇ
	if (m_pField->IsMovable(indexX, indexY + 1)) return false;

	return true;
}

bool Box::IsMoveLeft()
{
	int indexX = m_pos.x;
	int indexY = m_pos.y;
	// ���łɈ�ԍ��ɂ���ꍇ
	if (indexX >= (Field::kFieldX + 1)) return false;

	// ����Ƀu���b�N���u����Ă���ꍇ
	if (m_pField->IsMovable(indexX - 1, indexY)) return false;

	return true;
}

bool Box::IsMoveRight()
{
	int indexX = m_pos.x;
	int indexY = m_pos.y;
	// ���łɈ�ԉE�ɂ���ꍇ
	if (indexX >= (Field::kFieldX - 1)) return false;

	// ��E�Ƀu���b�N���u����Ă���ꍇ
	if (m_pField->IsMovable(indexX + 1, indexY)) return false;

	return true;
}

bool Box::IsPut()
{
	int indexX = m_pos.x;
	int indexY = m_pos.y;

	// �����u���Ă���ꍇ
	if (m_pField->IsPlaced(indexX, indexY)) return false;

	return true;
}

void Box::Draw()
{
	int posX = Field::kSize * m_pos.x;
	int posY = Field::kSize * m_pos.y;

	DrawBox(posX + Field::kWidth + 5, posY + Field::kHeight + 5,			//�\�����W
		(posX + Field::kSize) + Field::kWidth - 5, (posY + Field::kSize) + Field::kHeight - 5,
		GetColor(kIscolor, 255, 0), kIsflag);
}