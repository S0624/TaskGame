#include "SceneSelect.h"
#include "SceneTitle.h"
#include"SceneMain.h"
#include"SceneTitle.h"
#include"SceneManager.h"
#include"../UI/game.h"
#include"../UI/InputState.h"
#include"../GameManager.h"
#include<DxLib.h>

namespace
{
	const char* const kTextTitle = "ステージセレクト";
	const char* const kTextExplanation = "Aボタンを押してください";
	int kSelectNum = 1;
	constexpr int kMaxStage = 10;
}
void SceneSelect::FadeInUpdate(const InputState& input)
{
	m_fadeValue = 255 * (static_cast<float>(m_fadeTimer) / static_cast<float>(m_fadeInterval));
	if (--m_fadeTimer == 0) {
		m_updateFunc = &SceneSelect::NormalUpdate;
		m_fadeValue = 0;
	}
}

void SceneSelect::NormalUpdate(const InputState& input)
{
	//「前へ」ボタンが押されたらタイトルへ
	if (input.IsTrigger(InputType::back))
	{
		m_manager.ChangeScene(new SceneTitle(m_manager));
	}
	//「次へ」ボタンが押されたら次へ
	if (input.IsTrigger(InputType::next))
	{
		m_updateFunc = &SceneSelect::FadeOutUpdate;
	}
	MoveCursor(input);
	Animation();
}

void SceneSelect::FadeOutUpdate(const InputState& input)
{
	m_fadeValue = 255 * (static_cast<float>(m_fadeTimer) / static_cast<float>(m_fadeInterval));
	if (++m_fadeTimer == m_fadeInterval) {

		m_manager.ChangeScene(new SceneMain(m_manager));
		return;
	}
}

SceneSelect::SceneSelect(SceneManager& manager) :
	SceneBase(manager),
	m_updateFunc(&SceneSelect::FadeInUpdate),
	m_selectFont(0),
	m_guideFont(0),
	m_strTitle(-1),
	m_strEx(-1),
	m_fontSize(128)
{
	m_handle = my::MyLoadGraph("../Date/select.png");		//画像の読み込み

	my::MyFontPath("../Font/komorebi-gothic.ttf"); // 読み込むフォントファイルのパス

	m_selectFont = CreateFontToHandle("木漏れ日ゴシック", m_fontSize, -1, -1);
	//m_selectFont = CreateFontToHandle("851マカポップ", m_fontSize, -1, -1);
	//m_selectFont = CreateFontToHandle("851マカポップ", 162, -1, -1);
	m_guideFont = CreateFontToHandle("木漏れ日ゴシック", 42, -1, -1);

	m_strTitle = strlen(kTextTitle);
	m_strEx = strlen(kTextExplanation);
	m_strNum = strlen("%d");

}

SceneSelect::~SceneSelect()
{
	DeleteFontToHandle(m_selectFont);
	DeleteFontToHandle(m_guideFont);
}

void SceneSelect::Update(const InputState& input)
{
	(this->*m_updateFunc)(input);
}

