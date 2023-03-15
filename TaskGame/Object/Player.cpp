#include"DxLib.h"
#include "Player.h"
#include"Field.h"
#include"../Scene/SceneMain.h"
#include"../UI/InputState.h"
#include"../GameManager.h"

//�v���C���[�̓����̏���
void Player::UpdatePlayer(const InputState& input)
{
	Vec2 vel = { 0,0 };
	//�A�j���[�V�����̃t���O
	bool animetionFlag = false;

	//���������ꂽ���̏���
	if (input.IsPressed(InputType::down))
	{
		animetionFlag = true;				//�{�^���������ꂽ�������t���O��ς���
		m_imgidx = 0;						//�摜�̏ꏊ�̎w��
		if (m_playerMoveNum == 0)
		{
			if (IsMoveDown())
			{
				m_playerMoveNum = 1;
				if (IsMoveNextPos(0, 1))
				{
					//m_pField->test1();
					m_tempPos.push(m_pos);
					vel.y = +Field::kSize;		//���ɓ�����
					m_stepCount++;
				}
			}
		}
	}

	//��������ꂽ���̏���
	else if (input.IsPressed(InputType::up))
	{
		animetionFlag = true;				//�{�^���������ꂽ�������t���O��ς���
		m_imgidx = 1;						//�摜�̏ꏊ�̎w��
		if (m_playerMoveNum == 0) 
		{
			if (IsMoveUp())
			{
				m_playerMoveNum = 2;
				if (IsMoveNextPos(0, -1))
				{
					//m_pField->test1();
					m_tempPos.push(m_pos);
					vel.y = -Field::kSize;		//��ɓ�����
					m_stepCount++;
				}
			}
		}
	}
				
	//���������ꂽ���̏���
	else if (input.IsPressed(InputType::left))
	{
		animetionFlag = true;				//�{�^���������ꂽ�������t���O��ς���
		m_imgidx = 2;						//�摜�̏ꏊ�̎w��
		if (m_playerMoveNum == 0)
		{
			if (IsMoveLeft())
			{
				m_playerMoveNum = 3;
				if (IsMoveNextPos(-1, 0))
				{
					//m_pField->test1();
					m_tempPos.push(m_pos);
					vel.x = -Field::kSize;		//���ɓ�����
					m_stepCount++;
				}
			}
		}
	}

	//�E�������ꂽ���̏���
	else if (input.IsPressed(InputType::right))
	{
		animetionFlag = true;				//�{�^���������ꂽ�������t���O��ς���
		m_imgidx = 3;						//�摜�̏ꏊ�̎w��
		if (m_playerMoveNum == 0)
		{
			if (IsMoveRight())
			{
				m_playerMoveNum = 4;
				if (IsMoveNextPos(1, 0))
				{
					//m_pField->test1();
					m_tempPos.push(m_pos);
					vel.x = +Field::kSize;		//�E�ɓ���
					m_stepCount++;
				}
			}
		}
	}

	if(!m_animeFlag && !m_tempPos.empty())
	{
		if (input.IsTrigger(InputType::back))
		{
			m_pField->tempFieldOut();
			m_pos = m_tempPos.top();
			m_playerNextPos = m_tempPos.top();
			m_tempPos.pop();
			m_stepCount--;
		}
	}

	//�A�j���[�V�������s������
	AnimetionPlayer(m_animeFlag);
	//����������n��
	MoveFrame(vel);
}

//�v���C���[���������߂ɕK�v�ȏ������֐�
void Player::MoveFrame(Vec2 vel)
{
	//�ړ��X�s�[�h�̐ݒ�
	m_playerMoveSpeed = 3.0;
	//���̏ꏊ�Ɉړ����镪�̐��l������
	m_playerNextPos += vel;
}

