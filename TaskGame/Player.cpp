#include"DxLib.h"
#include "Player.h"
#include"Field.h"
#include"Box.h"
#include"Pad.h"

namespace
{
	//int kLRReoeatFrame = 8;
}
Player::Player() :
	m_pField(nullptr),
	m_pBox(nullptr),
	m_pos(2,2),
	m_handlePos(25),
	m_handle(0),
	m_imgidx(0)
{
	m_pBox = new Box;
}
Player::~Player()
{
	DeleteGraph(m_handle);		//�摜�̃f���[�g
}
void Player::Init()
{
	m_handle = LoadGraph("../Date/Player.png");		//�摜�̓ǂݍ���
}

void Player::Update()
{
	MovePlayer();				//�v���C���[�̈ړ��������Ăяo��
}

void Player::MovePlayer()
{
	//constexpr float speed = 2.0f;		//�v���C���[�̈ړ����x

	Vec2 vec = { 0.0f,0.0f };	//���x�x�N�g��

	Pad::update();

	//���������ɂ������ړ�
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

	//if (vec.length() > 0.0f)
	//{
	//	vec.normalize();		//�����ɂ�����炸�傫������ɂ���
	//	vec *= speed;			//1�̕����ɃX�s�[�h����Z����
	//}
	m_pos += vec;
}

bool Player::IsMoveUp()
{
	int indexX = m_pos.x;
	int indexY = m_pos.y;
	// ���łɈ�ԉ��ɂ���ꍇ
	if (indexY >= (Field::kFieldY + 1)) return false;

	// ����Ƀu���b�N���u����Ă���ꍇ
	if (m_pField->IsMovable(indexX, indexY - 1)) return false;
	
	return true;
}

bool Player::IsMoveDown()
{
	int indexX = m_pos.x;
	int indexY = m_pos.y;
	// ���łɈ�ԉ��ɂ���ꍇ
	if (indexY >= (Field::kFieldY - 1)) return false;

	// ����Ƀu���b�N���u����Ă���ꍇ
	if (m_pField->IsMovable(indexX, indexY + 1)) return false;

	return true;
}

bool Player::IsMoveLeft()
{
	int indexX = m_pos.x;
	int indexY = m_pos.y;
	// ���łɈ�ԍ��ɂ���ꍇ
	if (indexX >= (Field::kFieldX + 1)) return false;

	// ����Ƀu���b�N���u����Ă���ꍇ
	if (m_pField->IsMovable(indexX - 1, indexY)) return false;

	return true;
}

bool Player::IsMoveRight()
{
	int indexX = m_pos.x;
	int indexY = m_pos.y;
	// ���łɈ�ԉE�ɂ���ꍇ
	if (indexX >= (Field::kFieldX - 1)) return false;

	// ��E�Ƀu���b�N���u����Ă���ꍇ
	if (m_pField->IsMovable(indexX + 1, indexY)) return false;

	return true;
}

void Player::Draw()
{
	int posX = Field::kSize * m_pos.x;
	int posY = Field::kSize * m_pos.y;

	DrawBox(posX + Field::kWidth, posY + Field::kHeight,			//�\�����W
		(posX + Field::kSize) + Field::kWidth, (posY + Field::kSize) + Field::kHeight,
		GetColor(255,0,255),true);


	//DrawRectRotaGraph(posX + Field::kWidth + m_handlePos,
	//	posY + Field::kHeight + m_handlePos,			//�\�����W
	//	48 * 0, 48 * m_imgidx,							//�؂��荶��
	//	48, 48,							//���A����
	//	2.5f, 0.0f,						//�g�嗦�A��]�p�x
	//	m_handle, true);
	//m_pBox->Draw();
	

	DrawFormatString(0, 0, GetColor(255, 255, 255), "%d", posX);
	DrawFormatString(0, 20, GetColor(255, 255, 255), "%d", posY);
	DrawFormatString(0, 40, GetColor(255, 0, 0), "%f", m_pBox-> GetPos().x);
	DrawFormatString(0, 60, GetColor(255, 0, 0), "%f", m_pBox->GetPos().y);
}