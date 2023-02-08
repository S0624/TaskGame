#include "SceneSelect.h"
#include"SceneManager.h"
#include"SceneMain.h"
#include"SceneTitle.h"
#include"../UI/InputState.h"
#include"../UI/game.h"
#include"DxLib.h"

namespace
{
	constexpr int kMaxStage = 3;
}

SceneSelect::SceneSelect(SceneManager & manager) : SceneBase(manager)
{

}
SceneSelect::~SceneSelect()
{
}

void SceneSelect::Update(const InputState& input)
{
	if (input.IsTrigger(InputType::next))
	{
		m_manager.ChangeScene(new SceneMain(m_manager));
		//m_manager.PopScene();
		return;
	}
	//else if (m_numCount == 2 && input.IsTrigger(InputType::next))
	//{
	//	//m_manager.ChangeScene(new SceneMain(m_manager));
	//	return;
	//}
	//else if (m_numCount == 3 && input.IsTrigger(InputType::next))
	//{
	//	//m_manager.ChangeScene(new SceneTitle(m_manager));
	//	return;
	//}

	if (input.IsTrigger(InputType::right))
	{
		++m_numCount;
	}
	else if (input.IsTrigger(InputType::left))
	{
		--m_numCount;
	}


	if (m_numCount < 1)
	{
		m_numCount = kMaxStage;
	}
	if (m_numCount > kMaxStage)
	{
		m_numCount = 1;
	}
}

void SceneSelect::Draw()
{
	constexpr int width = 400;		//ポーズ枠の幅
	constexpr int height = 300;		//ポーズ枠の高さ
	constexpr int widthPos = (Game::kScreenWindth - width) / 2;
	constexpr int heightPos = (Game::kScreenHeight - height) / 2;



	SetDrawBlendMode(DX_BLENDMODE_MULA, 225);		//黒くしたいときMALA
													//ポーズウィンドウセロファン			//ポーズ中メッセージ
	DrawBox(widthPos, heightPos,
		widthPos + width, heightPos + height,
		0x00000, true);

	//元に戻す
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);			//通常描画に戻す

	//ポーズ中メッセージ
	DrawString(widthPos + 10, heightPos + 10, "セレクト画面", 0xffffff);
	DrawFormatString(widthPos + 50, heightPos + 50 * 1, 0xffffff, "%d",m_numCount);

	//DrawString(widthPos + 25, heightPos + 50 * m_numCount, "▶", 0xff0000);

	DrawFormatString(500, 0, 0x0ffffff, "%d", m_numCount);
	//ポーズウインドウ枠線
	DrawBox(widthPos, heightPos,
		widthPos + width, heightPos + height,
		0xffffff, false);
}
