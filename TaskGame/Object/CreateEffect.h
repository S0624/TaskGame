#pragma once
#include <array>
#include <memory>
class ClearEffect;

class CreateEffect
{
private:
	int kParticleNum = 4096;
	int kShowerInterval = 2;
	int kFlowerInterval = 120;
	int kAuraInterval = 2;

	float sinRate = 0.0f;
	int showerFrame = kShowerInterval;
	int flowerFrame = kFlowerInterval;
	int auraFrame = kAuraInterval;

	int m_startPosX = 200;
	int m_startPosY = 200;
private:
	std::array<std::shared_ptr<ClearEffect>, 4096> m_pClear;
public:
	CreateEffect();
	~CreateEffect();

	void Update();
	void Draw();
};

