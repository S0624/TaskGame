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
	void SetField(Field* pField) { m_pField = pField; }
	void SetPlayer(Player* pPlayer) { m_pPlayer = pPlayer; }
	
	// ���ݒn�̎擾
	Vec2 GetPos() const { return m_pos; }
	
	//���̈ړ�����
	void MoveBox();

	bool IsTouch(int x, int y);

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
	//Player�N���X
	Player* m_pPlayer;
	//�v���C���[�̈ʒu
	Vec2 m_pos;
};
