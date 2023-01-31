#include"DxLib.h"
#include "Player.h"
#include"Field.h"
//#include"Box.h"
#include"../UI/Pad.h"
#include"../UI/InputState.h"

namespace
{
	//int kLRReoeatFrame = 8;
}

//�v���C���[�N���X�̃R���X�g���N�^
Player::Player() :
	m_pField(nullptr),
	m_pos(2,2),
	m_handlePos(25),
	m_handle(0),
	m_imgidx(0)
{

}

//�v���C���[�N���X�̃f�X�g���N�^
Player::~Player()
{
	DeleteGraph(m_handle);		//�摜�̃f���[�g
}

//�v���C���[�N���X�̏�����
void Player::Init()
{
	m_handle = LoadGraph("../Date/Player.png");		//�摜�̓ǂݍ���
}

//�v���C���[�N���X�̍X�V����
void Player::Update(const InputState& input)
{
	if (!m_pField->GameClear())
	{
		MovePlayer(input);				//�v���C���[�̈ړ��������Ăяo��
	}
}

//�v���C���[�̓����̏���
void Player::MovePlayer(const InputState& input)
{
	//constexpr float speed = 2.0f;		//�v���C���[�̈ړ����x

	Vec2 vec = { 0.0f,0.0f };	//���x�x�N�g��

	Pad::update();

	//���������ɂ������ړ�
	if(input.IsTrigger(InputType::down))
	//if (Pad::isTrigger(PAD_INPUT_DOWN))		//���������ꂽ���̏���
	{
		if (IsMoveDown())
		{
			vec.y = +1.0f;
		}
		m_imgidx = 0;						//�摜�̏ꏊ�̎w��
	}
	else if (input.IsTrigger(InputType::up))	//��������ꂽ���̏���
	{
		if (IsMoveUp())
		{
			vec.y = -1.0f;
		}
		m_imgidx = 1;						//�摜�̏ꏊ�̎w��
	}
	else if (input.IsTrigger(InputType::left))		//���������ꂽ���̏���
	{
		if (IsMoveLeft())
		{
			vec.x = -1.0f;
		}
		m_imgidx = 2;						//�摜�̏ꏊ�̎w��
	}
	else if (input.IsTrigger(InputType::right))	//�E�������ꂽ���̏���
	{
		if (IsMoveRight())
		{
			vec.x = +1.0f;
		}
		m_imgidx = 3;						//�摜�̏ꏊ�̎w��
	}

	//if (vec.length() > 0.0f)
	//{
	//	vec.normalize();		//�����ɂ�����炸�傫������ɂ���
	//	vec *= speed;			//1�̕����ɃX�s�[�h����Z����
	//}
	m_pos += vec;
}

//�v���C���[�̏�ɍs���邩�̔���
bool Player::IsMoveUp()const
{
	int indexX = m_pos.x;
	int indexY = m_pos.y;
	int x = 0;
	int y = -1;
	// ���łɈ�ԉ��ɂ���ꍇ
	if (indexY >= (Field::kFieldY + 1)) return false;

	// ����Ƀu���b�N���u����Ă���ꍇ
	if (m_pField->IsMovable(indexX, indexY + y, x, y)) return false;


	return true;
}

//�v���C���[�̉��ɍs���邩�̔���
bool Player::IsMoveDown()const
{
	int indexX = m_pos.x;
	int indexY = m_pos.y;
	int x = 0;
	int y = 1;
	// ���łɈ�ԉ��ɂ���ꍇ
	if (indexY >= (Field::kFieldY - 1)) return false;

	// ����Ƀu���b�N���u����Ă���ꍇ
	if (m_pField->IsMovable(indexX, indexY + y,x,y)) return false;

	return true;
}

//�v���C���[�̍��ɍs���邩�̔���
bool Player::IsMoveLeft()const
{
	int indexX = m_pos.x;
	int indexY = m_pos.y;
	int x = -1;
	int y = 0;

	// ���łɈ�ԍ��ɂ���ꍇ
	if (indexX >= (Field::kFieldX + 1)) return false;

	// ����Ƀu���b�N���u����Ă���ꍇ
	if (m_pField->IsMovable(indexX + x, indexY, x, y)) return false;

	return true;
}

//�v���C���[�̉E�ɍs���邩�̔���
bool Player::IsMoveRight()const
{
	int indexX = m_pos.x;
	int indexY = m_pos.y;
	int x = 1;
	int y = 0;
	// ���łɈ�ԉE�ɂ���ꍇ
	if (indexX >= (Field::kFieldX - 1)) return false;

	// ��E�Ƀu���b�N���u����Ă���ꍇ
	if (m_pField->IsMovable(indexX + x, indexY, x, y)) return false;

	return true;
}

//�v���C���[�N���X�̕`�揈��
void Player::Draw()const
{
	//m_pField->Draw();		//�t�B�[���h�N���X�̕`�揈��
	int posX = Field::kSize * m_pos.x;
	int posY = Field::kSize * m_pos.y;

	//DrawBox(posX + Field::kWidth, posY + Field::kHeight,			//�\�����W
	//	(posX + Field::kSize) + Field::kWidth, (posY + Field::kSize) + Field::kHeight,
	//	GetColor(255,0,255),true);


	DrawRectRotaGraph(posX + Field::kWidth + m_handlePos,
		posY + Field::kHeight + m_handlePos,			//�\�����W
		48 * 0, 48 * m_imgidx,							//�؂��荶��
		48, 48,							//���A����
		2.5f, 0.0f,						//�g�嗦�A��]�p�x
		m_handle, true);

	DrawFormatString(0, 0, GetColor(255, 255, 255), "%d", posX);
	DrawFormatString(0, 20, GetColor(255, 255, 255), "%d", posY);
	if (m_pField->GameClear())
	{
		DrawFormatString(400, 100, GetColor(0, 125, 255), "�Q�[���N���A");
	}
}