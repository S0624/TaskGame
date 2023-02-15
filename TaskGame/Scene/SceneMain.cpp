#include "SceneMain.h"
#include"../Object/Field.h"
#include"../Object/Player.h"
#include"../UI/game.h"
#include"../UI/InputState.h"
#include "SceneSelect.h"
#include "SceneTitle.h"
#include"ScenePause.h"
#include"SceneManager.h"
#include"../Object/FieldInformation.h"
#include"DxLib.h"


namespace {
	//SceneTitle title;
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
	m_pField = new Field;
	m_pPlayer = new Player;
	m_pInformation = new FieldInformation;
	
	int num = 1;
	num = m_pSelect->SelectNum();

	//初期化
	m_pPlayer->SetField(m_pField);
	m_pInformation->StageNum(num);
	m_pInformation->Init();
	m_pInformation->SetField(m_pField);
	m_pInformation->SetPlayer(m_pPlayer);
	m_pInformation->FieldInit();
}

SceneMain::~SceneMain()
{
	delete m_pField;		//メモリの削除
	delete m_pPlayer;		//メモリの削除
	delete m_pInformation;	//メモリの削除
	delete m_pSelect;		//メモリの削除
}

void SceneMain::Update(const InputState& input)
{
	m_pField->Update();		//フィールドクラスの更新処理
	m_pPlayer->Update(input);	//プレイヤークラスの更新処理
	(this->*m_updateFunc)(input);
}

void SceneMain::Draw()
{
	//背景の代わり
	DrawBox(0, 0, Game::kScreenWindth, Game::kScreenHeight, 0x00000, true);

	m_pField->Draw();		//フィールドクラスの描画処理
	m_pPlayer->Draw();		//プレイヤークラスの描画処理

	if (m_pField->GameClear())
	{
		DrawFormatString(400, 0, GetColor(0, 125, 255), "ゲームクリア");
	}

	//普通の描画
	//今から書く画像と、すでに描画されているスクリーンとの
	//ブレンドの仕方を指定
	SetDrawBlendMode(DX_BLENDMODE_MULA, static_cast<int> (m_fadeValue));
	//画面全体を真っ黒に塗りつぶす
	//変更したら元に戻す
	DrawBox(0, 0, Game::kScreenWindth, Game::kScreenHeight, 0x00000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	
}
