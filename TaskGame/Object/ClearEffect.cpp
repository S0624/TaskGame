#include "ClearEffect.h"
#include"DxLib.h"

ClearEffect::ClearEffect()
{

}

ClearEffect::~ClearEffect()
{

}

void ClearEffect::Init()
{
	m_pos = { 0,0 };
	m_vec = { 0,0 };
	m_radius = 0;
	m_color = 0x0ffffff;
	m_alpha = 0;
	m_isExist = false;
	m_gravity = 0.0f;
	m_alphaDec = 0;
	m_radiusAcc = 0.0f;
}

void ClearEffect::Update()
{
	if (!m_isExist)	return;
	m_pos += m_vec;
	m_vec.y += m_gravity;

	m_radius += m_radiusAcc;
	if (m_radius < 0.0f)
	{
		m_radius = 0.0f;
		m_isExist = false;
	}
	m_alpha -= m_alphaDec;
	if (m_alpha < 0)
	{
		m_isExist = false;
	}
}

void ClearEffect::Draw()
{
	if (!m_isExist)	return;

	SetDrawBlendMode(DX_BLENDMODE_ADD, m_alpha);
	DrawCircleAA(m_pos.x, m_pos.y, m_radius, 16, m_color, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void ClearEffect::StartPos(Vec2 pos)
{
	Init();
	m_pos = pos;
	m_isExist = true;
}
