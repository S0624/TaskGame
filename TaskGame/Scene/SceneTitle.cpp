#include "SceneTitle.h"
#include"SceneSelect.h"
#include"SceneManager.h"
#include"../UI/game.h"
#include"../UI/InputState.h"
#include"../GameManager.h"
#include"../Object/MapChip.h"
#include<DxLib.h>

namespace
{
	//const char* const kTextTitle = "SOUKOBAN�iKARI�j";
	//const char* const kTextTitle = "�q�ɔԁi���j";
	//const char* const kTextExplanation = "A�{�^���������Ă�������";
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
	m_handle(0),
	m_displayCount(0),
	m_TitleFont(0),
	m_guideFont(0),
	m_strTitle(-1),
	m_strEx(-1)
{
	m_pMap = new MapChip;
	//std::shared_ptr<MapChip>;
	my::MyFontPath(L"../Font/851MkPOP_101.ttf"); // �ǂݍ��ރt�H���g�t�@�C���̃p�X
	my::MyFontPath(L"../Font/komorebi-gothic.ttf"); // �ǂݍ��ރt�H���g�t�@�C���̃p�X

	m_handle = my::MyLoadGraph(L"../Date/Grass.png");
	m_TitleFont = CreateFontToHandle(L"851�}�J�|�b�v", 162, -1, -1);
	m_guideFont = CreateFontToHandle(L"�ؘR����S�V�b�N", 42, -1, -1);
	m_strTitle = strlen("�q�ɔԁi���j");
	m_strEx = strlen("A�{�^���������Ă�������");
	m_strNum = strlen("%d");

	//m_map->Load(L"../Date/back.fmf");
	m_pMap->Load(L"../Date/back.fmf");
}

SceneTitle::~SceneTitle()
{
	delete m_pMap;
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
	//�w�i
	int mW, mH;
	m_pMap->GetMapSize(mW, mH);
	//m_map->GetMapSize(mW, mH);
	const auto& mapData = m_pMap->GetMapData();
	//const auto& mapData = m_map->GetMapData();
	for (int chipY = 0; chipY < mH; ++chipY)	// �c����
	{
		for (int chipX = 0; chipX < mW; ++chipX)	// ������
		{
			auto chipId = mapData[0][chipY * mW + chipX];
			//if (chipId == 0)
			{
				DrawRectGraph(
					chipX * 16, chipY * 16,
					(chipId % 8) * 16,
					(chipId / 8) * 16,
					16, 16,
					m_handle, true);
				/*my::MyDrawRectRotaGraph(
					chipX * 16, chipY * 16,
					(chipId % 8) * 16,
					(chipId / 8) * 16,
					16, 16,
					2.0f,0,
					m_handle, true);*/
			}
		}
	}
	DrawStringToHandle((Game::kScreenWindth -
		GetDrawStringWidthToHandle(L"�q�ɔԁi���j", m_strTitle, m_TitleFont)) / 2,
		200, L"�q�ɔԁi���j", 0xff0000, m_TitleFont);								//�^�C�g���̕\��

	//�_�ŏ���
	if (m_displayCount / 60 < 1)
	{
		DrawStringToHandle((Game::kScreenWindth -
			GetDrawStringWidthToHandle(L"A�{�^���������Ă�������", m_strEx, m_guideFont)) / 2,
			Game::kScreenHeight - 200, L"A�{�^���������Ă�������", 0xffffff, m_guideFont);	//�K�C�h�̕\��
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