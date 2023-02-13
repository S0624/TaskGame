#pragma once
#include"../UI/Vec2.h"

//#include"testField.h"

class FieldInformation;

class Field
{
public:
	//�Ֆʂ̃T�C�Y
	static constexpr int kSize = 48;		//��
	static constexpr int kFieldX = 20;		//��
	static constexpr int kFieldY = 10;		//�c
	static constexpr int kWidth = kSize * 5;		//����
	static constexpr int kHeight = kSize * 3;		//����

private:
	// ���݂̔Ֆʃf�[�^
	int m_field[kFieldY][kFieldX];
	int m_emptyHandle;				//��̎��̉摜
	int m_boxHandle;				//���̉摜
	int m_wallHandle;				//�ǂ̉摜
	int m_pinHandle;				//�u���ꏊ�̉摜

	int m_storageNum;
	bool m_drawFlag;	//�ړ����̔���\�����邩�ǂ����̃t���O
	float m_boxMoveSpeed;	//���̈ړ��X�s�[�h
	Vec2 m_pos;			//���݂̔��̈ʒu
	Vec2 m_boxNextPos;	//���̔��̏ꏊ�̈ʒu
	int m_boxType;				//���̃^�C�v�i���ʂ̔����A�u����Ă��邩�j

	enum
	{
		empty,		//�����u����Ă��Ȃ�
		ground,		//��
		wall,		//��
		storage,	//�u���ꏊ�i����u���ꏊ�j
		box,		//��
		input,		//�u���ꂽ
		nextpos		//���ɒu�����\��
	};

public:
	Field();
	~Field();

	//�X�V����
	void Update();
	//�`�揈��
	void Draw();

	//�v���C���[���������邩�z��̃f�[�^������֐�
	bool IsMovable(int posX, int posY, int x, int y);
	//
	//�v���C���[�̎��̏ꏊ���������邩�z��̃f�[�^������֐�
	bool IsMovablePos(int x, int y);

	//�Q�[���N���A������
	bool GameClear()const;

	//�t�B�[���h�̏��������Ă���֐�
	int FieldInfo(int field[kFieldY][kFieldX]);

	//�����ړ������邽�߂̏������֐�
	void MoveFrame(int posX, int posY, int x, int y, int type);
	//�����ړ������鏈��
	void MoveFrame();
};