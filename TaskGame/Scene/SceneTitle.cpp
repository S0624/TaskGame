#include "SceneTitle.h"
#include"SceneMain.h"
#include"SceneManager.h"
#include"../UI/game.h"
#include"../UI/InputState.h"
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
	//�u���ցv�{�^���������ꂽ�玟��
	if (input.IsTrigger(InputType::next))
	{
		m_updateFunc = &SceneTitle::FadeOutUpdate;
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
	SceneBase(manager), m_updateFunc(&SceneTitle::FadeInUpdate)
{

}

void SceneTitle::Update(const InputState& input)
{
	(this->*m_updateFunc)(input);
}

void SceneTitle::Draw()
{
	DrawBox(0, 0, Game::kScreenWindth, Game::kScreenHeight, 0x00000, true);
	//���ʂ̕`��
	DrawBox(200, 200, 300, 300, 0xffffff, true);
	DrawString(400, 200,"�^�C�g��", 0x00ffff, true);
	//�����珑���摜�ƁA���łɕ`�悳��Ă���X�N���[���Ƃ�
	//�u�����h�̎d�����w��
	SetDrawBlendMode(DX_BLENDMODE_MULA, m_fadeValue);
	//DrawBox(0, 0, 540, 480, 0x00000, true);
	//��ʑS�̂�^�����ɓh��Ԃ�
	//DrawGraph(0, 200, GradH_, true);
	//�ύX�����猳�ɖ߂�
	DrawBox(0, 0, Game::kScreenWindth, Game::kScreenHeight, 0x00000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	//DrawString(300, 200, L"TitleScene", 0xfffff);
}
