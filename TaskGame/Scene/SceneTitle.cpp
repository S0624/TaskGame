#include "SceneTitle.h"
#include"SceneMain.h"
#include"SceneManager.h"
#include"SceneSelect.h"
#include"../UI/game.h"
#include"../UI/InputState.h"
#include<DxLib.h>

namespace
{
	const char* const kTextTitle = "タイトル";
	const char* const kTextExplanation = "ボタンを押してください";
	int kNum = 1;
	constexpr int kMaxStage = 5;
}

void SceneTitle::FadeInUpdate(const InputState& input)
{
	m_fadeValue = 255 * (static_cast<float>(m_fadeTimer) / static_cast<float>(m_fadeInterval));
	if (--m_fadeTimer == 0) {
		m_updateFunc = &SceneTitle::NormalUpdate;
		m_fadeValue = 0;
	}
}

void SceneTitle::NormalUpdate(const InputState& input)
{
	//「次へ」ボタンが押されたら次へ
	if (input.IsTrigger(InputType::next))
	{
		//m_manager.PushScene(new SceneSelect(m_manager));
		m_updateFunc = &SceneTitle::FadeOutUpdate;
	}

	if (input.IsTrigger(InputType::right))
	{
		++m_numCount;
		++kNum;
	}
	else if (input.IsTrigger(InputType::left))
	{
		--kNum;
	}


	if (kNum < 1)
	{
		kNum = kMaxStage;
	}
	if (kNum > kMaxStage)
	{
		kNum = 1;
	}
}

void SceneTitle::FadeOutUpdate(const InputState& input)
{
	m_fadeValue = 255 * (static_cast<float>(m_fadeTimer) / static_cast<float>(m_fadeInterval));
	if (++m_fadeTimer == m_fadeInterval) {
	
		m_manager.ChangeScene(new SceneMain(m_manager));
		return;
	}
}

SceneTitle::SceneTitle(SceneManager& manager) :
	SceneBase(manager), 
	m_updateFunc(&SceneTitle::FadeInUpdate),
	m_font(0),
	m_strTitle(-1),
	m_strEx(-1)
{
	//m_test = MakeScreen(Game::kScreenWindth,Game::kScreenHeight,true);

	m_font = CreateFontToHandle("HGS創英角ﾎﾟｯﾌﾟ体", 48, -1, -1);
	m_strTitle = strlen(kTextTitle);
	m_strEx = strlen(kTextExplanation);
	m_strNum = strlen("%d");

}

SceneTitle::~SceneTitle()
{
	//DeleteGraph(m_test);
}

void SceneTitle::Update(const InputState& input)
{
	(this->*m_updateFunc)(input);
}

void SceneTitle::Draw()
{
	//揺れてる処理
	//SetDrawScreen(m_test);

	//背景の代わり
	DrawBox(0, 0, Game::kScreenWindth, Game::kScreenHeight, 0x00000, true);
	//普通の描画
	DrawBox(200, 200, 300, 300, 0xffffff, true);
	
	DrawStringToHandle((Game::kScreenWindth - 
		GetDrawStringWidthToHandle(kTextTitle, m_strTitle,m_font)) / 2,
		200, kTextTitle, 0xffffff, m_font);

	DrawFormatStringToHandle((Game::kScreenWindth - 
		GetDrawStringWidthToHandle("%d", m_strNum, m_font)) / 2,
		Game::kScreenHeight / 2,  0xffffff,m_font,"%d", kNum);
	
	DrawStringToHandle((Game::kScreenWindth - 
		GetDrawStringWidthToHandle(kTextExplanation, m_strEx,m_font)) / 2,
		Game::kScreenHeight - 200, kTextExplanation, 0x00ffff, m_font);

	//揺れてる処理
	//SetDrawScreen(DX_SCREEN_BACK);
	//int shakeX = GetRand(2) - 2;
	//int shakeY = GetRand(2) - 2;
	//DrawGraph(shakeX, shakeY, m_test, true);
	//DrawStringToHandle((Game::kScreenWindth - GetDrawStringWidth("タイトル", -1)) / 2,
	//	Game::kScreenHeight / 2,"タイトル", 0x00ffff, font);


	//今から書く画像と、すでに描画されているスクリーンとの
	//ブレンドの仕方を指定
	SetDrawBlendMode(DX_BLENDMODE_MULA, m_fadeValue);
	//画面全体を真っ黒に塗りつぶす
	//DrawGraph(0, 200, GradH_, true);
	//変更したら元に戻す
	DrawBox(0, 0, Game::kScreenWindth, Game::kScreenHeight, 0x00000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	//DrawString(300, 200, L"TitleScene", 0xfffff);

}

int SceneTitle::SelectNum()
{
	int selectNum = 0;
	selectNum = kNum;
	return selectNum;
}
