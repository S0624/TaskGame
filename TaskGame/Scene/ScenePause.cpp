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
}

ScenePause::ScenePause(SceneManager& manager) : SceneBase(manager)
{
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
}
ScenePause::~ScenePause()
{
	delete pMain;
	DeleteFontToHandle(m_pauseFont);
	DeleteFontToHandle(m_guideFont);
}

void ScenePause::Update(const InputState& input)
{
	if (input.IsTrigger(InputType::pause))
	{
		PlaySoundMem(m_pauseSESound, DX_PLAYTYPE_BACK);
		kPauseNum = 1;
		m_manager.PopScene();
		return;
	}
	else if (input.IsTrigger(InputType::next))
	{
		PlaySoundMem(m_enterSESound, DX_PLAYTYPE_BACK);
		m_manager.PopScene();
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
	constexpr int width = 400;		//ポーズ枠の幅
	constexpr int height = 300;		//ポーズ枠の高さ
	constexpr int widthPos = (Game::kScreenWindth - width) / 2;
	constexpr int heightPos = (Game::kScreenHeight - height) / 2;

	m_movingX += 10;
	if (m_movingX >= widthPos)
	{
		m_movingX = widthPos;
	}

	SetDrawBlendMode(DX_BLENDMODE_MULA, 150);		//黒くしたいときMALA
													//ポーズウィンドウセロファン			//ポーズ中メッセージ

	DrawBox(0, 0,
		Game::kScreenWindth, Game::kScreenHeight,
		0x00000, true);


	//元に戻す
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);			//通常描画に戻す

	DrawExtendGraph(m_movingX, heightPos,
		m_movingX + width, heightPos + height,
		m_handle, true);

	//ポーズ中メッセージ

	DrawStringToHandle(m_movingX + 10, heightPos + 20, L"Pause", 0x000000, m_pauseFont);
	DrawStringToHandle(m_movingX + 50, heightPos + 60 * 1, L"ゲームに戻る", 0x000000, m_guideFont);
	DrawStringToHandle(m_movingX + 50, heightPos + 60 * 2, L"リトライ", 0x000000, m_guideFont);
	DrawStringToHandle(m_movingX + 50, heightPos + 60 * 3, L"タイトル", 0x000000, m_guideFont);

	//DrawString(widthPos + 10, heightPos + 10, "ポーズ画面（仮実装）", 0x000000);
	//DrawString(widthPos + 50, heightPos + 50 * 1, "ゲームに戻る（仮実装）", 0x000000);
	//DrawString(widthPos + 50, heightPos + 50 * 2, "リトライ（仮実装）", 0x000000);
	//DrawString(widthPos + 50, heightPos + 50 * 3, "タイトル（仮実装）", 0x000000);
	//
	//if (m_numCount == 1)
	//{
	//	DrawString(widthPos + 50 + 10, heightPos + 50 * 1, "ゲームに戻る（仮実装）", 0xffffff);
	//}
	//else
	//{
	//	DrawString(widthPos + 50, heightPos + 50 * 1, "ゲームに戻る（仮実装）", 0xffffff);
	//}
	//if (m_numCount == 2)
	//{
	//	DrawString(widthPos + 50 + 10, heightPos + 50 * 2, "リトライ（仮実装）", 0xffffff);
	//}
	//else
	//{
	//	DrawString(widthPos + 50, heightPos + 50 * 2, "リトライ（仮実装）", 0xffffff);
	//}
	//if (m_numCount == 3)
	//{
	//	DrawString(widthPos + 50 + 10, heightPos + 50 * 3, "タイトル（仮実装）", 0xffffff);
	//}
	//else
	//{
	//	DrawString(widthPos + 50, heightPos + 50 * 3, "タイトル（仮実装）", 0xffffff);
	//}
	DrawStringToHandle(m_movingX + 10, heightPos + 60 * kPauseNum, L"→", 0x00a000, m_guideFont);

}

int ScenePause::CursolUpdate()
{
	int num = kPauseNum;
	kPauseNum = 1;
	return 	num;
}
