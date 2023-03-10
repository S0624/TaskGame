#include"CreateEffect.h"
#include"ClearEffect.h"
#include "DxLib.h"
#include"../UI/game.h"

CreateEffect::CreateEffect()
{
	for (auto& clear : m_pClear)
	{
		clear = std::make_shared<ClearEffect>();
	}
}

CreateEffect::~CreateEffect()
{
}

void CreateEffect::Update()
{
	for (auto& clear : m_pClear)
	{
		if (!clear->IsExist())	continue;
		clear->Update();
	}

	flowerFrame--;

	if (flowerFrame <= 0)
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
		flowerFrame = kFlowerInterval;
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
}

void CreateEffect::Draw()
{
	int count = 0;
	for (auto& clear : m_pClear)
	{
		if (!clear->IsExist())	continue;
		clear->Draw();
		count++;
	}
}