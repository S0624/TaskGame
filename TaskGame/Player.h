#pragma once
#include"Vec2.h"

class Field;
class Box;

class Player
{
public:
	Player();
	~Player();

	//������
	void Init();
	//�X�V����
	void Update();
	// �g�p����t�B�[���h�̃f�[�^��ݒ肷��
	void SetField(Field* pField) { m_pField = pField; }


	//�v���C���[�̈ړ�����
	void MovePlayer();

	//��ɓ����邩�ǂ����̔��菈��
	bool IsMoveUp();
	//���ɓ����邩�ǂ����̔��菈��
	bool IsMoveDown();
	//���ɓ����邩�ǂ����̔��菈��
	bool IsMoveLeft();
	//�E�ɓ����邩�ǂ����̔��菈��
	bool IsMoveRight();

	//�`�揈��
	void Draw();
private:
	//field�N���X
	Field* m_pField;
	//Box�N���X���|�C���^�Ő錾
	Box* m_pBox;		

	//�v���C���[�̈ʒu
	Vec2 m_pos;
	//�v���C���[�̉摜�����炷
	int m_handlePos;
	//�v���C���[�̉摜
	int m_handle;
	//�v���C���[�̉摜�̕\����ύX����ϐ�
	int m_imgidx;
};

