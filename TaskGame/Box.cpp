#include "Box.h"
#include"DxLib.h"
#include "Player.h"
#include"Field.h"
#include"Pad.h"

namespace
{
	bool kIsflag = false;
}

Box::Box() :
	m_pField(nullptr),
	m_pos()
{

}
Box::~Box()
{
	//DeleteGraph(m_handle);		//�摜�̃f���[�g
}
void Box::Init()
{
	m_pos.x = 3;				//�v���C���[�̏����ʒu
	m_pos.y = 3;				//�v���C���[�̏����ʒu
	//m_pos.x = 175;				//�v���C���[�̏����ʒu
	//m_pos.y = 125;				//�v���C���[�̏����ʒu

	//m_handle = LoadGraph("../Date/Box.png");		//�摜�̓ǂݍ���
}

void Box::Update()
{
	MoveBox();				//�v���C���[�̈ړ��������Ăяo��
}

void Box::MoveBox()
{
	constexpr float speed = 2.0f;		//�v���C���[�̈ړ����x

	Vec2 vec = { 0.0f,0.0f };	//���x�x�N�g��

	Pad::update();

	////���������ɂ������ړ�
	//if (Pad::isTrigger(PAD_INPUT_DOWN))		//���������ꂽ���̏���
	//{
	//	if (IsMoveDown())
	//	{
	//		vec.y = +1.0f;
	//	}
	//	//m_imgidx = 0;						//�摜�̏ꏊ�̎w��
	//}
	//else if (Pad::isTrigger(PAD_INPUT_UP))	//��������ꂽ���̏���
	//{
	//	if (IsMoveUp())
	//	{
	//		vec.y = -1.0f;
	//	}
	//	//m_imgidx = 1;						//�摜�̏ꏊ�̎w��
	//}
	//if (Pad::isTrigger(PAD_INPUT_LEFT))		//���������ꂽ���̏���
	//{
	//	if (IsMoveLeft())
	//	{
	//		vec.x = -1.0f;
	//	}
	//	//m_imgidx = 2;						//�摜�̏ꏊ�̎w��
	//}
	//else if (Pad::isTrigger(PAD_INPUT_RIGHT))	//�E�������ꂽ���̏���
	//{
	//	if (IsMoveRight())
	//	{
	//		vec.x = +1.0f;
	//	}
	//	//m_imgidx = 3;						//�摜�̏ꏊ�̎w��
	//}

	////if (vec.length() > 0.0f)
	////{
	////	vec.normalize();		//�����ɂ�����炸�傫������ɂ���
	////	vec *= speed;			//1�̕����ɃX�s�[�h����Z����
	////}
	//m_pos += vec;
}

bool Box::IsMoveUp()
{
	int indexX = m_pos.x;
	int indexY = m_pos.y;
	// ���łɈ�ԉ��ɂ���ꍇ
	if (indexY >= (Field::kFieldY + 1)) return false;

	// ����Ƀu���b�N���u����Ă���ꍇ
	if (m_pField->IsBlockDate(indexX, indexY - 1)) return false;

	return true;
}

bool Box::IsMoveDown()
{
	int indexX = m_pos.x;
	int indexY = m_pos.y;
	// ���łɈ�ԉ��ɂ���ꍇ
	if (indexY >= (Field::kFieldY - 1)) return false;

	// ����Ƀu���b�N���u����Ă���ꍇ
	if (m_pField->IsBlockDate(indexX, indexY + 1)) return false;

	return true;
}

bool Box::IsMoveLeft()
{
	int indexX = m_pos.x;
	int indexY = m_pos.y;
	// ���łɈ�ԍ��ɂ���ꍇ
	if (indexX >= (Field::kFieldX + 1)) return false;

	// ����Ƀu���b�N���u����Ă���ꍇ
	if (m_pField->IsBlockDate(indexX - 1, indexY)) return false;

	return true;
}

bool Box::IsMoveRight()
{
	int indexX = m_pos.x;
	int indexY = m_pos.y;
	// ���łɈ�ԉE�ɂ���ꍇ
	if (indexX >= (Field::kFieldX - 1)) return false;

	// ��E�Ƀu���b�N���u����Ă���ꍇ
	if (m_pField->IsBlockDate(indexX + 1, indexY)) return false;

	return true;
}

void Box::Draw()
{
	//int posX = Field::kSize * m_pos.x;
	//int posY = Field::kSize * m_pos.y;

	//DrawBox(posX + Field::kWidth, posY + Field::kHeight,			//�\�����W
	//	(posX + Field::kSize) + Field::kWidth, (posY + Field::kSize) + Field::kHeight,
	//	GetColor(0, 0, 255), true);

	DrawBox((3 * 50) + 100, (3 * 50) + 50,			//�\�����W
		((3 * 50) + 50) + 100, ((3 * 50) + 50) + 50,
		GetColor(0, 255, 255), kIsflag);

	//DrawRectRotaGraph(posX + Field::kWidth + m_handlePos,
	//	posY + Field::kHeight + m_handlePos,			//�\�����W
	//	48 * 0, 48 * m_imgidx,							//�؂��荶��
	//	48, 48,							//���A����
	//	2.5f, 0.0f,						//�g�嗦�A��]�p�x
	//	m_handle, true);


	//DrawFormatString(0, 40, GetColor(255, 0, 0), "%d", posX);
	//DrawFormatString(0, 60, GetColor(255, 0, 0), "%d", posY);
}