#include "SceneTitle.h"
#include"SceneSelect.h"
#include"SceneManager.h"
#include"../UI/game.h"
#include"../UI/InputState.h"
#include"../GameManager.h"
#include"../Object/MapChip.h"
#include<DxLib.h>

namespace
{
	//const char* const kTextTitle = "SOUKOBAN（KARI）";
	const char* const kTextTitle = "倉庫番（仮）";
	const char* const kTextExplanation = "Aボタンを押してください";
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
	//ガイドの文字の点滅
	m_displayCount++;
	if (m_displayCount >= 60 * 2)
	{
		m_displayCount = 0;
	}

	//「次へ」ボタンが押されたら次へ
	if (input.IsTrigger(InputType::next))
	{
		//m_manager.PushScene(new SceneSelect(m_manager));
		m_updateFunc = &SceneTitle::FadeOutUpdate;
	}
}

void SceneTitle::FadeOutUpdate(const InputState& input)
{
	m_fadeValue = 255 * (static_cast<float>(m_fadeTimer) / static_cast<float>(m_fadeInterval));
	if (++m_fadeTimer == m_fadeInterval) {
	
		m_manager.ChangeScene(new SceneSelect(m_manager));
		return;
	}
}

SceneTitle::SceneTitle(SceneManager& manager) :
	SceneBase(manager), 
	m_updateFunc(&SceneTitle::FadeInUpdate),
	m_handle(0),
	m_displayCount(0),
	m_TitleFont(0),
	m_guideFont(0),
	m_strTitle(-1),
	m_strEx(-1)
{
	m_pMap = new MapChip;
	//std::shared_ptr<MapChip>;
	my::MyFontPath("../Font/851MkPOP_101.ttf"); // 読み込むフォントファイルのパス
	my::MyFontPath("../Font/komorebi-gothic.ttf"); // 読み込むフォントファイルのパス
	
	m_handle = my::MyLoadGraph("../Date/Grass.jpg");
	m_TitleFont = CreateFontToHandle("851マカポップ", 162, -1, -1);
	m_guideFont = CreateFontToHandle("木漏れ日ゴシック", 42, -1, -1);
	m_strTitle = strlen(kTextTitle);
	m_strEx = strlen(kTextExplanation);
	m_strNum = strlen("%d");

	//m_map->Load(L"../Date/back.fmf");
	m_pMap->Load(L"../Date/back.fmf");

}

SceneTitle::~SceneTitle()
{
	delete m_pMap;
	DeleteFontToHandle(m_TitleFont);
	DeleteFontToHandle(m_guideFont);
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

	DrawStringToHandle((Game::kScreenWindth - 
		GetDrawStringWidthToHandle(kTextTitle, m_strTitle,m_TitleFont)) / 2,
		200, kTextTitle, 0xff0000, m_TitleFont);								//タイトルの表示
	
	//点滅処理
	if (m_displayCount / 60 < 1)
	{
		DrawStringToHandle((Game::kScreenWindth -
			GetDrawStringWidthToHandle(kTextExplanation, m_strEx, m_guideFont)) / 2,
			Game::kScreenHeight - 200, kTextExplanation, 0xffffff, m_guideFont);	//ガイドの表示
	}
	//揺れてる処理
	//SetDrawScreen(DX_SCREEN_BACK);
	//int shakeX = GetRand(2) - 2;
	//int shakeY = GetRand(2) - 2;
	//DrawGraph(shakeX, shakeY, m_test, true);
	//DrawStringToHandle((Game::kScreenWindth - GetDrawStringWidth("タイトル", -1)) / 2,
	//	Game::kScreenHeight / 2,"タイトル", 0x00ffff, font);

	
	int mW, mH;
	m_pMap->GetMapSize(mW, mH);
	const auto& mapData = m_pMap->GetMapData();
	for (int chipY = 0; chipY < mH; ++chipY)	// 縦方向
	{
		for (int chipX = 0; chipX < mW; ++chipX)	// 横方向
		{
			auto chipId = mapData[0][chipY * mW + chipX];
			//if (chipId != 0)
			{
				DrawRectGraph(chipX * 16 , chipY * 16,
					(chipId % 16) * 16,
					(chipId / 16) * 16,
					16, 16,
					m_handle, true);
			}
		}
	}

	//今から書く画像と、すでに描画されているスクリーンとの
	//ブレンドの仕方を指定
	SetDrawBlendMode(DX_BLENDMODE_MULA, static_cast<int> (m_fadeValue));
	//画面全体を真っ黒に塗りつぶす
	//変更したら元に戻す
	DrawBox(0, 0, Game::kScreenWindth, Game::kScreenHeight, 0x00000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	//DrawString(300, 200, L"TitleScene", 0xfffff);
}