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
#include"../Object/MapChip.h"
#include"../GameManager.h"
#include"../Object/CreateEffect.h"
#include"DxLib.h"

namespace {
	int kNextStage = 0;
}

//フェード処理
void SceneMain::FadeInUpdate(const InputState& input)
{
	//SetVolumeMusic(static_cast<int>(255 - 255.0f / 60.0f * static_cast<int>(60 - m_fadeTimer)));
	m_fadeValue = 255 * (static_cast<float>(m_fadeTimer) / static_cast<float>(m_fadeInterval));
	if (--m_fadeTimer == 0) {
		m_updateFunc = &SceneMain::NormalUpdate;
		m_fadeValue = 0;
	}
}

//アップデート処理
void SceneMain::NormalUpdate(const InputState& input)
{
	m_pField->Update();		//フィールドクラスの更新処理
	m_pPlayer->Update(input);	//プレイヤークラスの更新処理

	//現在のステップ数
	m_stepNum = m_pPlayer->MoveStep();

	if (!m_pField->MoveBox())
	{
		if (m_pField->GameClear())
		{
			m_pEffect->Update();
		}
		else if (m_stepNum >= m_LimitNum)
		{
			m_gameOverFlag = true;
		}
	}
	//クリアしてフェードが掛かり切ったらセレクトしてもらう
	if (m_fadeColor)
	{
		CursorUpdate(input);
	}
	//「ポーズ」ボタンが押されたらポーズを表示
	//ゲームクリアしていたら押せなくする
	else if (input.IsTrigger(InputType::pause))
	{
		PlaySoundMem(m_pauseSESound, DX_PLAYTYPE_BACK);
		m_manager.PushScene(new ScenePause(m_manager));
	}

	m_pauseNum = m_pPause->CursolUpdate();
	if (m_pauseNum == 2 || m_pauseNum == 3)
	{
		m_selectNum = m_pauseNum;
		m_updateFunc = &SceneMain::FadeOutUpdate;
	}
}

//フェード処理
void SceneMain::FadeOutUpdate(const InputState& input)
{
	m_fadeValue = 255 * (static_cast<float>(m_fadeTimer) / static_cast<float>(m_fadeInterval));
	if (++m_fadeTimer == m_fadeInterval) {
		if (m_numCount == 3 || m_selectNum == 3)
		{
			kNextStage = 0;
			m_manager.ChangeScene(new SceneTitle(m_manager));
			return;
		}
		if (m_numCount == 2 || m_selectNum == 2)
		{
			kNextStage = 0;
			m_manager.ChangeScene(new SceneMain(m_manager));
			return;
		}
		if (m_stageNum != 10)
		{
			if (m_numCount == 1)
			{
				kNextStage = 1;
				m_manager.ChangeScene(new SceneMain(m_manager));
				return;
			}
		}
	}
}

//ロード系の初期化
void SceneMain::InitLoad()
{
	m_handle = my::MyLoadGraph(L"../Date/Setting menu.png");		//画像の読み込み
	my::MyFontPath(L"../Font/851MkPOP_101.ttf"); // 読み込むフォントファイルのパス
	my::MyFontPath(L"../Font/komorebi-gothic.ttf"); // 読み込むフォントファイルのパス
	my::MyFontPath(L"../Font/erizifont.otf"); // 読み込むフォントファイルのパス

	m_clearFont = CreateFontToHandle(L"851マカポップ", 128, -1, -1);
	m_guideFont = CreateFontToHandle(L"木漏れ日ゴシック", 42, -1, -1);
	m_scoreFont = CreateFontToHandle(L"えり字", 64, -1, -1);

	m_backHandle = my::MyLoadGraph(L"../Date/Grass.png");
	m_pMap->Load(L"../Date/room.fmf");
}

//サウンド系の初期化
void SceneMain::InitSound()
{
	m_enterSESound = LoadSoundMem(L"../Sound/SE1.mp3");
	m_moveSESound = LoadSoundMem(L"../Sound/SE2.mp3");
	m_pauseSESound = LoadSoundMem(L"../Sound/Pause1.mp3");
	m_clearSESound = LoadSoundMem(L"../Sound/GameClear.mp3");
	m_overSESound = LoadSoundMem(L"../Sound/GameOver.mp3");
	m_gamePlayBgSound = LoadSoundMem(L"../Sound/GamePlayBg.mp3");

	PlaySoundMem(m_gamePlayBgSound, DX_PLAYTYPE_LOOP, false);
}

