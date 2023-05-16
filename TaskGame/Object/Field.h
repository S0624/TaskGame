#pragma once
#include"../UI/Vec2.h"
#include<stack>

class FieldInformation;

class Field
{
public:
	//�Ֆʂ̃T�C�Y
	static constexpr int kSize = 48;					//��
	static constexpr int kFieldX = 20;					//��
	static constexpr int kFieldY = 12;					//�c
	static constexpr int kWidth = kSize * 5;			//����
	static constexpr int kHeight = kSize * 3;			//����

private:
	// ���݂̔Ֆʃf�[�^
	int m_field[kFieldY][kFieldX];
	int m_handle;
	int m_groundHandle;			//��̎��̉摜
	int m_boxHandle;			//���̉摜
	int m_wallHandle;			//�ǂ̉摜
	int m_pinHandle;			//�u���ꏊ�̉摜
	int m_indexSize = 0;
	float m_index = 0.0;
	int m_shift = 0;

	int m_storageNum;			//����u���ׂ��ꏊ�̎c��
	bool m_drawFlag;			//�ړ����̔���\�����邩�ǂ����̃t���O
	float m_boxMoveSpeed;		//���̈ړ��X�s�[�h
	Vec2 m_pos;					//���݂̔��̈ʒu
	Vec2 m_boxNextPos;			//���̔��̏ꏊ�̈ʒu
	int m_boxType;				//���̃^�C�v�i���ʂ̔����A�u����Ă��邩�j
	bool m_moveBox = false;		//�����ړ������ǂ���
	int m_step = 0;
	enum
	{
		empty,		//�����u����Ă��Ȃ�
		ground,		//��
		wall,		//��
		storage,	//�u���ꏊ�i����u���ꏊ�j
		box,		//��
		input,		//�u���ꂽ
		nextPos,	//���ɒu���ꏊ�̋L��
	};

	std::stack<int>m_tempField[kFieldY][kFieldX];
public:
	Field();
	~Field();

	//�X�V����
	void Update();
	//�`�揈��
	void Draw();
	void DrawField(int x,int y);

	//�v���C���[���������邩�z��̃f�[�^������֐�
	bool IsMovable(int posX, int posY, int x, int y);
	//
	//�v���C���[�̎��̏ꏊ���������邩�z��̃f�[�^������֐�
	bool IsMovablePos(int x, int y);

	//�Q�[���N���A������
	bool GameClear()const;

	//�t�B�[���h�̏��������Ă���֐�
	int FieldInfo(int field[kFieldY][kFieldX]);
	int StepLimit(int step);
	int StepLimit();

	//�����ړ������邽�߂̏������֐�
	void MoveFrame(int posX, int posY, int x, int y, int type);
	//�����ړ������鏈��
	void MoveFrame();

	//�����ړ������ǂ�������
	bool MoveBox()const;

	//�t�B�[���h�̈�߂�����
	void tempFieldInput();
	//�t�B�[���h�̈�߂�����
	void tempFieldOut();
};