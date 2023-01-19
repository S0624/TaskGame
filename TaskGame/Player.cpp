#include"DxLib.h"
#include "Player.h"
#include"Pad.h"

Player::Player() :
	m_pos(),
	m_vec()
{

}
void Player::Init()
{
	m_pos.x = 0;
	m_pos.y = 0;
	m_vec.x = 5.5;
	m_vec.y = 5.0;

}

void Player::Update()
{
	Pad::update();
	if (Pad::isPress(PAD_INPUT_RIGHT))
	{
		m_pos.x += m_vec.x;
	}
	if (Pad::isPress(PAD_INPUT_LEFT))
	{
		m_pos.x -= m_vec.x;
	}
	if (Pad::isPress(PAD_INPUT_DOWN))
	{
		m_pos.y += m_vec.y;
	}
	if (Pad::isPress(PAD_INPUT_UP))
	{
		m_pos.y -= m_vec.y;
	}
	//m_pos += m_vec;
}

void Player::Draw()
{
	DrawBox(m_pos.x , m_pos.y ,
		m_pos.x + 50, m_pos.y + 50 , GetColor(255, 255, 255), false);
}