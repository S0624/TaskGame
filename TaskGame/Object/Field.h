#pragma once

class Field
{
public:
	//�Ֆʂ̃T�C�Y
	static constexpr int kSize = 48;		//��
	static constexpr int kFieldX = 6;		//��
	static constexpr int kFieldY = 10;		//�c
	static constexpr int kWidth = 100;		//����
	static constexpr int kHeight = 50;		//����

private:
	// ���݂̔Ֆʃf�[�^
	int m_field[kFieldY][kFieldX];
	int m_handle;
	int m_handle2;
	int m_handle3;

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