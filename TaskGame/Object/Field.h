#pragma once
#include<vector>

class Field
{
public:
	//�Ֆʂ̃T�C�Y
	static constexpr int kSize = 48;		//��
	static constexpr int kFieldX = 6;		//��
	static constexpr int kFieldY = 10;		//�c
	static constexpr int kWidth = 48 * 2;		//����
	static constexpr int kHeight = 6 * 10;		//����

private:
	//m_field[kFieldY][kFieldX]
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
};