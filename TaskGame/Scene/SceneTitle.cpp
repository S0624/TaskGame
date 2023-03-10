#include "SceneTitle.h"
#include"SceneSelect.h"
#include"SceneManager.h"
#include"../Object/Player.h"
#include"../UI/game.h"
#include"../UI/InputState.h"
#include"../GameManager.h"
#include"../Object/MapChip.h"
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
	m_pPlayer->TitleUpdate();

	//�K�C�h�̕����̓_��
	m_animation++;
	if (m_animation > 60)
	{
		m_displayCount++;
		if (m_displayCount >= 5 * 4)
		{
			m_animation = 0;
			m_displayCount = 0;
		}
	}

	//�u���ցv�{�^���������ꂽ�玟��
	if (input.IsTrigger(InputType::next))
	{
		PlaySoundMem(m_enterSESound, DX_PLAYTYPE_BACK);
		m_updateFunc = &SceneTitle::FadeOutUpdate;
	}
}

void SceneTitle::FadeOutUpdate(const InputState& input)
{
	SetVolumeMusic(255 - static_cast<int>(255.0f / 60.0f * static_cast<int>(60 - m_fadeTimer)));

	m_fadeValue = 255 * (static_cast<float>(m_fadeTimer) / static_cast<float>(m_fadeInterval));
	if (++m_fadeTimer == m_fadeInterval) {

		m_manager.ChangeScene(new SceneSelect(m_manager));
		return;
	}
}

SceneTitle::SceneTitle(SceneManager& manager) :
	SceneBase(manager),
	m_updateFunc(&SceneTitle::FadeInUpdate),
	m_backHandle(0),
	m_roomHandle(0),
	m_enterSESound(0),
	m_BgSound(0),
	m_displayCount(0),
	m_TitleFont(0),
	m_guideFont(0),
	m_strTitle(-1),
	m_strEx(-1)
{
	m_pMap = new MapChip;
	m_pPlayer = new Player;
	my::MyFontPath(L"../Font/851MkPOP_101.ttf"); // �ǂݍ��ރt�H���g�t�@�C���̃p�X
	my::MyFontPath(L"../Font/komorebi-gothic.ttf"); // �ǂݍ��ރt�H���g�t�@�C���̃p�X

	//m_enterSESound = LoadSoundMem(L"../Sound/SE1.mp3");
	//m_BgSound = LoadSoundMem(L"../Sound/TitleBg.mp3");

	m_backHandle = my::MyLoadGraph(L"../Date/Grass.png");
	m_roomHandle = my::MyLoadGraph(L"../Date/texture.png");
	m_buttonHandle = my::MyLoadGraph(L"../Date/button.png");
	m_titleHandle = my::MyLoadGraph(L"../Date/Title.png");
	//m_TitleFont = CreateFontToHandle(L"851�}�J�|�b�v", 162, -1, -1);
	m_guideFont = CreateFontToHandle(L"HG�ۺ޼��M-PRO", 42, -1, -1);
	m_strTitle = strlen("�Еt����");
	m_strEx = strlen("A�{�^���������Ă�������");
	m_strNum = strlen("%d");

	m_pMap->Load(L"../Date/room.fmf");

	ChangeNextPlayVolumeSoundMem(160, m_enterSESound);
	PlaySoundMem(m_BgSound, DX_PLAYTYPE_LOOP);
}

SceneTitle::~SceneTitle()
{
	delete m_pMap;
	delete m_pPlayer;
	DeleteGraph(m_backHandle);
	DeleteGraph(m_roomHandle);
	DeleteSoundMem(m_enterSESound);
	DeleteSoundMem(m_BgSound);
	DeleteFontToHandle(m_TitleFont);
	DeleteFontToHandle(m_guideFont);
}

void SceneTitle::Update(const InputState& input)
{
	ChangeVolumeSoundMem(255 - static_cast<int>(m_fadeValue), m_BgSound);
	(this->*m_updateFunc)(input);
}

void SceneTitle::Draw()
{
	int posX = (Game::kScreenWindth -
			GetDrawStringWidthToHandle(L"A�{�^���������Ă�������", m_strEx, m_guideFont)) / 2;
	int posY = Game::kScreenHeight - 200;
	int animeNum = (m_displayCount / 5) + 1;


	//�w�i
	DrawBackground();
	m_pPlayer->Draw();

	//DrawStringToHandle((Game::kScreenWindth -
	//	GetDrawStringWidthToHandle(L"�Еt����", m_strTitle, m_TitleFont)) / 2 + 5,
	//	200 + 3, L"�Еt����", 0x000000, m_TitleFont);								//�^�C�g���̕\��
	//DrawStringToHandle((Game::kScreenWindth -
	//	GetDrawStringWidthToHandle(L"�Еt����", m_strTitle, m_TitleFont)) / 2,
	//	200, L"�Еt����", 0xff0000, m_TitleFont);								//�^�C�g���̕\��
	
	DrawRotaGraph((Game::kScreenWindth  / 2), 300,
		0.5f,0,
		m_titleHandle, true);

	//�_�ŏ���

	my::MyDrawRectRotaGraph(posX, posY + 25,			//�\�����W
		32 + (16 * animeNum), 16 + (16 * 2),			//�؂��荶��
		16, 16,							//���A����
		3.0f, 0.0f,						//�g�嗦�A��]�p�x
		m_buttonHandle, true);
	DrawStringToHandle(posX + 5, posY, L" �{�^���������Ă�������", 0xffffff, m_guideFont);	//�K�C�h�̕\��

	//�����珑���摜�ƁA���łɕ`�悳��Ă���X�N���[���Ƃ�
	//�u�����h�̎d�����w��
	SetDrawBlendMode(DX_BLENDMODE_MULA, static_cast<int> (m_fadeValue));
	//��ʑS�̂�^�����ɓh��Ԃ�
	//�ύX�����猳�ɖ߂�
	DrawBox(0, 0, Game::kScreenWindth, Game::kScreenHeight, 0x00000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void SceneTitle::DrawBackground()
{
	//�w�i
	int mW, mH;
	m_pMap->GetMapSize(mW, mH);
	const auto& mapData = m_pMap->GetMapData();
	for (int chipY = 0; chipY < mH; ++chipY)	// �c����
	{
		for (int chipX = 0; chipX < mW; ++chipX)	// ������
		{
			auto backChipId = mapData[0][chipY * mW + chipX];
			my::MyDrawRectRotaGraph(chipX * 32, chipY * 32,
				(backChipId % 10) * 16,
				(backChipId / 8) * 16,
				16, 16,
				2.0f, 0,
				m_backHandle, true);

			auto roomchipId = mapData[1][chipY * mW + chipX];
			if (roomchipId == 0 || roomchipId == 2)
			{
				my::MyDrawRectRotaGraph((chipX * 32) - 650, chipY * 32 - 125,
					(roomchipId % 12) * 16,
					(roomchipId / 8) * 16,
					16, 16,
					2.0f, 0,
					m_roomHandle, true);
			}
		}
	}
}
