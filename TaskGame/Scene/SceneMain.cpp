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
#include"DxLib.h"


namespace {
	//SceneTitle title;
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
	//�������@�N���A�ɂȂ�����^�C�g���֖߂�
	if (m_pField->GameClear())
	{
		//�u���ցv�{�^���������ꂽ�玟��
		if (input.IsTrigger(InputType::next))
		{
			m_updateFunc = &SceneMain::FadeOutUpdate;
		}
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
		m_manager.ChangeScene(new SceneTitle(m_manager));
		return;
	}
}

SceneMain::SceneMain(SceneManager& manager) :
	SceneBase(manager), m_updateFunc(&SceneMain::FadeInUpdate)
{
	m_pField = new Field;
	m_pPlayer = new Player;
	m_pInformation = new FieldInformation;
	
	int num = 1;
	num = m_pSelect->SelectNum();

	//������
	m_pPlayer->SetField(m_pField);
	m_pInformation->StageNum(num);
	m_pInformation->Init();
	m_pInformation->SetField(m_pField);
	m_pInformation->SetPlayer(m_pPlayer);
	m_pInformation->FieldInit();
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

void SceneMain::Draw()
{
	//�w�i�̑���
	DrawBox(0, 0, Game::kScreenWindth, Game::kScreenHeight, 0x00000, true);

	m_pField->Draw();		//�t�B�[���h�N���X�̕`�揈��
	m_pPlayer->Draw();		//�v���C���[�N���X�̕`�揈��

	if (m_pField->GameClear())
	{
		DrawFormatString(400, 0, GetColor(0, 125, 255), "�Q�[���N���A");
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
