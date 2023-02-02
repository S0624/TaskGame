#pragma once
#include "SceneBase.h"

//　プロトタイプ宣言
class Player;
class Field;
class InputState;

class SceneMain : public SceneBase
{
//public:
//	//盤面のサイズ
//	static constexpr int kSize = 48;		//横
//	static constexpr int kFieldX = 6;		//横
//	static constexpr int kFieldY = 10;		//縦
//	static constexpr int kWidth = 48 * 10;		//横幅
//	static constexpr int kHeight = 6 * 15;		//高さ

private:
	Player* m_pPlayer;		//Playerクラスをポインタで宣言
	Field* m_pField;		//Fieldクラスをポインタで宣言


private:
	//static constexpr int m_fadeInterval = 10;
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
	void (SceneMain::* m_updateFunc)(const InputState& input);

public:
	SceneMain(SceneManager& manager);
	~SceneMain();

	//初期化
	void Init()const;
	//更新処理
	void Update(const InputState& input);
	//描画処理
	void Draw();

};

