#include "ScenePause.h"
#include"SceneManager.h"
#include"SceneMain.h"
#include"SceneTitle.h"
#include"../UI/InputState.h"
#include"../UI/game.h"
#include"../GameManager.h"
#include"../SoundManager.h"
#include"DxLib.h"

namespace
{
	int kPauseNum = 1;
	constexpr int kWidth = 400;		//ポーズ枠の幅
	constexpr int kHeight = 300;		//ポーズ枠の高さ
	constexpr int kWidthPos = (Game::kScreenWindth - kWidth) / 2;
	constexpr int kHeightPos = (Game::kScreenHeight - kHeight) / 2;
}

ScenePause::ScenePause(SceneManager& manager) : SceneBase(manager)
{
	//m_handle = my::MyLoadGraph(L"../Date/pause.png");		//画像の読み込み
	m_handle = my::MyLoadGraph(L"../Date/Setting menu.png");		//画像の読み込み
	my::MyFontPath(L"../Font/erizifont.otf"); // 読み込むフォントファイルのパス
	kPauseNum = 1;

	m_pauseFont = CreateFontToHandle(L"HG丸ｺﾞｼｯｸM-PRO", 30, -1, -1);
	m_guideFont = CreateFontToHandle(L"HG丸ｺﾞｼｯｸM-PRO", 40, -1, -1);


	PauseInit();
}
ScenePause::~ScenePause()
{
	delete pMain;
	DeleteGraph(m_handle);
	DeleteGraph(m_pausehandle);
	DeleteFontToHandle(m_pauseFont);
	DeleteFontToHandle(m_guideFont);
}

void ScenePause::PauseInit()
{
	m_pausehandle = MakeScreen(kWidth - 8 ,kHeight);
	SetDrawScreen(m_pausehandle);
	DrawExtendGraph(0,0,
		kWidth , kHeight,
		m_handle, true);


	//ポーズ中メッセージ
	DrawStringToHandle(15, 20, L"Pause", 0x000000, m_pauseFont);
	DrawStringToHandle(45, 60 * 1, L"ゲームに戻る", 0x000000, m_guideFont);
	DrawStringToHandle(45, 60 * 2, L"リトライ", 0x000000, m_guideFont);
	DrawStringToHandle(45, 60 * 3, L"ステージセレクト", 0x000000, m_guideFont);
	DrawStringToHandle(45, 60 * 4, L"タイトル", 0x000000, m_guideFont);

	SetDrawScreen(DX_SCREEN_BACK);
}

void ScenePause::Update(const InputState& input)
{
	m_magnification += static_cast<float>(m_Increase);
	m_cursolFlag = false;
	if (m_magnification > 1.0f)
	{
		m_magnification = 1.0f;
		m_cursolFlag = true;
	}
	if (m_magnification < 0.0f)
	{
		m_magnification = 0.0f;
		m_manager.PopScene();
	}

	if (input.IsTrigger(InputType::pause))
	{
		SoundManager::GetInstance().Play(L"Pause21");
		kPauseNum = 1;
		m_Increase *= -1;
		return;
	}
	else if (input.IsTrigger(InputType::next))
	{
		SoundManager::GetInstance().Play(L"SE1");
		m_Increase *= -1;
		return;
	}

	int count = kPauseNum;

	if (input.IsTrigger(InputType::down))
	{
		++kPauseNum;
	}
	else if (input.IsTrigger(InputType::up))
	{
		--kPauseNum;
	}


	if (kPauseNum < 1)
	{
		kPauseNum = 4;
	}
	if (kPauseNum > 4)
	{
		kPauseNum = 1;
	}
	if (kPauseNum != count)
	{
		SoundManager::GetInstance().Play(L"SE2");
	}
}

void ScenePause::Draw()
{
	SetDrawBlendMode(DX_BLENDMODE_MULA, 150);		//黒くしたいときMALA
													//ポーズウィンドウセロファン			//ポーズ中メッセージ
	DrawBox(0, 0,
		Game::kScreenWindth, Game::kScreenHeight,
		0x00000, true);


	//元に戻す
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);			//通常描画に戻す

	DrawRotaGraph(kWidthPos + 200, kHeightPos + 150,
		m_magnification, 0.0f, m_pausehandle, true);

	if (m_cursolFlag)
	{
		DrawStringToHandle(kWidthPos + 10, kHeightPos + 60 * kPauseNum, L"▶", 0x00a000, m_guideFont);
	}
}

int ScenePause::CursolUpdate()
{
	int num = kPauseNum;
	kPauseNum = 1;
	return 	num;
}
