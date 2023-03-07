#include "CreateEffect.h"
#include "ClearEffect.h"

#include"DxLib.h"
CreateEffect::CreateEffect()
{
	for (auto& pPart : m_pClear)
	{
		pPart = std::make_shared<ClearEffect>();
	}
}

CreateEffect::~CreateEffect()
{
}

void CreateEffect::Update()
{
	for (auto& pPart : m_pClear)
	{
		if (!pPart->IsExist())	continue;
		pPart->Update();
	}

	flowerFrame--;

	if (flowerFrame <= 0)
	{
		int count = 0;
		// ”­¶ˆÊ’u‚©‚çã‚É”ò‚ñ‚Å—Ž‚¿‚Ä‚¢‚­
		for (auto& pPart : m_pClear)
		{
			if (pPart->IsExist())	continue;

			float randSin = static_cast<float>(GetRand(360)) / 360.0f;
			randSin *= DX_TWO_PI_F;
			float randSpeed = static_cast<float>(GetRand(160)) / 10.0f + 1.0f;

			Vec2 pos;
			pos.x = 200;
			//pos.x = 256 + cosf(randSin) * 2.0f;
			pos.y = 256 + sinf(randSin) * 2.0f;

			Vec2 vec;
			vec.x = cosf(randSin) * randSpeed;
			vec.y = sinf(randSin) * randSpeed;

			pPart->StartPos(pos);
			pPart->SetVec(vec);
			pPart->SetRadius(2.0f);
			pPart->SetColor(0xff2020);
			pPart->SetGravity(0.4f);

			count++;
			if (count >= 32)
			{
				break;
			}
		}
		flowerFrame = kFlowerInterval;
	}
}

void CreateEffect::Draw()
{
	int count = 0;
	for (auto& pPart : m_pClear)
	{
		if (!pPart->IsExist())	continue;
		pPart->Draw();
		count++;
	}
	DrawFormatString(24, 24, 0xffffff, L"Particle Num : %d", count);
	DrawFormatString(24, 40, 0xffffff, L"DrawCall : %d", GetDrawCallCount());
}
