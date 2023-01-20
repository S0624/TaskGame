#include"DxLib.h"
#include "Field.h"
#include"game.h"
Field::Field() 
{

}
void Field::Init()
{
	m_wide = Game::kScreenWindth / 2;
	m_hight = Game::kScreenHeight / 2;
}

void Field::Update()
{

}

void Field::Draw()
{
	DrawBox(100, 50,
		m_wide + 100,  m_hight + 50, GetColor(255, 255, 255), false);
}