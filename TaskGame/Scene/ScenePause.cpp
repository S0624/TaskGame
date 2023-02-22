#include "ScenePause.h"
#include"SceneManager.h"
#include"SceneMain.h"
#include"SceneTitle.h"
#include"../UI/InputState.h"
#include"../UI/game.h"
#include"../GameManager.h"
#include"DxLib.h"

ScenePause::ScenePause(SceneManager& manager) : SceneBase(manager)
{
	m_handle = my::MyLoadGraph(L"../Date/Setting menu.png");		//画像の読み込み
	my::MyFontPath(L"../Font/komorebi-gothic.ttf"); // 読み込むフォントファイルのパス

	m_pauseFont = CreateFontToHandle(L"木漏れ日ゴシック", 32, -1, -1);
	m_guideFont = CreateFontToHandle(L"木漏れ日ゴシック", 42, -1, -1);
}
ScenePause::~ScenePause()
{
	DeleteFontToHandle(m_pauseFont);
	DeleteFontToHandle(m_guideFont);
}

void ScenePause::Update(const InputState& input)
{
	if (input.IsTrigger(InputType::pause) || (m_numCount == 1 && input.IsTrigger(InputType::next)))
	{
		m_manager.PopScene();
		return;
	}
	else if (m_numCount == 2 && input.IsTrigger(InputType::next))
	{
		m_manager.ChangeScene(new SceneMain(m_manager));
		return;
	}
	else if (m_numCount == 3 && input.IsTrigger(InputType::next))
	{
		m_manager.ChangeScene(new SceneTitle(m_manager));
		return;
	}

	if (input.IsTrigger(InputType::down))
	{
		++m_numCount;
	}
	else if (input.IsTrigger(InputType::up))
	{
		--m_numCount;
	}


	if (m_numCount < 1)
	{
		m_numCount = 3;
	}
	if (m_numCount > 3)
	{
		m_numCount = 1;
	}
}

void ScenePause::Draw()
{
	constexpr int width = 400;		//ポーズ枠の幅
	constexpr int height = 300;		//ポーズ枠の高さ
	constexpr int widthPos = (Game::kScreenWindth - width) / 2;
	constexpr int heightPos = (Game::kScreenHeight - height) / 2;


	SetDrawBlendMode(DX_BLENDMODE_MULA, 150);		//黒くしたいときMALA
													//ポーズウィンドウセロファン			//ポーズ中メッセージ

	DrawBox(0, 0,
		Game::kScreenWindth, Game::kScreenHeight,
		0x00000, true);


	//元に戻す
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);			//通常描画に戻す

	DrawExtendGraph(widthPos, heightPos,
		widthPos + width, heightPos + height,
		m_handle, true);

	//ポーズ中メッセージ

	DrawStringToHandle(widthPos + 10, heightPos + 20, L"Pause", 0x000000, m_pauseFont);
	DrawStringToHandle(widthPos + 50, heightPos + 60 * 1, L"ゲームに戻る", 0x000000, m_guideFont);
	DrawStringToHandle(widthPos + 50, heightPos + 60 * 2, L"リトライ", 0x000000, m_guideFont);
	DrawStringToHandle(widthPos + 50, heightPos + 60 * 3, L"タイトル", 0x000000, m_guideFont);

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
	DrawStringToHandle(widthPos + 10, heightPos + 60 * m_numCount, L"→", 0x00a000, m_guideFont);

}
