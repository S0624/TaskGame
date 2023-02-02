#include "SceneMain.h"
#include"../Object/Player.h"
#include"../Object/Field.h"
#include"../UI/game.h"
#include"../UI/InputState.h"
#include "SceneTitle.h"
#include"ScenePause.h"
#include"SceneManager.h"
#include"DxLib.h"

namespace {

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
	m_pPlayer = new Player;
	m_pField = new Field;

	Init();
}

SceneMain::~SceneMain()
{
	delete m_pPlayer;		//�������̍폜
	delete m_pField;		//�������̍폜
	//delete m_pBox;		//�������̍폜
}

void SceneMain::Init()const
{
	m_pPlayer->Init();		//�v���C���[�N���X�̏�����
	m_pField->Init();		//�t�B�[���h�N���X�̏�����
	m_pPlayer->SetField(m_pField);
}

void SceneMain::Update(const InputState& input)
{
	m_pPlayer->Update(input);	//�v���C���[�N���X�̍X�V����
	m_pField->Update();		//�t�B�[���h�N���X�̍X�V����
	(this->*m_updateFunc)(input);
}

void SceneMain::Draw()
{
	m_pField->Draw();		//�t�B�[���h�N���X�̕`�揈��
	m_pPlayer->Draw();		//�v���C���[�N���X�̕`�揈��

	if (m_pField->GameClear())
	{
		DrawFormatString(400, 100, GetColor(0, 125, 255), "�Q�[���N���A");
	}

	//���ʂ̕`��
	//�����珑���摜�ƁA���łɕ`�悳��Ă���X�N���[���Ƃ�
	//�u�����h�̎d�����w��
	SetDrawBlendMode(DX_BLENDMODE_MULA, m_fadeValue);
	//��ʑS�̂�^�����ɓh��Ԃ�
	//�ύX�����猳�ɖ߂�
	DrawBox(0, 0, Game::kScreenWindth, Game::kScreenHeight, 0x00000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	
}
