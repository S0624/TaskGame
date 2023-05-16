#pragma once
#include"../Scene/SceneBase.h"
#include"../UI/InputState.h"
class SoundSettingScene : public SceneBase
{
private:
	int m_waitInterval = 60;	//�l���ω�����C���^�[�o��
	int m_pressTimer = 0;		//�������ςȂ��̎���

public:
	SoundSettingScene(SceneManager& manager);
	~SoundSettingScene(){}
	void Update(const InputState& input);
	void Draw();
};

