#include"DxLib.h"
#include "Player.h"
#include"Pad.h"

Player::Player() :
	m_pos(),
	m_handle(0),
	m_imgidx(0)
{

}
Player::~Player()
{
	DeleteGraph(m_handle);		//�摜�̃f���[�g
}
void Player::Init()
{
	m_pos.x = 150;				//�v���C���[�̏����ʒu
	m_pos.y = 100;				//�v���C���[�̏����ʒu

	m_handle = LoadGraph("../Date/Player.png");		//�摜�̓ǂݍ���
}

void Player::Update()
{
	MovePlayer();				//�v���C���[�̈ړ��������Ăяo��
}

void Player::MovePlayer()
{
	constexpr float speed = 2.0f;		//�v���C���[�̈ړ����x

	Vec2 vec = { 0.0f,0.0f };	//���x�x�N�g��

	Pad::update();

	if (Pad::isPress(PAD_INPUT_DOWN))		//���������ꂽ���̏���
	{
		vec.y = +2.0f;
		m_imgidx = 0;						//�摜�̏ꏊ�̎w��
	}
	else if (Pad::isPress(PAD_INPUT_UP))	//��������ꂽ���̏���
	{
		vec.y = -2.0f;
		m_imgidx = 1;						//�摜�̏ꏊ�̎w��
	}
	if (Pad::isPress(PAD_INPUT_LEFT))		//���������ꂽ���̏���
	{
		vec.x = -2.0f;
		m_imgidx = 2;						//�摜�̏ꏊ�̎w��
	}
	else if (Pad::isPress(PAD_INPUT_RIGHT))	//�E�������ꂽ���̏���
	{
		vec.x = +2.0f;
		m_imgidx = 3;						//�摜�̏ꏊ�̎w��
	}

	if (vec.length() > 0.0f)
	{
		vec.normalize();		//�����ɂ�����炤�傫������ɂ���
		vec *= speed;			//1�̕����ɃX�s�[�h����Z����
	}
	m_pos += vec;
}

void Player::Draw()
{
	DrawRectRotaGraph(m_pos.x, m_pos.y,			//�\�����W
		48 * 0, 48 * m_imgidx,							//�؂��荶��
		48, 48,							//���A����
		2.5f, 0.0f,						//�g�嗦�A��]�p�x
		m_handle, true);


}