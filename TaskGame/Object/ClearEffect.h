#pragma once
#include"../UI/Vec2.h"

class ClearEffect
{
private:
//protected:
	Vec2 m_pos = { 0,0 };
	Vec2 m_vec = { 0,0 };
	float m_radius = 0;
	unsigned int m_color = 0x0ffffff;
	int m_alpha = 0;
	bool m_isExist = false;

	// �d�͉����x	�����Ȃ��ꍇ��0.0���w�肷��
	float m_gravity = 0.0f;

	// �����x�̌������x	����255����w�肵���������Ă���
	int m_alphaDec = 0;

	// ���a�̕ω���
	float m_radiusAcc = 0.0f;


public:
	ClearEffect();
	~ClearEffect();
	void Init();
	void Update();
	void Draw();

	//�����ʒu�̐ݒ�
	void StartPos(Vec2 pos);

	void SetPos(Vec2 pos){ m_pos = pos; }
	void SetVec(Vec2 vec){ m_vec = vec; }
	void SetRadius(float radius){ m_radius = radius; }
	void SetColor(unsigned int color) { m_color = color; }
	void SetGravity(float gravity) { m_gravity = gravity; }

	bool IsExist()const { return m_isExist; }
};