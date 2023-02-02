#include "ScenePause.h"
#include"SceneManager.h"
#include"SceneMain.h"
#include"SceneTitle.h"
#include"../UI/InputState.h"
#include"../UI/game.h"
#include"DxLib.h"

ScenePause::ScenePause(SceneManager& manager) : SceneBase(manager)
{

}
ScenePause::~ScenePause()
{
}

void ScenePause::Update(const InputState& input)
{
	if (input.IsTrigger(InputType::pause) || (m_numCount == 1 &&input.IsTrigger(InputType::next)))
	{
		m_manager.PopScene();
		return;
	}
	else if(m_numCount == 2 && input.IsTrigger(InputType::next))
	{
		m_manager.ChangeScene(new SceneMain(m_manager));
		return;
	}
	else if(m_numCount == 3 && input.IsTrigger(InputType::next))
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
	//constexpr int pw_width = 400;		//ポーズ枠の幅
	//constexpr int pw_height = 300;		//ポーズ枠の高さ
	//constexpr int pw_start_x = (Game::kScreenWindth - pw_width) / 2;
	//constexpr int pw_start_y = (Game::kScreenHeight - pw_height) / 2;

	constexpr int width = 400;		//ポーズ枠の幅
	constexpr int height = 300;		//ポーズ枠の高さ
	constexpr int widthPos = (640 - width) / 2;
	constexpr int heightPos = (480 - height) / 2;


	SetDrawBlendMode(DX_BLENDMODE_MULA, 225);		//黒くしたいときMALA
	//ポーズウィンドウセロファン			//ポーズ中メッセージ
	DrawBox(widthPos, heightPos,
		widthPos + width, heightPos + height,
		0x00000, true);

	//元に戻す
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);			//通常描画に戻す

	//ポーズ中メッセージ
	DrawString(widthPos + 10, heightPos + 10, "ポーズ画面（仮実装）", 0xffffff);
	DrawString(widthPos + 50, heightPos + 50 * 1, "ゲームに戻る（仮実装）", 0xffffff);
	DrawString(widthPos + 50, heightPos + 50 * 2, "リトライ（仮実装）", 0xffffff);
	DrawString(widthPos + 50, heightPos + 50 * 3, "タイトル（仮実装）", 0xffffff);
	
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

	DrawString(widthPos + 25, heightPos + 50 * m_numCount, "→", 0x00ffff);
	//DrawString(pw_start_x + 90, y + yoffset, L"▶", 0xff0000);

	DrawFormatString(500, 0, 0x0ffffff, "%d", m_numCount);
	//ポーズウインドウ枠線
	DrawBox(widthPos, heightPos,
		widthPos + width, heightPos + height,
		0xffffff, false);
}
