#pragma once
#include "SceneBase.h"

class InputState;
//タイトルシーン

class SceneTitle : public SceneBase
{
private:
	static constexpr int m_fadeInterval = 30;
	int m_fadeTimer = m_fadeInterval; //フェードタイマー
	int m_fadeValue = 255; //黒矩形とのブレンド具合

	//フェードインの時のUpdeta関数
	void FadeInUpdate(const InputState& input);
	//通常状態のUpdate関数
	void NormalUpdate(const InputState& input);
	//フェードアウトの時のUpdate関数
	void FadeOutUpdate(const InputState& input);
	//Update用メンバ関数ポインタ
	void (SceneTitle::* m_updateFunc)(const InputState& input);

	//int m_test;
	int m_numCount = 1;
	int m_font;
	int m_strTitle;
	int m_strEx;
	int m_strNum;

public:
	SceneTitle(SceneManager& manager);
	~SceneTitle();

	void Update(const InputState& input);
	void Draw();

	int SelectNum();

};