#pragma once
#include "SceneBase.h"

//　プロトタイプ宣言
class Field;
class Player;
class MapChip;
class InputState;
class SceneSelect;

class FieldInformation;

class SceneMain : public SceneBase
{
private:
	Player* m_pPlayer;		//Playerクラスをポインタで宣言
	Field* m_pField;		//Fieldクラスをポインタで宣言
	FieldInformation* m_pInformation;
	SceneSelect* m_pSelect;
	MapChip* m_pMap;

private:
	//static constexpr int m_fadeInterval = 10;
	 static constexpr int m_fadeInterval = 30;
	int m_fadeTimer = m_fadeInterval; //フェードタイマー
	float m_fadeValue = 255; //黒矩形とのブレンド具合

	int m_numCount = 0;
	int m_handle = 0;
	int m_backHandle;
	int m_ClearFont = 0;
	int m_guideFont = 0;

	int m_num = 0;
	int m_minNum = 0;
	int m_index = 50;

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

	//更新処理
	void Update(const InputState& input);
	
	void CursorUpdate(const InputState& input);

	//描画処理
	void Draw();
	void DrawBackground();
	//ゲームクリア時の演出
	void DrawGameClear();

};

