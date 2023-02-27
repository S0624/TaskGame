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
	//const char* const kTextTitle = "倉庫番（仮）";
	//const char* const kTextExplanation = "Aボタンを押してください";
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
		PlaySoundMem(m_enterSESound, DX_PLAYTYPE_BACK);
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
	m_backHandle(0),
	m_roomHandle(0),
	m_enterSESound(0),
	m_BgSound(0),
	m_displayCount(0),
	m_TitleFont(0),
	m_guideFont(0),
	m_strTitle(-1),
	m_strEx(-1)
{
	m_pMap = new MapChip;
	my::MyFontPath(L"../Font/851MkPOP_101.ttf"); // 読み込むフォントファイルのパス
	my::MyFontPath(L"../Font/komorebi-gothic.ttf"); // 読み込むフォントファイルのパス

	m_enterSESound = LoadSoundMem(L"../Sound/SE1.mp3");
	m_BgSound = LoadSoundMem(L"../Sound/TitleBg.mp3");

	m_backHandle = my::MyLoadGraph(L"../Date/Grass.png");
	m_roomHandle = my::MyLoadGraph(L"../Date/texture.png");
	m_TitleFont = CreateFontToHandle(L"851マカポップ", 162, -1, -1);
	m_guideFont = CreateFontToHandle(L"木漏れ日ゴシック", 42, -1, -1);
	m_strTitle = strlen("倉庫番");
	m_strEx = strlen("Aボタンを押してください");
	m_strNum = strlen("%d");

	m_pMap->Load(L"../Date/room.fmf");

	PlaySoundMem(m_BgSound, DX_PLAYTYPE_LOOP);

}

SceneTitle::~SceneTitle()
{
	delete m_pMap;
	DeleteGraph(m_backHandle);
	DeleteGraph(m_roomHandle);
	DeleteSoundMem(m_enterSESound);
	DeleteSoundMem(m_BgSound);
	DeleteFontToHandle(m_TitleFont);
	DeleteFontToHandle(m_guideFont);
}

void SceneTitle::Update(const InputState& input)
{

	(this->*m_updateFunc)(input);
}

void SceneTitle::Draw()
{
	//背景
	DrawBackground();

	DrawStringToHandle((Game::kScreenWindth -
		GetDrawStringWidthToHandle(L"倉庫番", m_strTitle, m_TitleFont)) / 2 + 5,
		200 + 3, L"倉庫番", 0x000000, m_TitleFont);								//タイトルの表示
	DrawStringToHandle((Game::kScreenWindth -
		GetDrawStringWidthToHandle(L"倉庫番", m_strTitle, m_TitleFont)) / 2,
		200, L"倉庫番", 0xff0000, m_TitleFont);								//タイトルの表示
	//点滅処理
	if (m_displayCount / 60 < 1)
	{
		DrawStringToHandle((Game::kScreenWindth -
			GetDrawStringWidthToHandle(L"Aボタンを押してください", m_strEx, m_guideFont)) / 2,
			Game::kScreenHeight - 200, L"Aボタンを押してください", 0xffffff, m_guideFont);	//ガイドの表示
	}

	//今から書く画像と、すでに描画されているスクリーンとの
	//ブレンドの仕方を指定
	SetDrawBlendMode(DX_BLENDMODE_MULA, static_cast<int> (m_fadeValue));
	//画面全体を真っ黒に塗りつぶす
	//変更したら元に戻す
	DrawBox(0, 0, Game::kScreenWindth, Game::kScreenHeight, 0x00000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void SceneTitle::DrawBackground()
{
	//背景
	int mW, mH;
	m_pMap->GetMapSize(mW, mH);
	const auto& mapData = m_pMap->GetMapData();
	for (int chipY = 0; chipY < mH; ++chipY)	// 縦方向
	{
		for (int chipX = 0; chipX < mW; ++chipX)	// 横方向
		{
			auto backChipId = mapData[0][chipY * mW + chipX];
			my::MyDrawRectRotaGraph(chipX * 32, chipY * 32,
				(backChipId % 10) * 16,
				(backChipId / 8) * 16,
				16, 16,
				2.0f, 0,
				m_backHandle, true);

			auto roomchipId = mapData[1][chipY * mW + chipX];
			if (roomchipId == 0 || roomchipId == 2)
			{
				my::MyDrawRectRotaGraph((chipX * 32) - 650, chipY * 32 - 125,
					(roomchipId % 12) * 16,
					(roomchipId / 8) * 16,
					16, 16,
					2.0f, 0,
					m_roomHandle, true);
			}
		}
	}
}
