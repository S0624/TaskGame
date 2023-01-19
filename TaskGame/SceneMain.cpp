#include "SceneMain.h"
#include"Player.h"
#include"Field.h"
//#include"DxLib.h"

namespace {
	Player m_player;
	Field m_field;
}

void SceneMain::Init()
{
	m_player.Init();
}

void SceneMain::Update()
{
	m_player.Update();
	m_field.Update();
}

void SceneMain::Draw()
{
	m_player.Draw();
	m_field.Draw();
}
