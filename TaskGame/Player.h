#pragma once
#include"Vec2.h"
class Player
{
public:
	Player();
	~Player();

	//������
	void Init();
	//�X�V����
	void Update();
	//�v���C���[�̈ړ�����
	void MovePlayer();
	
	//�`�揈��
	void Draw();
private:
	//�v���C���[�̈ʒu
	Vec2 m_pos;
	//�v���C���[�̉摜
	int m_handle;
	//�v���C���[�̉摜�̕\����ύX����ϐ�
	int m_imgidx;

	int m_repeatDown;

};

