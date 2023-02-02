#include"DxLib.h"
#include "Player.h"
#include"Field.h"
//#include"Box.h"
#include"../UI/Pad.h"
#include"../UI/InputState.h"

namespace
{
	//int kLRReoeatFrame = 8;
	// ���E�L�[�̃��s�[�g�t���[��
	constexpr int kMovementFrame = 10;
}

//�v���C���[�N���X�̃R���X�g���N�^
Player::Player() :
	m_pField(nullptr),
	m_pos(2,2),
	m_handlePos(25),
	m_handle(0),
	m_imgidx(0),
	m_moveDown(0),
	m_moveUp(0),
	m_moveLeft(0),
	m_moveRight(0),
	m_lastMove(0),
	m_animationNumber(0),
	m_animetionFraem(0),
	m_stepCount(0)

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
	bool animetionFlag = false;

	int pad = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	//���������ɂ������ړ�
	//if (pad & PAD_INPUT_DOWN)
	//if(input.IsTrigger(InputType::down))
	if(input.IsPressed(InputType::down))
	{
		animetionFlag = true;
		m_imgidx = 0;						//�摜�̏ꏊ�̎w��
		++m_moveDown;
	}
	else
	{
		m_moveDown = 0;
	}
	
	bool isTriggerDown = (pad & PAD_INPUT_DOWN) && !(m_lastMove & PAD_INPUT_DOWN);
	bool isRepeatDown = false;
	if (m_moveDown >= kMovementFrame)		isRepeatDown = true;
	
	if (isTriggerDown || isRepeatDown)
	{
		m_moveDown = 0;
		if (IsMoveDown())
		{
			m_pos.y++;
			m_stepCount++;
		}
	}

	if(input.IsPressed(InputType::up))
	{
		animetionFlag = true;
		m_imgidx = 1;						//�摜�̏ꏊ�̎w��
		++m_moveUp;
	}
	else
	{
		m_moveUp = 0;
	}
	
	bool isTriggerUp = (pad & PAD_INPUT_UP) && !(m_lastMove & PAD_INPUT_UP);
	bool isRepeatUp = false;
	if (m_moveUp >= kMovementFrame)		isRepeatUp = true;
	
	if (isTriggerUp || isRepeatUp)
	{
		m_moveUp = 0;
		if (IsMoveUp())
		{
			m_pos.y--;
			m_stepCount++;
		}
	}

	if(input.IsPressed(InputType::left))
	{
		animetionFlag = true;
		m_imgidx = 2;						//�摜�̏ꏊ�̎w��
		++m_moveLeft;
	}
	else
	{
		m_moveLeft = 0;
	}
	
	bool isTriggerLeft = (pad & PAD_INPUT_LEFT) && !(m_lastMove & PAD_INPUT_LEFT);
	bool isRepeatLeft = false;
	if (m_moveLeft >= kMovementFrame)		isRepeatLeft = true;
	
	if (isTriggerLeft || isRepeatLeft)
	{
		m_moveLeft = 0;
		if (IsMoveLeft())
		{
			m_pos.x--;
			m_stepCount++;
		}
	}
	if(input.IsPressed(InputType::right))
	{
		animetionFlag = true;
		m_imgidx = 3;						//�摜�̏ꏊ�̎w��
		++m_moveRight;
	}
	else
	{
		m_moveRight = 0;
	}
	
	bool isTriggerRight = (pad & PAD_INPUT_RIGHT) && !(m_lastMove & PAD_INPUT_RIGHT);
	bool isRepeatRight = false;
	if (m_moveRight >= kMovementFrame)		isRepeatRight = true;
	
	if (isTriggerRight || isRepeatRight)
	{
		m_moveRight = 0;
		if (IsMoveRight())
		{
			m_pos.x++;
			m_stepCount++;
		}
	}
	m_lastMove = pad;
	

	//if (input.IsTrigger(InputType::up))	//��������ꂽ���̏���
	//{
	//	if (IsMoveUp())
	//	{
	//		vec.y = -1.0f;
	//	}
	//	m_imgidx = 1;						//�摜�̏ꏊ�̎w��
	//}
	//
	//else if (input.IsTrigger(InputType::left))		//���������ꂽ���̏���
	//{
	//	if (IsMoveLeft())
	//	{
	//		vec.x = -1.0f;
	//	}
	//	m_imgidx = 2;						//�摜�̏ꏊ�̎w��
	//}
	//else if (input.IsTrigger(InputType::right))	//�E�������ꂽ���̏���
	//{
	//	if (IsMoveRight())
	//	{
	//		vec.x = +1.0f;
	//	}
	//	m_imgidx = 3;						//�摜�̏ꏊ�̎w��
	//}

	if (animetionFlag == true)
	{
		m_animetionFraem++;
		if (m_animetionFraem > 7)
		{
			m_animationNumber++;
			if (m_animationNumber > 3)
			{
				m_animationNumber = 0;
			}
			if (m_animationNumber == 1)
			{
				m_animationNumber = 2;
			}
			m_animetionFraem = 0;
		}
	}
}

//�v���C���[�̏�ɍs���邩�̔���
bool Player::IsMoveUp()const
{
	int indexX = static_cast<int>(m_pos.x);
	int indexY = static_cast<int>(m_pos.y);
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
	int indexX = static_cast<int>(m_pos.x);
	int indexY = static_cast<int>(m_pos.y);
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
	int indexX = static_cast<int>(m_pos.x);
	int indexY = static_cast<int>(m_pos.y);
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
	int indexX = static_cast<int>(m_pos.x);
	int indexY = static_cast<int>(m_pos.y);
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
	int posX = Field::kSize * static_cast<int>(m_pos.x);
	int posY = Field::kSize * static_cast<int>(m_pos.y);

	//DrawBox(posX + Field::kWidth, posY + Field::kHeight,			//�\�����W
	//	(posX + Field::kSize) + Field::kWidth, (posY + Field::kSize) + Field::kHeight,
	//	GetColor(255,0,255),true);


	DrawRectRotaGraph(posX + Field::kWidth + m_handlePos,
		posY + Field::kHeight + m_handlePos,			//�\�����W
		48 * m_animationNumber, 48 * m_imgidx,			//�؂��荶��
		48, 48,							//���A����
		2.5f, 0.0f,						//�g�嗦�A��]�p�x
		m_handle, true);

	//DrawFormatString(200, 0, 0xffff00, "%d", m_animationNumber);
	//DrawFormatString(200, 20, 0xffff00, "%d", m_animetionFraem);
	//DrawFormatString(200, 40, 0x00ff0f, "%d", m_stepCount);
}