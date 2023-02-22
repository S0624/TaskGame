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
#include"../GameManager.h"
#include"DxLib.h"


namespace {
	//SceneTitle title;
	int ktest = 0;
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

	//クリアになったらタイトルへ戻す
	if (m_pField->GameClear())
	{
		CursorUpdate(input);
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
		if (num = !10)
		{
			if (m_numCount == 1)
			{
				ktest = 1;
				m_manager.ChangeScene(new SceneMain(m_manager));
				return;
			}
		}
		if (m_numCount == 2)
		{
			m_manager.ChangeScene(new SceneMain(m_manager));
			return;
		}
		if (m_numCount == 3)
		{
			m_manager.ChangeScene(new SceneTitle(m_manager));
			return;
		}
	}
}

SceneMain::SceneMain(SceneManager& manager) :
	SceneBase(manager), m_updateFunc(&SceneMain::FadeInUpdate)
{
	m_pField = new Field;
	m_pPlayer = new Player;
	m_pInformation = new FieldInformation;

	//int num = 1;
	num = m_pSelect->SelectNum(ktest);
	ktest = 0;
	//初期化
	m_pPlayer->SetField(m_pField);
	m_pInformation->StageNum(num);
	m_pInformation->Init();
	m_pInformation->SetField(m_pField);
	m_pInformation->SetPlayer(m_pPlayer);
	m_pInformation->FieldInit();

	m_handle = my::MyLoadGraph(L"../Date/Setting menu.png");		//画像の読み込み
	my::MyFontPath(L"../Font/851MkPOP_101.ttf"); // 読み込むフォントファイルのパス
	my::MyFontPath(L"../Font/komorebi-gothic.ttf"); // 読み込むフォントファイルのパス

	m_ClearFont = CreateFontToHandle(L"851マカポップ", 128, -1, -1);
	m_guideFont = CreateFontToHandle(L"木漏れ日ゴシック", 42, -1, -1);
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

void SceneMain::CursorUpdate(const InputState& input)
{
	if (m_numCount == 0)
	{
		m_numCount = 1;
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

	//「次へ」ボタンが押されたら次へ
	if (input.IsTrigger(InputType::next))
	{
		m_updateFunc = &SceneMain::FadeOutUpdate;
	}
}

void SceneMain::Draw()
{
	//背景の代わり
	DrawBox(0, 0, Game::kScreenWindth, Game::kScreenHeight, 0x00000, true);

	m_pField->Draw();		//フィールドクラスの描画処理
	m_pPlayer->Draw();		//プレイヤークラスの描画処理

	if (m_pField->GameClear())
	{
		test = 1;
		DrawGameClear();
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

void SceneMain::DrawGameClear()
{
	SetDrawBlendMode(DX_BLENDMODE_MULA, 100);		//黒くする
	DrawBox(0, 0,
		Game::kScreenWindth, Game::kScreenHeight,
		0x00000, true);		//ポーズウィンドウセロファン

	//元に戻す
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);			//通常描画に戻す
	
	DrawStringToHandle((Game::kScreenWindth -
		GetDrawStringWidthToHandle(L"Game Clear", 11, m_ClearFont)) / 2,
		175, L"Game Clear", 0xff0000, m_ClearFont);								//タイトルの表示

	constexpr int width = 400;		//ポーズ枠の幅
	constexpr int height = 300;		//ポーズ枠の高さ
	constexpr int widthPos = (Game::kScreenWindth - width) / 2;
	constexpr int heightPos = (Game::kScreenHeight - height) / 2;

	DrawExtendGraph(widthPos, heightPos,
		widthPos + width, heightPos + height,
		m_handle, true);
	if (num = !10)
	{
		DrawStringToHandle(widthPos + 50, heightPos + 70 * 1, L"次へすすむ", 0x000000, m_guideFont);
	}
	DrawStringToHandle(widthPos + 50, heightPos + 70 * 2, L"もう一度プレイ", 0x000000, m_guideFont);
	DrawStringToHandle(widthPos + 50, heightPos + 70 * 3, L"タイトルへ戻る", 0x000000, m_guideFont);

	DrawStringToHandle(widthPos + 10, heightPos + 70 * m_numCount, L"→", 0x00a000, m_guideFont);

	//DrawFormatString(400, 0, GetColor(0, 125, 255), L"ゲームクリア");
}
