#include "SceneMain.h"
#include"../Object/Player.h"
#include"../Object/Field.h"
#include"../UI/game.h"
#include"../UI/InputState.h"
#include "SceneTitle.h"
#include"ScenePause.h"
#include"SceneManager.h"
#include"DxLib.h"

namespace {

}

void SceneMain::FadeInUpdate(const InputState& input)
{
	m_fadeValue = 255 * (static_cast<float>(m_fadeTimer) / static_cast<float>(m_fadeInterval));
	if (--m_fadeTimer == 0) {
		m_updateFunc = &SceneMain::NormalUpdate;
		m_fadeValue = 0;
	}
}

void SceneMain::NormalUpdate(const InputState& input)
{
	//仮実装　クリアになったらタイトルへ戻す
	if (m_pField->GameClear())
	{
		//「次へ」ボタンが押されたら次へ
		if (input.IsTrigger(InputType::next))
		{
			m_updateFunc = &SceneMain::FadeOutUpdate;
		}
	}
	//「ポーズ」ボタンが押されたらポーズを表示
	//ゲームクリアしていたら押せなくする
	else if (input.IsTrigger(InputType::pause))
	{
		m_manager.PushScene(new ScenePause(m_manager));
	}

}

void SceneMain::FadeOutUpdate(const InputState& input)
{
	m_fadeValue = 255 * (static_cast<float>(m_fadeTimer) / static_cast<float>(m_fadeInterval));
	if (++m_fadeTimer == m_fadeInterval) {
		m_manager.ChangeScene(new SceneTitle(m_manager));
		return;
	}
}

SceneMain::SceneMain(SceneManager& manager) :
	SceneBase(manager), m_updateFunc(&SceneMain::FadeInUpdate)
{
	m_pPlayer = new Player;
	m_pField = new Field;

	Init();
}

SceneMain::~SceneMain()
{
	delete m_pPlayer;		//メモリの削除
	delete m_pField;		//メモリの削除
	//delete m_pBox;		//メモリの削除
}

void SceneMain::Init()const
{
	m_pPlayer->Init();		//プレイヤークラスの初期化
	m_pField->Init();		//フィールドクラスの初期化
	m_pPlayer->SetField(m_pField);
}

void SceneMain::Update(const InputState& input)
{
	m_pPlayer->Update(input);	//プレイヤークラスの更新処理
	m_pField->Update();		//フィールドクラスの更新処理
	(this->*m_updateFunc)(input);
}

void SceneMain::Draw()
{
	m_pField->Draw();		//フィールドクラスの描画処理
	m_pPlayer->Draw();		//プレイヤークラスの描画処理

	if (m_pField->GameClear())
	{
		DrawFormatString(400, 100, GetColor(0, 125, 255), "ゲームクリア");
	}

	//普通の描画
	//今から書く画像と、すでに描画されているスクリーンとの
	//ブレンドの仕方を指定
	SetDrawBlendMode(DX_BLENDMODE_MULA, m_fadeValue);
	//画面全体を真っ黒に塗りつぶす
	//変更したら元に戻す
	DrawBox(0, 0, Game::kScreenWindth, Game::kScreenHeight, 0x00000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	
}
