#include "ScenePause.h"
#include"SceneManager.h"
#include"SceneMain.h"
#include"SceneTitle.h"
#include"../UI/InputState.h"
#include"../UI/game.h"
#include"../GameManager.h"
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
	my::MyFontPath(L"../Font/komorebi-gothic.ttf"); // 読み込むフォントファイルのパス
	kPauseNum = 1;

	m_enterSESound = LoadSoundMem(L"../Sound/SE1.mp3");
	m_moveSESound = LoadSoundMem(L"../Sound/SE2.mp3");
	m_pauseSESound = LoadSoundMem(L"../Sound/Pause2.mp3");

	m_pauseFont = CreateFontToHandle(L"木漏れ日ゴシック", 32, -1, -1);
	m_guideFont = CreateFontToHandle(L"木漏れ日ゴシック", 42, -1, -1);

	ChangeNextPlayVolumeSoundMem(160, m_enterSESound);
	ChangeNextPlayVolumeSoundMem(160, m_moveSESound);
	ChangeNextPlayVolumeSoundMem(150, m_pauseSESound);

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
	DrawStringToHandle(10, 20, L"Pause", 0x000000, m_pauseFont);
	DrawStringToHandle(50, 60 * 1, L"ゲームに戻る", 0x000000, m_guideFont);
	DrawStringToHandle(50, 60 * 2, L"リトライ", 0x000000, m_guideFont);
	DrawStringToHandle(50, 60 * 3, L"タイトル", 0x000000, m_guideFont);

	SetDrawScreen(DX_SCREEN_BACK);
}

void ScenePause::Update(const InputState& input)
{
	m_magnification += m_Increase;
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
		PlaySoundMem(m_pauseSESound, DX_PLAYTYPE_BACK);
		kPauseNum = 1;
		m_Increase *= -1;
		return;
	}
	else if (input.IsTrigger(InputType::next))
	{
		PlaySoundMem(m_enterSESound, DX_PLAYTYPE_BACK);
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
		kPauseNum = 3;
	}
	if (kPauseNum > 3)
	{
		kPauseNum = 1;
	}
	if (kPauseNum != count)
	{
		PlaySoundMem(m_moveSESound, DX_PLAYTYPE_BACK);
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
		DrawStringToHandle(kWidthPos + 10, kHeightPos + 60 * kPauseNum, L"→", 0x00a000, m_guideFont);
	}
}

int ScenePause::CursolUpdate()
{
	int num = kPauseNum;
	kPauseNum = 1;
	return 	num;
}
