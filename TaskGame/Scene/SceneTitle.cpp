#include "SceneTitle.h"
#include"SceneSelect.h"
#include"SceneManager.h"
#include"../UI/game.h"
#include"../UI/InputState.h"
#include<DxLib.h>

namespace
{
	//const char* const kTextTitle = "SOUKOBAN�iKARI�j";
	const char* const kTextTitle = "�q�ɔԁi���j";
	const char* const kTextExplanation = "A�{�^���������Ă�������";
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
	//�K�C�h�̕����̓_��
	m_displayCount++;
	if (m_displayCount >= 60 * 2)
	{
		m_displayCount = 0;
	}

	//�u���ցv�{�^���������ꂽ�玟��
	if (input.IsTrigger(InputType::next))
	{
		//m_manager.PushScene(new SceneSelect(m_manager));
		m_updateFunc = &SceneTitle::FadeOutUpdate;
	}
}

void SceneTitle::FadeOutUpdate(const InputState& input)
{
	m_fadeValue = 255 * (static_cast<float>(m_fadeTimer) / static_cast<float>(m_fadeInterval));
	if (++m_fadeTimer == m_fadeInterval) {
	
		m_manager.ChangeScene(new SceneSelect(m_manager));
		return;
	}
}

SceneTitle::SceneTitle(SceneManager& manager) :
	SceneBase(manager), 
	m_updateFunc(&SceneTitle::FadeInUpdate),
	m_displayCount(0),
	m_TitleFont(0),
	m_guideFont(0),
	m_strTitle(-1),
	m_strEx(-1)
{
	//m_test = MakeScreen(Game::kScreenWindth,Game::kScreenHeight,true);

	LPCSTR font_path1 = "../Font/851MkPOP_101.ttf"; // �ǂݍ��ރt�H���g�t�@�C���̃p�X
	LPCSTR font_path2 = "../Font/komorebi-gothic.ttf"; // �ǂݍ��ރt�H���g�t�@�C���̃p�X
	if (AddFontResourceEx(font_path1, FR_PRIVATE, NULL) > 0) {
	}
	else {
		// �t�H���g�Ǎ��G���[����
		MessageBox(NULL, "�t�H���g�Ǎ����s", "", MB_OK);
	}
	if (AddFontResourceEx(font_path2, FR_PRIVATE, NULL) > 0) {
	}
	else {
		// �t�H���g�Ǎ��G���[����
		MessageBox(NULL, "�t�H���g�Ǎ����s", "", MB_OK);
	}

	m_TitleFont = CreateFontToHandle("851�}�J�|�b�v", 162, -1, -1);
	m_guideFont = CreateFontToHandle("�ؘR����S�V�b�N", 42, -1, -1);
	m_strTitle = strlen(kTextTitle);
	m_strEx = strlen(kTextExplanation);
	m_strNum = strlen("%d");

}

SceneTitle::~SceneTitle()
{
	DeleteFontToHandle(m_TitleFont);
	DeleteFontToHandle(m_guideFont);
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

	DrawStringToHandle((Game::kScreenWindth - 
		GetDrawStringWidthToHandle(kTextTitle, m_strTitle,m_TitleFont)) / 2,
		200, kTextTitle, 0xffffa0, m_TitleFont);								//�^�C�g���̕\��
	
	//�_�ŏ���
	if (m_displayCount / 60 < 1)
	{
		DrawStringToHandle((Game::kScreenWindth -
			GetDrawStringWidthToHandle(kTextExplanation, m_strEx, m_guideFont)) / 2,
			Game::kScreenHeight - 200, kTextExplanation, 0xffffff, m_guideFont);	//�K�C�h�̕\��
	}
	//�h��Ă鏈��
	//SetDrawScreen(DX_SCREEN_BACK);
	//int shakeX = GetRand(2) - 2;
	//int shakeY = GetRand(2) - 2;
	//DrawGraph(shakeX, shakeY, m_test, true);
	//DrawStringToHandle((Game::kScreenWindth - GetDrawStringWidth("�^�C�g��", -1)) / 2,
	//	Game::kScreenHeight / 2,"�^�C�g��", 0x00ffff, font);

	
	//�����珑���摜�ƁA���łɕ`�悳��Ă���X�N���[���Ƃ�
	//�u�����h�̎d�����w��
	SetDrawBlendMode(DX_BLENDMODE_MULA, static_cast<int> (m_fadeValue));
	//��ʑS�̂�^�����ɓh��Ԃ�
	//�ύX�����猳�ɖ߂�
	DrawBox(0, 0, Game::kScreenWindth, Game::kScreenHeight, 0x00000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	//DrawString(300, 200, L"TitleScene", 0xfffff);
}