//背景表示の処理
void SceneMain::DrawBackground()
{
	//背景
	int mW, mH;
	m_pMap->GetMapSize(mW, mH);
	const auto& mapData = m_pMap->GetMapData();
	for (int chipY = 0; chipY < mH; ++chipY)	// 縦方向
	{
		for (int chipX = 0; chipX < mW; ++chipX)	// 横方向
		{
			auto backChipId = mapData[0][chipY * mW + chipX];
			my::MyDrawRectRotaGraph(chipX * 32, chipY * 32,
				(backChipId % 10) * 16,
				(backChipId / 8) * 16,
				16, 16,
				2.0f, 0,
				m_backHandle, true);
		}
	}
	SetDrawBlendMode(DX_BLENDMODE_MULA, 50);		//黒くする
	DrawBox(0, 0,
		Game::kScreenWindth, Game::kScreenHeight,
		0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);			//通常描画に戻す
}

//ゲームクリアの処理
void SceneMain::DrawGameClear()
{
	SetDrawBlendMode(DX_BLENDMODE_MULA, m_setBlend);		//黒くする
	DrawBox(0, 0,
		Game::kScreenWindth, Game::kScreenHeight,
		0x00000, true);		//ポーズウィンドウセロファン
	m_setBlend++;

	if (m_setBlend < 100)
	{
		if (m_setBlend == 90)
		{
			PlaySoundMem(m_clearSESound, DX_PLAYTYPE_BACK, true);
		}
		return;
	}
	if (m_setBlend > 100)
	{
		m_fadeColor = true;
		m_setBlend = 100;
	}

	DeleteSoundMem(m_gamePlayBgSound);

	//元に戻す
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);			//通常描画に戻す


	//m_pEffect->Draw();
	DrawStringToHandle((Game::kScreenWindth -
		GetDrawStringWidthToHandle(L"Game Clear", 11, m_clearFont)) / 2,
		175, L"Game Clear", 0xff0000, m_clearFont);								//タイトルの表示

	constexpr int width = 400;		//ポーズ枠の幅
	constexpr int height = 300;		//ポーズ枠の高さ
	constexpr int widthPos = (Game::kScreenWindth - width) / 2;
	constexpr int heightPos = (Game::kScreenHeight - height) / 2;

	DrawExtendGraph(widthPos, heightPos,
		widthPos + width, heightPos + height,
		m_handle, true);
	if (m_stageNum != 10)
	{
		DrawStringToHandle(widthPos + 50, heightPos + m_index, L"次へすすむ", 0x000000, m_guideFont);
	}
	DrawStringToHandle(widthPos + 50, heightPos + m_index * 2, L"もう一度プレイ", 0x000000, m_guideFont);
	DrawStringToHandle(widthPos + 50, heightPos + m_index * 3, L"タイトルへ戻る", 0x000000, m_guideFont);

	DrawStringToHandle(widthPos + 10, heightPos + m_index * m_numCount, L"→", 0x00a000, m_guideFont);
}

//ゲームオーバーの処理
void SceneMain::DrawGameOver()
{
	m_index = 50;
	if (m_numCount == 1)
	{
		m_minNum = 2;
		m_numCount = m_minNum;
	}
	SetDrawBlendMode(DX_BLENDMODE_MULA, m_setBlend);		//黒くする
	DrawBox(0, 0,
		Game::kScreenWindth, Game::kScreenHeight,
		0x00000, true);		//ポーズウィンドウセロファン
	m_setBlend++;

	if (m_setBlend == 140)
	{
		PlaySoundMem(m_overSESound, DX_PLAYTYPE_BACK, true);
	}
	if (m_setBlend < 150)
	{
		return;
	}
	m_fadeColor = true;
	m_setBlend = 150;

	DeleteSoundMem(m_gamePlayBgSound);

	//元に戻す
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);			//通常描画に戻す

	DrawStringToHandle((Game::kScreenWindth -
		GetDrawStringWidthToHandle(L"Game Over...", 11, m_clearFont)) / 2,
		175, L"Game Over...", 0xa000a0, m_clearFont);								//タイトルの表示

	constexpr int width = 400;		//ポーズ枠の幅
	constexpr int height = 300;		//ポーズ枠の高さ
	constexpr int widthPos = (Game::kScreenWindth - width) / 2;
	constexpr int heightPos = (Game::kScreenHeight - height) / 2;

	DrawExtendGraph(widthPos, heightPos,
		widthPos + width, heightPos + height,
		m_handle, true);

	DrawStringToHandle(widthPos + 50, heightPos + m_index * 2, L"もう一度プレイ", 0x000000, m_guideFont);
	DrawStringToHandle(widthPos + 50, heightPos + m_index * 3, L"タイトルへ戻る", 0x000000, m_guideFont);

	DrawStringToHandle(widthPos + 10, heightPos + m_index * m_numCount, L"→", 0x00a000, m_guideFont);
}

