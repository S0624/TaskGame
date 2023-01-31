#include "SceneTitle.h"
#include"SceneMain.h"
#include"SceneManager.h"
#include"../UI/game.h"
#include"../UI/InputState.h"
#include<DxLib.h>
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
		m_updateFunc = &SceneTitle::FadeOutUpdate;
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
	SceneBase(manager), m_updateFunc(&SceneTitle::FadeInUpdate)
{

}

void SceneTitle::Update(const InputState& input)
{
	(this->*m_updateFunc)(input);
}

void SceneTitle::Draw()
{
	DrawBox(0, 0, Game::kScreenWindth, Game::kScreenHeight, 0x00000, true);
	//普通の描画
	DrawBox(200, 200, 300, 300, 0xffffff, true);
	DrawString(400, 200,"タイトル", 0x00ffff, true);
	//今から書く画像と、すでに描画されているスクリーンとの
	//ブレンドの仕方を指定
	SetDrawBlendMode(DX_BLENDMODE_MULA, m_fadeValue);
	//DrawBox(0, 0, 540, 480, 0x00000, true);
	//画面全体を真っ黒に塗りつぶす
	//DrawGraph(0, 200, GradH_, true);
	//変更したら元に戻す
	DrawBox(0, 0, Game::kScreenWindth, Game::kScreenHeight, 0x00000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	//DrawString(300, 200, L"TitleScene", 0xfffff);
}
