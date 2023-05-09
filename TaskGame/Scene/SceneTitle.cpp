#include "SceneTitle.h"
#include"SceneSelect.h"
#include"SceneManager.h"
#include"../Object/Player.h"
#include"../UI/game.h"
#include"../UI/InputState.h"
#include"../GameManager.h"
#include"../Object/MapChip.h"
#include"../SoundManager.h"
#include<DxLib.h>

//�t�F�[�h����
void SceneTitle::FadeInUpdate(const InputState& input)
{
	m_fadeValue = 255 * (static_cast<float>(m_fadeTimer) / static_cast<float>(m_fadeInterval));
	if (--m_fadeTimer == 0) {
		m_updateFunc = &SceneTitle::NormalUpdate;
		m_fadeValue = 0;
	}
}
//�X�V����
void SceneTitle::NormalUpdate(const InputState& input)
{
	m_pPlayer->TitleUpdate();
	//�A�j���[�V�����̏����i�{�^���j
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
		m_updateFunc = &SceneTitle::FadeOutUpdate;
		SoundManager::GetInstance().Play(L"SE1");
	}
}
//�t�F�[�h����
void SceneTitle::FadeOutUpdate(const InputState& input)
{
	m_fadeValue = 255 * (static_cast<float>(m_fadeTimer) / static_cast<float>(m_fadeInterval));
	if (++m_fadeTimer == m_fadeInterval)
	{
		m_manager.ChangeScene(new SceneSelect(m_manager));
		return;
	}
}
//�R���X�g���N�^
SceneTitle::SceneTitle(SceneManager& manager) :
	SceneBase(manager),
	m_updateFunc(&SceneTitle::FadeInUpdate),
	m_backHandle(0),
	m_roomHandle(0),
	m_BgSound(0),
	m_displayCount(0),
	m_TitleFont(0),
	m_guideFont(0),
	m_strTitle(-1),
	m_strEx(-1)
{
	m_pMap = new MapChip;
	m_pPlayer = new Player;
	my::MyFontPath(L"../Font/851MkPOP_101.ttf");	// �ǂݍ��ރt�H���g�t�@�C���̃p�X
	my::MyFontPath(L"../Font/komorebi-gothic.ttf"); // �ǂݍ��ރt�H���g�t�@�C���̃p�X
	m_BgSound = LoadSoundMem(L"../Sound/BGM/TitleBg.mp3"); //�T�E���h�̓ǂݍ���
	m_backHandle = my::MyLoadGraph(L"../Date/Grass.png");	 //�w�i�̓ǂݍ���
	m_roomHandle = my::MyLoadGraph(L"../Date/texture.png");	 //�w�i�̓ǂݍ���
	m_buttonHandle = my::MyLoadGraph(L"../Date/button.png");	//UI�̉摜�̓ǂݍ���
	m_titleHandle = my::MyLoadGraph(L"../Date/Title.png");		//�^�C�g���摜�̓ǂݍ���
	m_guideFont = CreateFontToHandle(L"HG�ۺ޼��M-PRO", 42, -1, -1);	//�t�H���g�̓ǂݍ���
	m_strTitle = static_cast<int>(strlen("�Еt����"));				//������̒����̓ǂݍ���
	m_strEx = static_cast<int>(strlen("A�{�^���������Ă�������"));	//������̒����̓ǂݍ���
	m_strNum = static_cast<int>(strlen("%d"));						//������̒����̓ǂݍ���
	m_pMap->Load(L"../Date/room.fmf");								//�w�i�f�[�^�̓ǂݍ���
	SoundManager::GetInstance().PlayMusic(m_BgSound);				//SE�̓ǂݍ���
}
//�f�X�g���N�^
SceneTitle::~SceneTitle()
{
	delete m_pMap;						//�������̍폜
	delete m_pPlayer;					//�������̍폜
	DeleteGraph(m_backHandle);			//�摜�̍폜
	DeleteGraph(m_roomHandle);			//�摜�̍폜
	DeleteSoundMem(m_BgSound);			//���̍폜
	DeleteFontToHandle(m_TitleFont);	//�t�H���g�̍폜
	DeleteFontToHandle(m_guideFont);	//�t�H���g�̍폜
}
//�X�V����
void SceneTitle::Update(const InputState& input)
{
	ChangeVolumeSoundMem(255 - static_cast<int>(m_fadeValue), m_BgSound);	//�t�F�[�h�ɍ��킹�ĉ����t�F�[�h����
	(this->*m_updateFunc)(input);
}
//�`�揈��
void SceneTitle::Draw()
{
	int posX = (Game::kScreenWindth -
			GetDrawStringWidthToHandle(L"A�{�^���������Ă�������", m_strEx, m_guideFont)) / 2;
	int posY = Game::kScreenHeight - 200;
	int animeNum = (m_displayCount / 5) + 1;
	//�w�i
	DrawBackground();
	m_pPlayer->Draw();
	//�^�C�g���̕\��
	DrawRotaGraph((Game::kScreenWindth  / 2), 300,
		0.5f,0,
		m_titleHandle, true);
	//�{�^���̏����i�A�j���[�V�����̒ǉ��j
	my::MyDrawRectRotaGraph(posX - 5, posY + 25,			//�\�����W
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
//�w�i�`��
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
			auto backChipId = mapData[0][static_cast<__int64>(chipY) * mW + chipX];
			my::MyDrawRectRotaGraph(chipX * 32, chipY * 32,
				(backChipId % 10) * 16,
				(backChipId / 8) * 16,
				16, 16,
				2.0f, 0,
				m_backHandle, true);
			auto roomchipId = mapData[1][static_cast<__int64>(chipY) * mW + chipX];
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
