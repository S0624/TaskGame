#pragma once
#include"../Scene/SceneBase.h"
#include"../UI/InputState.h"
class SoundSettingScene : public SceneBase
{
private:
	int m_waitInterval = 60;	//�l���ω�����C���^�[�o��
	int m_pressTimer = 0;		//�������ςȂ��̎���

	/// <summary>
	/// BGM�{�����[�����������ύX����
	/// </summary>
	/// <param name="inputtype">�L�[���͒l</param>
	/// <param name="changeVal">�ω��̒l</param>
	void AcceleraChangeBGMVolume(const InputState& input, InputType inputtype, int changeVal);
	void AcceleraChangeSEVolume(const InputState& input, InputType inputtype, int changeVal);

public:
	SoundSettingScene(SceneManager& manager);
	~SoundSettingScene();
	void Update(const InputState& input);
	void Draw();
};

