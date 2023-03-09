#pragma once
#include"../UI/Vec2.h"

//�@�v���g�^�C�v�錾
class Field;
class InputState;
class Player
{
private:
	//field�N���X
	Field* m_pField;

	//�v���C���[�̈ʒu
	Vec2 m_pos;
	//�v���C���[�̉摜�����炷
	int m_handlePos;
	//�v���C���[�̉摜
	int m_handle;
	//�v���C���[�̉摜�̕\����ύX����ϐ�
	int m_imgidx;

	//�L�[�{�[�h�������ꂽ���Ɉړ��ɐ�����������
	int m_moveDown;			//��
	int m_moveUp;			//��
	int m_moveLeft;			//��
	int m_moveRight;		//�E
	int m_lastMove;			//�Ō�ɉ����ꂽ�L�[���o���Ă���

	int m_animationNumber;		//�A�j���[�V�����̔ԍ�
	int m_animetionFraem;		//�A�j���[�V������ς���C���^�[�o��

	//�����������i�������j
	int m_stepCount;

	float m_playerMoveSpeed;	//�v���C���[�������X�s�[�h	
	Vec2 m_playerNextPos;		//�v���C���[�����ɓ����ꏊ
	bool m_animeFlag;			//�A�j���[�V�����̃t���O

	int m_playerMoveNum;		//�v���C���[���ǂ̌����ɓ�����

	int m_test = 1;
	float m_posX = 800;
	float m_posY = 500;
private:
	//�v���C���[���������߂ɕK�v�ȏ������֐�
	void MoveFrame(Vec2 vel);
	//�v���C���[����������
	void MoveFrame();
	//�v���C���[�̈ړ�����
	void UpdatePlayer(const InputState& input);
	//���ɓ����邩�ǂ����̔��菈��
	bool IsMoveDown()const;
	//��ɓ����邩�ǂ����̔��菈��
	bool IsMoveUp()const;
	//���ɓ����邩�ǂ����̔��菈��
	bool IsMoveLeft()const;
	//�E�ɓ����邩�ǂ����̔��菈��
	bool IsMoveRight()const;

	//�A�j���[�V�������s������
	const void AnimetionPlayer(bool animeFlag);


public:
	Player();
	~Player();

	//�v���C���[�̏����ʒu���󂯎��
	void PosInit(int x, int y);

	//�X�V����
	void Update(const InputState& input);
	// �g�p����t�B�[���h�̃f�[�^��ݒ肷��
	void SetField(Field* pField) { m_pField = pField; }

	//���ɓ����ꏊ�������邩���`�F�b�N���鏈��
	bool IsMoveNextPos(int x, int y)const;

	void TitleUpdate();
	//�`�揈��
	void Draw()const;

	int MoveStep()const { return m_stepCount; }
};

