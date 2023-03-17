#pragma once
#include"../Scene/SceneBase.h"
#include"../UI/InputState.h"
class SoundSettingScene : public SceneBase
{
private:
	int m_waitInterval = 60;	//値が変化するインターバル
	int m_pressTimer = 0;		//押しっぱなしの時間

	/// <summary>
	/// BGMボリュームを加速しつつ変更する
	/// </summary>
	/// <param name="inputtype">キー入力値</param>
	/// <param name="changeVal">変化の値</param>
	void AcceleraChangeBGMVolume(const InputState& input, InputType inputtype, int changeVal);
	void AcceleraChangeSEVolume(const InputState& input, InputType inputtype, int changeVal);

public:
	SoundSettingScene(SceneManager& manager);
	~SoundSettingScene();
	void Update(const InputState& input);
	void Draw();
};