void SceneSelect::Draw()
{
	//背景の代わり
	DrawBox(0, 0, Game::kScreenWindth, Game::kScreenHeight, 0x00000, true);

	DrawStringToHandle((Game::kScreenWindth -
		GetDrawStringWidthToHandle(kTextTitle, m_strTitle, m_guideFont)) / 2,
		200, kTextTitle, 0xffffff, m_guideFont);								//タイトルの表示

	//点滅処理
	//if (m_displayCount / 60 < 1)
	{
		DrawStringToHandle((Game::kScreenWindth -
			GetDrawStringWidthToHandle(kTextExplanation, m_strEx, m_guideFont)) / 2,
			Game::kScreenHeight - 100, kTextExplanation, 0xffffff, m_guideFont);	//ガイドの表示
	}

	DrawSelectNum();

	//DrawFormatStringToHandle((Game::kScreenWindth -
	//	GetDrawStringWidthToHandle("%d", m_strNum, m_selectFont)) / 2,
	//	(Game::kScreenHeight / 2) - 25, 0xffffff, m_selectFont, "%d", kSelectNum);	//選択中のステージの表示



	my::MyDrawRectRotaGraph(200,
		Game::kScreenHeight - 32,			//表示座標
		32 * m_AnimeNum, 32 * 3,			//切り取り左上
		32, 32,							//幅、高さ
		3.0f, 0.0f,						//拡大率、回転角度
		m_handle, true);


	//今から書く画像と、すでに描画されているスクリーンとの
	//ブレンドの仕方を指定
	SetDrawBlendMode(DX_BLENDMODE_MULA, static_cast<int> (m_fadeValue));
	//画面全体を真っ黒に塗りつぶす
	//変更したら元に戻す
	DrawBox(0, 0, Game::kScreenWindth, Game::kScreenHeight, 0x00000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void SceneSelect::DrawSelectNum()
{
	int X = 0;		//何番目の数字か
	int Y = 0;		//何番目の数字か
	int index = m_fontSize + 20;		//文字をずらす
	int posX = ((Game::kScreenWindth -
		GetDrawStringWidthToHandle("%d", m_strNum, m_selectFont)) / 2)
		- (index * 2);

	int posY = (Game::kScreenHeight / 2) - (index * 2);


	for (int i = 0; i < kMaxStage; i++)
	{

		int indexUp = 0;
		int color = 0xffffff;
		const char*  letter = "%d";
		
		X = i % 5;	//改行したときに文字がずれないように割った余りをXに代入する

		//五個ずつで改行する
		if (i % 5 == 0)
		{
			Y++;
		}

		if (i + 1 == kSelectNum)
		{
			indexUp = -10;
			color = 0xff0000;
		}

		if (i < 9)
		{
			letter = "0%d";
		}

		/*DrawBox(posX + index * X - 5,
			posY + index * Y - 5,
			index + posX + index * X - 5,
			index + posY + index * Y - 5, 0xaaaaf0, true);*/

		DrawFormatStringToHandle(posX + index * X,
			(posY + index * Y) + indexUp, color, m_selectFont, letter, i + 1);	//選択中のステージの表示
		

	   
	   DrawBox(posX + index * X - 5,
		posY + index * Y - 5,
		index + posX + index * X - 5,
		index + posY + index * Y - 5, 0x00a000, false);
	}
}

int SceneSelect::SelectNum()
{
	int selectNum = 0;
	selectNum = kSelectNum;
	return selectNum;
}

void SceneSelect::MoveCursor(const InputState& input)
{
	if (input.IsTrigger(InputType::right))
	{
		++kSelectNum;
	}
	else if (input.IsTrigger(InputType::left))
	{
		--kSelectNum;
	}
	else if (input.IsTrigger(InputType::up))
	{
		kSelectNum -= 5;
		if (kSelectNum < 1)
		{
			kSelectNum += 10;
		}
		if (kSelectNum > kMaxStage)
		{
			kSelectNum *= -1;
		}
	}
	else if (input.IsTrigger(InputType::down))
	{
		kSelectNum += 5;
		if (kSelectNum < 1)
		{
			kSelectNum += 5;
		}
		if (kSelectNum > kMaxStage)
		{
			kSelectNum -= 10;
			//kSelectNum *= -1;
		}
	}

	if (kSelectNum < 1)
	{
		kSelectNum = kMaxStage;
	}
	if (kSelectNum > kMaxStage)
	{
		kSelectNum = 1;
	}


}

void SceneSelect::Animation()
{
	m_freamStop++;
	if (m_freamStop >= 60)
	{
		m_freamAnime++;
		if (m_freamAnime >= 10)
		{
			m_AnimeNum++;
			m_freamAnime = 0;
		}
		if (m_AnimeNum > 3)
		//if (m_num > 4)
		{
			m_AnimeNum = 0;
			m_freamStop = 0;
		}
	}
}
