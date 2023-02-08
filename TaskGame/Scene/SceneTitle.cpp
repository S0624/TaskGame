#include "SceneTitle.h"
#include"SceneMain.h"
#include"SceneManager.h"
#include"SceneSelect.h"
#include"../UI/game.h"
#include"../UI/InputState.h"
#include<DxLib.h>

namespace
{
	const char* const kTextTitle = "�^�C�g��";
	const char* const kTextExplanation = "�{�^���������Ă�������";
	int kNum = 1;
	constexpr int kMaxStage = 5;
}

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
	//�u���ցv�{�^���������ꂽ�玟��
	if (input.IsTrigger(InputType::next))
	{
		//m_manager.PushScene(new SceneSelect(m_manager));
		m_updateFunc = &SceneTitle::FadeOutUpdate;
	}

	if (input.IsTrigger(InputType::right))
	{
		++m_numCount;
		++kNum;
	}
	else if (input.IsTrigger(InputType::left))
	{
		--kNum;
	}


	if (kNum < 1)
	{
		kNum = kMaxStage;
	}
	if (kNum > kMaxStage)
	{
		kNum = 1;
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
	SceneBase(manager), 
	m_updateFunc(&SceneTitle::FadeInUpdate),
	m_font(0),
	m_strTitle(-1),
	m_strEx(-1)
{
	//m_test = MakeScreen(Game::kScreenWindth,Game::kScreenHeight,true);

	m_font = CreateFontToHandle("HGS�n�p�p�߯�ߑ�", 48, -1, -1);
	m_strTitle = strlen(kTextTitle);
	m_strEx = strlen(kTextExplanation);
	m_strNum = strlen("%d");

}

SceneTitle::~SceneTitle()
{
	//DeleteGraph(m_test);
}

void SceneTitle::Update(const InputState& input)
{
	(this->*m_updateFunc)(input);
}

void SceneTitle::Draw()
{
	//�h��Ă鏈��
	//SetDrawScreen(m_test);

	//�w�i�̑���
	DrawBox(0, 0, Game::kScreenWindth, Game::kScreenHeight, 0x00000, true);
	//���ʂ̕`��
	DrawBox(200, 200, 300, 300, 0xffffff, true);
	
	DrawStringToHandle((Game::kScreenWindth - 
		GetDrawStringWidthToHandle(kTextTitle, m_strTitle,m_font)) / 2,
		200, kTextTitle, 0xffffff, m_font);

	DrawFormatStringToHandle((Game::kScreenWindth - 
		GetDrawStringWidthToHandle("%d", m_strNum, m_font)) / 2,
		Game::kScreenHeight / 2,  0xffffff,m_font,"%d", kNum);
	
	DrawStringToHandle((Game::kScreenWindth - 
		GetDrawStringWidthToHandle(kTextExplanation, m_strEx,m_font)) / 2,
		Game::kScreenHeight - 200, kTextExplanation, 0x00ffff, m_font);

	//�h��Ă鏈��
	//SetDrawScreen(DX_SCREEN_BACK);
	//int shakeX = GetRand(2) - 2;
	//int shakeY = GetRand(2) - 2;
	//DrawGraph(shakeX, shakeY, m_test, true);
	//DrawStringToHandle((Game::kScreenWindth - GetDrawStringWidth("�^�C�g��", -1)) / 2,
	//	Game::kScreenHeight / 2,"�^�C�g��", 0x00ffff, font);


	//�����珑���摜�ƁA���łɕ`�悳��Ă���X�N���[���Ƃ�
	//�u�����h�̎d�����w��
	SetDrawBlendMode(DX_BLENDMODE_MULA, m_fadeValue);
	//��ʑS�̂�^�����ɓh��Ԃ�
	//DrawGraph(0, 200, GradH_, true);
	//�ύX�����猳�ɖ߂�
	DrawBox(0, 0, Game::kScreenWindth, Game::kScreenHeight, 0x00000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	//DrawString(300, 200, L"TitleScene", 0xfffff);

}

int SceneTitle::SelectNum()
{
	int selectNum = 0;
	selectNum = kNum;
	return selectNum;
}