//右上のスコアを表示させる処理
void SceneMain::DrawScore()
{
	SetDrawBlendMode(DX_BLENDMODE_MULA, 200);		//黒くする
	//仮の数値
	DrawBox(Game::kScreenWindth - 450, 100, Game::kScreenWindth - 100, 250, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);			//通常描画に戻す

	DrawFormatStringToHandle(Game::kScreenWindth - 450, 100,
		0xffffff, m_scoreFont, L"STAGE:%d", m_stageNum);
	DrawFormatStringToHandle(Game::kScreenWindth - 450, 100 + 48,
		0xffffff, m_scoreFont, L"STEP :%d",m_stepNum);
	DrawFormatStringToHandle(Game::kScreenWindth - 450, 100 + 96,
		0xffffff, m_scoreFont, L"LIMIT:%d", m_LimitNum);
}

//コンストラクタ
SceneMain::SceneMain(SceneManager& manager) :
	SceneBase(manager), m_updateFunc(&SceneMain::FadeInUpdate)
{
	m_pField = new Field;
	m_pPlayer = new Player;
	m_pInformation = new FieldInformation;
	m_pMap = new MapChip;
	m_pEffect = std::make_shared<CreateEffect>();

	m_stageNum = m_pSelect->SelectNum(kNextStage);
	kNextStage = 0;
	//初期化
	m_pPlayer->SetField(m_pField);
	m_pInformation->StageNum(m_stageNum);
	m_pInformation->Init();
	m_pInformation->SetField(m_pField);
	m_pInformation->SetPlayer(m_pPlayer);
	m_pInformation->FieldInit();
	//ステージのリミット
	m_LimitNum = m_pInformation->StepLimit();

	if (m_stageNum == 10)
	{
		m_index = 50;
	}

	if (m_numCount == 0)
	{
		if (m_stageNum != 10)
		{
			m_minNum = 1;
			m_numCount = m_minNum;
		}
		else
		{
			m_minNum = 2;
			m_numCount = m_minNum;
		}
	}

	InitLoad();
	InitSound();
}

//デストラクタ
SceneMain::~SceneMain()
{
	delete m_pField;		//メモリの削除
	delete m_pPlayer;		//メモリの削除
	delete m_pInformation;	//メモリの削除
	delete m_pSelect;		//メモリの削除
	delete m_pMap;
	//delete m_pPause;

	DeleteGraph(m_handle);
	DeleteGraph(m_backHandle);
	DeleteSoundMem(m_enterSESound);
	DeleteSoundMem(m_moveSESound);
	DeleteSoundMem(m_pauseSESound);
	DeleteSoundMem(m_clearSESound);
	DeleteSoundMem(m_gamePlayBgSound);
	DeleteFontToHandle(m_clearFont);
	DeleteFontToHandle(m_guideFont);
}

//アップデート処理
void SceneMain::Update(const InputState& input)
{
	ChangeVolumeSoundMem(255 - static_cast<int>(m_fadeValue), m_gamePlayBgSound);
	(this->*m_updateFunc)(input);
}

//ゲームクリアしたときのCursorを動かす処理
void SceneMain::CursorUpdate(const InputState& input)
{
	int count = m_numCount;
	
	if (input.IsTrigger(InputType::down))
	{
		++m_numCount;
	}
	else if (input.IsTrigger(InputType::up))
	{
		--m_numCount;
	}
	if (m_numCount < m_minNum)
	{
		m_numCount = 3;
	}
	if (m_numCount > 3)
	{
		m_numCount = m_minNum;
	}


	//「次へ」ボタンが押されたら次へ
	if (input.IsTrigger(InputType::next))
	{
		PlaySoundMem(m_enterSESound, DX_PLAYTYPE_BACK);
		m_updateFunc = &SceneMain::FadeOutUpdate;
	}
	if (m_numCount != count)
	{
		PlaySoundMem(m_moveSESound, DX_PLAYTYPE_BACK);
	}
}

//描画処理
void SceneMain::Draw()
{
	//背景の代わり
	DrawBackground();

	m_pField->Draw();		//フィールドクラスの描画処理
	m_pPlayer->Draw();		//プレイヤークラスの描画処理
	DrawScore();
	if (m_pField->GameClear())
	{
		DrawGameClear();
	}
	if (m_gameOverFlag)
	{
		DrawGameOver();
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