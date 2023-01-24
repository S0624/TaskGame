#pragma once
#include"Vec2.h"

class Field;
class Player;

class Box
{
public:
	Box();
	~Box();

	//������
	void Init();
	//�X�V����
	void Update();
	// �g�p����t�B�[���h�̃f�[�^��ݒ肷��
	void setField(Field* pField) { m_pField = pField; }

	//�v���C���[�̈ړ�����
	void MoveBox();

	//��ɓ����邩�ǂ����̔��菈��
	bool IsMoveUp();
	//���ɓ����邩�ǂ����̔��菈��
	bool IsMoveDown();
	//���ɓ����邩�ǂ����̔��菈��
	bool IsMoveLeft();
	//�E�ɓ����邩�ǂ����̔��菈��
	bool IsMoveRight();

	//�w��̏ꏊ�ɒu���Ă��邩�̔��菈��
	bool IsPut();

	//�`�揈��
	void Draw();
private:
	//field�N���X
	Field* m_pField;
	//�v���C���[�̈ʒu
	Vec2 m_pos;
};