//�v���C���[����������
void Player::MoveFrame()
{
	if (m_playerMoveNum == 1)
	{
		// ���t���[���ɂ₩�ɖڕW�ɋ߂Â�
		if (m_pos.y != m_playerNextPos.y)
		{
			m_animeFlag = true;
			m_pos.y += m_playerMoveSpeed;
			// �ڕW�ɍ��v������~�߂�
			if (m_pos.y >= m_playerNextPos.y)
			{
				m_pos.y = m_playerNextPos.y;
				m_animeFlag = false;
				m_playerMoveNum = 0;
			}
		}
	}
	if (m_playerMoveNum == 2)
	{
		// ���t���[���ɂ₩�ɖڕW�ɋ߂Â�
		if (m_pos.y != m_playerNextPos.y)
		{
			m_animeFlag = true;
			m_pos.y -= m_playerMoveSpeed;
			// �ڕW�ɍ��v������~�߂�
			if (m_pos.y <= m_playerNextPos.y)
			{
				m_pos.y = m_playerNextPos.y;
				m_animeFlag = false;
				m_playerMoveNum = 0;
			}
		}
	}
	// ���t���[���ɂ₩�ɖڕW�ɋ߂Â�
	if (m_playerMoveNum == 3)
	{
		if (m_pos.x != m_playerNextPos.x)
		{
			m_animeFlag = true;
			m_pos.x -= m_playerMoveSpeed;
			// �ڕW�ɍ��v������~�߂�
			if (m_pos.x <= m_playerNextPos.x)
			{
				m_pos.x = m_playerNextPos.x;
				m_animeFlag = false;
				m_playerMoveNum = 0;
			}
		}
	}
	if (m_playerMoveNum == 4)
	{
		if (m_pos.x != m_playerNextPos.x)
		{
			m_animeFlag = true;
			m_pos.x += m_playerMoveSpeed;
			// �ڕW�ɍ��v������~�߂�
			if (m_pos.x >= m_playerNextPos.x)
			{
				m_pos.x = m_playerNextPos.x;
				m_animeFlag = false;
				m_playerMoveNum = 0;
			}
		}
	}
}

//�v���C���[�̉��ɍs���邩�̔���
bool Player::IsMoveDown()const
{
	int indexX = static_cast<int>(m_pos.x) / Field::kSize;
	int indexY = static_cast<int>(m_pos.y) / Field::kSize;
	int x = 0;
	int y = 1;
	// ���łɈ�ԉ��ɂ���ꍇ
	if (indexY >= (Field::kFieldY - 1)) return false;
	// ����Ƀu���b�N���u����Ă���ꍇ
	if (m_pField->IsMovable(indexX, indexY + y, x, y)) return false;

	return true;
}

//�v���C���[�̏�ɍs���邩�̔���
bool Player::IsMoveUp()const
{
	int indexX = static_cast<int>(m_pos.x) / Field::kSize;
	int indexY = static_cast<int>(m_pos.y) / Field::kSize;
	int x = 0;
	int y = -1;
	// ���łɈ�ԏ�ɂ���ꍇ
	if (indexY <= 0) return false;
	// ����Ƀu���b�N���u����Ă���ꍇ
	if (m_pField->IsMovable(indexX, indexY + y, x, y)) return false;

	return true;
}

//�v���C���[�̍��ɍs���邩�̔���
bool Player::IsMoveLeft()const
{
	int indexX = static_cast<int>(m_pos.x) / Field::kSize;
	int indexY = static_cast<int>(m_pos.y) / Field::kSize;
	int x = -1;
	int y = 0;

	// ���łɈ�ԍ��ɂ���ꍇ
	if (indexX <= 0) return false;
	// ����Ƀu���b�N���u����Ă���ꍇ
	if (m_pField->IsMovable(indexX + x, indexY, x, y)) return false;

	return true;
}

//�v���C���[�̉E�ɍs���邩�̔���
bool Player::IsMoveRight()const
{
	int indexX = static_cast<int>(m_pos.x) / Field::kSize;
	int indexY = static_cast<int>(m_pos.y) / Field::kSize;
	int x = 1;
	int y = 0;

	// ���łɈ�ԉE�ɂ���ꍇ
	if (indexX >= (Field::kFieldX - 1)) return false;
	// ��E�Ƀu���b�N���u����Ă���ꍇ
	if (m_pField->IsMovable(indexX + x, indexY, x, y)) return false;

	return true;
}

//�A�j���[�V�������s������
const void Player::AnimetionPlayer(bool anime)
{
	//�����Ă���Ԃ����A�j���[�V�������s��
	if (m_animeFlag == true)
	{
		//�A�j���[�V�����̃C���^�[�o��
		m_animetionFraem++;
		if (m_animetionFraem > 7)
		{
			//�A�j���[�V������ς���
			m_animationNumber++;
			//�ݒ�l���傫���Ȃ������ԍŏ��̃R�}�ɖ߂�
			if (m_animationNumber > 3)
			{
				m_animationNumber = 0;
			}
			//����̃R�}���΂�
			if (m_animationNumber == 1)
			{
				m_animationNumber = 2;
			}
			//�C���^�[�o�������ɖ߂�
			m_animetionFraem = 0;
		}
	}
	//�����Ă��Ȃ�������~�܂��Ă���i�����Ă���j�摜�ɖ߂�
	else
	{
		m_animetionFraem++;
		if (m_animetionFraem >= 60 * 2)
		{
			m_animetionFraem = 0;
		}

		if (m_animetionFraem / 60 == 1)
		{
			m_animationNumber = 1;
		}
		else
		{
			m_animationNumber = 0;
		}
	}
}

