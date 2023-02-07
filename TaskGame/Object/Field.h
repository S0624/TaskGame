#pragma once
#include<vector>

//#include"testField.h"

class testField;

class Field
{
public:
	//�Ֆʂ̃T�C�Y
	static constexpr int kSize = 48;		//��
	static constexpr int kFieldX = 20;		//��
	static constexpr int kFieldY = 10;		//�c
	static constexpr int kWidth = kSize * 3;		//����
	static constexpr int kHeight = kSize * 1.5;		//����

	//enum
	//{
	//	empty,		//�����u����Ă��Ȃ�
	//	ground,		//��
	//	wall,		//��
	//	storage,	//�u���ꏊ�i����u���ꏊ�j
	//	box,		//��
	//	input,		//�u���ꂽ
	//};

private:
	// ���݂̔Ֆʃf�[�^
	int m_field[kFieldY][kFieldX];
	int m_emptyHandle;
	int m_boxHandle;
	int m_wallHandle;
	int m_pinHandle;

public:
	Field();
	~Field();

	//������
	void Init();
	//�X�V����
	void Update();
	//�`�揈��
	void Draw();

	//�������邩�z��̃f�[�^������֐�
	bool IsMovable(int indexX, int indexY,int x, int y);

	//�Q�[���N���A������
	bool GameClear()const;

	//������
	int test(int test[kFieldY][kFieldX]);

};