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

	//�N���A�ɂȂ�����^�C�g���֖߂�
	if (m_pField->GameClear())
	{
		CursorUpdate(input);
	}
	//�u�|�[�Y�v�{�^���������ꂽ��|�[�Y��\��
	//�Q�[���N���A���Ă����牟���Ȃ�����
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
	//������
	m_pPlayer->SetField(m_pField);
	m_pInformation->StageNum(num);
	m_pInformation->Init();
	m_pInformation->SetField(m_pField);
	m_pInformation->SetPlayer(m_pPlayer);
	m_pInformation->FieldInit();

	m_handle = my::MyLoadGraph(L"../Date/Setting menu.png");		//�摜�̓ǂݍ���
	my::MyFontPath(L"../Font/851MkPOP_101.ttf"); // �ǂݍ��ރt�H���g�t�@�C���̃p�X
	my::MyFontPath(L"../Font/komorebi-gothic.ttf"); // �ǂݍ��ރt�H���g�t�@�C���̃p�X

	m_ClearFont = CreateFontToHandle(L"851�}�J�|�b�v", 128, -1, -1);
	m_guideFont = CreateFontToHandle(L"�ؘR����S�V�b�N", 42, -1, -1);
}

SceneMain::~SceneMain()
{
	delete m_pField;		//�������̍폜
	delete m_pPlayer;		//�������̍폜
	delete m_pInformation;	//�������̍폜
	delete m_pSelect;		//�������̍폜
}

void SceneMain::Update(const InputState& input)
{
	m_pField->Update();		//�t�B�[���h�N���X�̍X�V����
	m_pPlayer->Update(input);	//�v���C���[�N���X�̍X�V����
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

	//�u���ցv�{�^���������ꂽ�玟��
	if (input.IsTrigger(InputType::next))
	{
		m_updateFunc = &SceneMain::FadeOutUpdate;
	}
}

void SceneMain::Draw()
{
	//�w�i�̑���
	DrawBox(0, 0, Game::kScreenWindth, Game::kScreenHeight, 0x00000, true);

	m_pField->Draw();		//�t�B�[���h�N���X�̕`�揈��
	m_pPlayer->Draw();		//�v���C���[�N���X�̕`�揈��

	if (m_pField->GameClear())
	{
		test = 1;
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

void SceneMain::DrawGameClear()
{
	SetDrawBlendMode(DX_BLENDMODE_MULA, 100);		//��������
	DrawBox(0, 0,
		Game::kScreenWindth, Game::kScreenHeight,
		0x00000, true);		//�|�[�Y�E�B���h�E�Z���t�@��

	//���ɖ߂�
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);			//�ʏ�`��ɖ߂�
	
	DrawStringToHandle((Game::kScreenWindth -
		GetDrawStringWidthToHandle(L"Game Clear", 11, m_ClearFont)) / 2,
		175, L"Game Clear", 0xff0000, m_ClearFont);								//�^�C�g���̕\��

	constexpr int width = 400;		//�|�[�Y�g�̕�
	constexpr int height = 300;		//�|�[�Y�g�̍���
	constexpr int widthPos = (Game::kScreenWindth - width) / 2;
	constexpr int heightPos = (Game::kScreenHeight - height) / 2;

	DrawExtendGraph(widthPos, heightPos,
		widthPos + width, heightPos + height,
		m_handle, true);
	if (num = !10)
	{
		DrawStringToHandle(widthPos + 50, heightPos + 70 * 1, L"���ւ�����", 0x000000, m_guideFont);
	}
	DrawStringToHandle(widthPos + 50, heightPos + 70 * 2, L"������x�v���C", 0x000000, m_guideFont);
	DrawStringToHandle(widthPos + 50, heightPos + 70 * 3, L"�^�C�g���֖߂�", 0x000000, m_guideFont);

	DrawStringToHandle(widthPos + 10, heightPos + 70 * m_numCount, L"��", 0x00a000, m_guideFont);

	//DrawFormatString(400, 0, GetColor(0, 125, 255), L"�Q�[���N���A");
}
