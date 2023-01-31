#include "ScenePause.h"
#include"SceneManager.h"
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
	if (input.IsTrigger(InputType::pause))
	{
		m_manager.PopScene();
		return;
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
	//SetDrawBlendMode(DX_BLENDMODE_ADD, 128);		//白くしたいときはADD
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

	//ポーズウインドウ枠線
	DrawBox(widthPos, heightPos,
		widthPos + width, heightPos + height,
		0xffffff, false);
}
