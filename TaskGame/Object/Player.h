#pragma once
#include"../UI/Vec2.h"

//�@�v���g�^�C�v�錾
class Field;
class InputState;
//class Box;

class Player
{
private:
	//field�N���X
	Field* m_pField;
	//Box�N���X���|�C���^�Ő錾
	//Box* m_pBox;		

	//�v���C���[�̈ʒu
	Vec2 m_pos;
	//�v���C���[�̉摜�����炷
	int m_handlePos;
	//�v���C���[�̉摜
	int m_handle;
	//�v���C���[�̉摜�̕\����ύX����ϐ�
	int m_imgidx;

	//�������ǂ�
	int m_moveDown;
	int m_moveUp;
	int m_moveLeft;
	int m_moveRight;
	int m_lastMove;

	int m_animationNumber;
	int m_animetionFraem;

	int m_stepCount;
public:
	Player();
	~Player();

	//������
	void Init();
	//�X�V����
	void Update(const InputState& input);
	// �g�p����t�B�[���h�̃f�[�^��ݒ肷��
	void SetField(Field* pField) { m_pField = pField; }
	//void SetBox(Box* pBox) { m_pBox = pBox; }

	// ���ݒn�̎擾
	Vec2 GetPos() const { return m_pos; }

	//�v���C���[�̈ړ�����
	void MovePlayer(const InputState& input);

	//��ɓ����邩�ǂ����̔��菈��
	bool IsMoveUp()const;
	//���ɓ����邩�ǂ����̔��菈��
	bool IsMoveDown()const;
	//���ɓ����邩�ǂ����̔��菈��
	bool IsMoveLeft()const;
	//�E�ɓ����邩�ǂ����̔��菈��
	bool IsMoveRight()const;

	//�`�揈��
	void Draw()const;
};