//�v���C���[�N���X�̃R���X�g���N�^
Player::Player() :
	m_pField(nullptr),
	m_pos(200, 300),
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
	m_stepCount(0),
	m_playerMoveSpeed(0),
	m_playerNextPos(0, 0),
	m_animeFlag(0),
	m_playerMoveNum(0)

{
	m_handle = my::MyLoadGraph(L"../Date/Player.png");		//�摜�̓ǂݍ���
}

//�v���C���[�N���X�̃f�X�g���N�^
Player::~Player()
{
	DeleteGraph(m_handle);		//�摜�̃f���[�g
}

//�����ʒu���󂯎��
void Player::PosInit(int x, int y)
{
	//�ʒu�ɃT�C�Y��������
	m_pos.x = static_cast<float>(x) * Field::kSize;
	m_pos.y = static_cast<float>(y) * Field::kSize;
	
	//������
	m_playerNextPos = m_pos;
}

//�v���C���[�N���X�̍X�V����
void Player::Update(const InputState& input)
{
	//�v���C���[����������
	MoveFrame();
	//�Q�[���N���A�ł͂Ȃ�������L�[���͂��󂯕t����
	if (!m_pField->GameClear() && m_stepCount < m_pField->StepLimit())
	//if (!m_pField->GameClear() || !m_pMain->GameOver())
	{
		UpdatePlayer(input);				//�v���C���[�̈ړ��������Ăяo��
	}
}

//���ɓ����ꏊ�������邩���`�F�b�N���鏈��
bool Player::IsMoveNextPos(int x, int y) const
{
	int indexPosX = static_cast<int>(m_playerNextPos.x) / Field::kSize;
	int indexPosY = static_cast<int>(m_playerNextPos.y) / Field::kSize;
	int posX = 0;
	int posY = 0;
	posX = x;
	posY = y;

	// ���łɈ�ԉ��ɂ���ꍇ
	if (indexPosX <= 0) return false;
	if (indexPosY <= 0) return false;
	if (indexPosX >= (Field::kFieldX - 1)) return false;
	if (indexPosY >= (Field::kFieldY - 1)) return false;
	// ����Ƀu���b�N���u����Ă���ꍇ
	if (m_pField->IsMovablePos(indexPosX + posX, indexPosY + posY)) return false;

	return true;
}

void Player::TitleUpdate()
{
	//���̈ړ�
	m_animeFlag = true;				//�t���O��ς���
	if (m_playerMoveNum == 0)
	{
		m_pos.y += m_addition;
		if (m_pos.y >= 500)
		{
			m_imgidx = 3;
			m_pos.y = m_posY;
			m_posY = 300;
			m_playerMoveNum = 1;
		}
	}
	if (m_playerMoveNum == 1)
	{
		m_pos.x += m_addition;
		if (m_pos.x >= 800)
		{
			m_addition *= -1;
			m_imgidx = 1;
			m_pos.x = m_posX;
			m_posX = 300;
			m_playerMoveNum = 2;
		}
	}
	if (m_playerMoveNum == 2)
	{
		m_pos.y += m_addition;
		if (m_pos.y <= 300)
		{
			m_imgidx = 2;
			m_pos.y = m_posY;
			m_posY = 500;
			m_playerMoveNum = 3;
		}
	}
	if (m_playerMoveNum == 3)
	{
		m_pos.x += m_addition;
		if (m_pos.x <= 300)
		{
			m_addition *= -1;
			m_imgidx = 0;
			m_pos.x = m_posX;
			m_posX = 800;
			m_playerMoveNum = 0;
		}
	}
	//�A�j���[�V�������s������
	AnimetionPlayer(m_animeFlag);
}

//�v���C���[�N���X�̕`�揈��
void Player::Draw()const
{
	int posX = static_cast<int>(m_pos.x);
	int posY = static_cast<int>(m_pos.y);

	my::MyDrawRectRotaGraph(posX + Field::kWidth + m_handlePos,
		posY + Field::kHeight + m_handlePos,			//�\�����W
		48 * m_animationNumber, 48 * m_imgidx,			//�؂��荶��
		48, 48,							//���A����
		2.5f, 0.0f,						//�g�嗦�A��]�p�x
		m_handle, true);
}