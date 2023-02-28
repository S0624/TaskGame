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
#include"DxLib.h"


namespace {
	int kNextStage = 0;
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

	//�N���A���ăt�F�[�h���|����؂�����Z���N�g���Ă��炤
	if (m_fadeColor)
	{
		CursorUpdate(input);
	}
	//�u�|�[�Y�v�{�^���������ꂽ��|�[�Y��\��
	//�Q�[���N���A���Ă����牟���Ȃ�����
	else if (input.IsTrigger(InputType::pause))
	{
		PlaySoundMem(m_pauseSESound, DX_PLAYTYPE_BACK);
		m_manager.PushScene(new ScenePause(m_manager));
	}

	m_pauseNum = m_pPause->CursolUpdate();
	if (m_pauseNum == 2 || m_pauseNum == 3)
	{
		m_test = m_pauseNum;
		m_updateFunc = &SceneMain::FadeOutUpdate;
	}


}

void SceneMain::FadeOutUpdate(const InputState& input)
{
	m_fadeValue = 255 * (static_cast<float>(m_fadeTimer) / static_cast<float>(m_fadeInterval));
	if (++m_fadeTimer == m_fadeInterval) {
		if (m_numCount == 2 || m_test == 2)
		{
			kNextStage = 0;
			m_manager.ChangeScene(new SceneMain(m_manager));
			return;
		}
		if (m_numCount == 3 || m_test == 3)
		{
			kNextStage = 0;
			m_manager.ChangeScene(new SceneTitle(m_manager));
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

void SceneMain::InitLoad()
{
	m_handle = my::MyLoadGraph(L"../Date/Setting menu.png");		//�摜�̓ǂݍ���
	my::MyFontPath(L"../Font/851MkPOP_101.ttf"); // �ǂݍ��ރt�H���g�t�@�C���̃p�X
	my::MyFontPath(L"../Font/komorebi-gothic.ttf"); // �ǂݍ��ރt�H���g�t�@�C���̃p�X
	my::MyFontPath(L"../Font/erizifont.otf"); // �ǂݍ��ރt�H���g�t�@�C���̃p�X

	m_clearFont = CreateFontToHandle(L"851�}�J�|�b�v", 128, -1, -1);
	m_guideFont = CreateFontToHandle(L"�ؘR����S�V�b�N", 42, -1, -1);
	m_scoreFont = CreateFontToHandle(L"���莚", 64, -1, -1);

	m_backHandle = my::MyLoadGraph(L"../Date/Grass.png");
	m_pMap->Load(L"../Date/room.fmf");
}

void SceneMain::InitSound()
{
	m_enterSESound = LoadSoundMem(L"../Sound/SE1.mp3");
	m_moveSESound = LoadSoundMem(L"../Sound/SE2.mp3");
	m_pauseSESound = LoadSoundMem(L"../Sound/Pause1.mp3");
	m_clearSESound = LoadSoundMem(L"../Sound/GameClear.mp3");
	m_gamePlayBgSound = LoadSoundMem(L"../Sound/GamePlayBg.mp3");

	ChangeNextPlayVolumeSoundMem(160, m_enterSESound);
	ChangeNextPlayVolumeSoundMem(160, m_moveSESound);
	ChangeNextPlayVolumeSoundMem(150, m_pauseSESound);
	ChangeNextPlayVolumeSoundMem(150, m_clearSESound);
	ChangeNextPlayVolumeSoundMem(150, m_gamePlayBgSound);
}

SceneMain::SceneMain(SceneManager& manager) :
	SceneBase(manager), m_updateFunc(&SceneMain::FadeInUpdate)
{
	m_pField = new Field;
	m_pPlayer = new Player;
	m_pInformation = new FieldInformation;

	m_pMap = new MapChip;

	m_stageNum = m_pSelect->SelectNum(kNextStage);
	kNextStage = 0;
	//������
	m_pPlayer->SetField(m_pField);
	m_pInformation->StageNum(m_stageNum);
	m_pInformation->Init();
	m_pInformation->SetField(m_pField);
	m_pInformation->SetPlayer(m_pPlayer);
	m_pInformation->FieldInit();

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

	PlaySoundMem(m_gamePlayBgSound, DX_PLAYTYPE_LOOP, false);

}

SceneMain::~SceneMain()
{
	delete m_pField;		//�������̍폜
	delete m_pPlayer;		//�������̍폜
	delete m_pInformation;	//�������̍폜
	delete m_pSelect;		//�������̍폜
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

void SceneMain::Update(const InputState& input)
{
	m_pField->Update();		//�t�B�[���h�N���X�̍X�V����
	m_pPlayer->Update(input);	//�v���C���[�N���X�̍X�V����
	(this->*m_updateFunc)(input);
}

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


	//�u���ցv�{�^���������ꂽ�玟��
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

void SceneMain::Draw()
{
	//�w�i�̑���
	DrawBackground();

	m_pField->Draw();		//�t�B�[���h�N���X�̕`�揈��
	m_pPlayer->Draw();		//�v���C���[�N���X�̕`�揈��
	DrawScore();
	if (m_pField->GameClear())
	{
		DrawGameClear();
	}

	//���ʂ̕`��
	//�����珑���摜�ƁA���łɕ`�悳��Ă���X�N���[���Ƃ�
	//�u�����h�̎d�����w��
	SetDrawBlendMode(DX_BLENDMODE_MULA, static_cast<int> (m_fadeValue));
	//��ʑS�̂�^�����ɓh��Ԃ�
	//�ύX�����猳�ɖ߂�
	DrawBox(0, 0, Game::kScreenWindth, Game::kScreenHeight, 0x00000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

}

void SceneMain::DrawBackground()
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
		}
	}
	SetDrawBlendMode(DX_BLENDMODE_MULA, 50);		//��������
	DrawBox(0, 0,
		Game::kScreenWindth, Game::kScreenHeight,
		0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);			//�ʏ�`��ɖ߂�
}

void SceneMain::DrawGameClear()
{
	SetDrawBlendMode(DX_BLENDMODE_MULA, m_setBlend);		//��������
	DrawBox(0, 0,
		Game::kScreenWindth, Game::kScreenHeight,
		0x00000, true);		//�|�[�Y�E�B���h�E�Z���t�@��
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

	//���ɖ߂�
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);			//�ʏ�`��ɖ߂�
	
	DrawStringToHandle((Game::kScreenWindth -
		GetDrawStringWidthToHandle(L"Game Clear", 11, m_clearFont)) / 2,
		175, L"Game Clear", 0xff0000, m_clearFont);								//�^�C�g���̕\��

	constexpr int width = 400;		//�|�[�Y�g�̕�
	constexpr int height = 300;		//�|�[�Y�g�̍���
	constexpr int widthPos = (Game::kScreenWindth - width) / 2;
	constexpr int heightPos = (Game::kScreenHeight - height) / 2;

	DrawExtendGraph(widthPos, heightPos,
		widthPos + width, heightPos + height,
		m_handle, true);
	if (m_stageNum != 10)
	{
		DrawStringToHandle(widthPos + 50, heightPos + m_index * 0.9, L"���ւ�����", 0x000000, m_guideFont);
	}
	DrawStringToHandle(widthPos + 50, heightPos + m_index * 2, L"������x�v���C", 0x000000, m_guideFont);
	DrawStringToHandle(widthPos + 50, heightPos + m_index * 3, L"�^�C�g���֖߂�", 0x000000, m_guideFont);

	DrawStringToHandle(widthPos + 10, heightPos + m_index * m_numCount, L"��", 0x00a000, m_guideFont);
}

void SceneMain::DrawScore()
{
	//���̐��l
	DrawBox(Game::kScreenWindth - 400, 100, Game::kScreenWindth - 100, 250, 0x000000, true);
	DrawFormatStringToHandle(Game::kScreenWindth - 400, 100, 
		0x0f0add, m_scoreFont,L"STAGE:%d", m_stageNum);
	DrawFormatStringToHandle(Game::kScreenWindth - 400, 100 + 48,
		0x0f0add, m_scoreFont,L"STEP:%d", m_pPlayer->MoveStep());
	DrawFormatStringToHandle(Game::kScreenWindth - 400, 100 + 96,
		0x0f0add, m_scoreFont,L"LIMIT:%d", 0);
}