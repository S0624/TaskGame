#include"CreateEffect.h"
#include"ClearEffect.h"
#include "DxLib.h"
#include"../UI/game.h"
#include"../GameManager.h"
#include"../SoundManager.h"
void CreateEffect::AnimationUpdate()
{
	m_testFrame++;
	if (m_testFrame > 2)
	{
		m_animeNumX++;
		if (m_animeNumX >= 5)
		{
			m_animeNumY++;
			m_animeNumX = 0;
		}
		if (m_animeNumY >= 6)
		{
			m_animeNumY = 0;
			m_startPosY = GetRand(600) + 200;
			if (m_startPosX == 200)
			{
				m_startPosX = 1200;
			}
			else
			{
				m_startPosX = 200;
			}
		}
		if (m_animeNumX == 1 && m_animeNumY == 3)
		{
			SoundManager::GetInstance().Play(L"fireflower");
		}
		m_testFrame = 0;
	}
}
CreateEffect::CreateEffect()
{
	for (auto& clear : m_pClear)
	{
		clear = std::make_shared<ClearEffect>();
	}

	m_handle = my::MyLoadGraph(L"../Date/Clear.png");

}

CreateEffect::~CreateEffect()
{
	DeleteGraph(m_handle);
}

void CreateEffect::Update()
{
	for (auto& clear : m_pClear)
	{
		if (!clear->IsExist())	continue;
		clear->Update();
	}

	m_flowerFrame--;

	if (m_flowerFrame <= 0)
	{
		int count = 0;
		// ”­¶ˆÊ’u‚©‚çã‚É”ò‚ñ‚Å—Ž‚¿‚Ä‚¢‚­
		for (auto& clear : m_pClear)
		{
			if (clear->IsExist())	continue;

			float randSin = static_cast<float>(GetRand(360)) / 360.0f;
			randSin *= DX_TWO_PI_F;
			float randSpeed = static_cast<float>(GetRand(160)) / 10.0f + 1.0f;

			Vec2 pos;
			//pos.x = m_startPosX;
			//pos.x = 256 + cosf(randSin) * 2.0f;
			pos.x = m_startPosX + cosf(randSin) * 2.0f;
			pos.y = m_startPosY + sinf(randSin) * 2.0f;

			Vec2 vec;
			vec.x = cosf(randSin) * randSpeed;
			vec.y = sinf(randSin) * randSpeed;

			clear->StartPos(pos);
			clear->SetVec(vec);
			clear->SetRadius(2.0f);
			clear->SetColor(0xff2020);
			clear->SetGravity(0.4f);

			count++;
			if (count >= 32)
			{
				break;
			}
		}
		m_flowerFrame = m_flowerInterval;
		//m_startPosY = GetRand(600) + 200;
		//if (m_startPosX == 200)
		//{
		//	m_startPosX = 1200;
		//}
		//else
		//{
		//	m_startPosX = 200;
		//}
	}
}

void CreateEffect::Draw()
{
	AnimationUpdate();

	my::MyDrawRectRotaGraph(m_startPosX, m_startPosY,			//•\Ž¦À•W
		480 * m_animeNumX, 480 * m_animeNumY,			//Ø‚èŽæ‚è¶ã
		480, 480,							//•A‚‚³
		0.5f, 0.0f,						//Šg‘å—¦A‰ñ“]Šp“x
		m_handle, true);

	int count = 0;
	//for (auto& clear : m_pClear)
	//{
	//	if (!clear->IsExist())	continue;
	//	clear->Draw();
	//	count++;
	//}
}