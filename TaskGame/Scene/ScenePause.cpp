#include "ScenePause.h"
#include"SceneManager.h"
#include"../UI/InputState.h"
#include"../UI/game.h"
#include"DxLib.h"

ScenePause::ScenePause(SceneManager& manager) : SceneBase(manager)
{

}
ScenePause::~ScenePause()
{
}

void ScenePause::Update(const InputState& input)
{
	if (input.IsTrigger(InputType::pause))
	{
		m_manager.PopScene();
		return;
	}

}

void ScenePause::Draw()
{
	//constexpr int pw_width = 400;		//�|�[�Y�g�̕�
	//constexpr int pw_height = 300;		//�|�[�Y�g�̍���
	//constexpr int pw_start_x = (Game::kScreenWindth - pw_width) / 2;
	//constexpr int pw_start_y = (Game::kScreenHeight - pw_height) / 2;

	constexpr int width = 400;		//�|�[�Y�g�̕�
	constexpr int height = 300;		//�|�[�Y�g�̍���
	constexpr int widthPos = (640 - width) / 2;
	constexpr int heightPos = (480 - height) / 2;


	SetDrawBlendMode(DX_BLENDMODE_MULA, 225);		//�����������Ƃ�MALA
	//SetDrawBlendMode(DX_BLENDMODE_ADD, 128);		//�����������Ƃ���ADD
	//�|�[�Y�E�B���h�E�Z���t�@��			//�|�[�Y�����b�Z�[�W
	DrawBox(widthPos, heightPos,
		widthPos + width, heightPos + height,
		0x00000, true);

	//���ɖ߂�
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);			//�ʏ�`��ɖ߂�

	//�|�[�Y�����b�Z�[�W
	DrawString(widthPos + 10, heightPos + 10, "�|�[�Y��ʁi�������j", 0xffffff);
	DrawString(widthPos + 50, heightPos + 50 * 1, "�Q�[���ɖ߂�i�������j", 0xffffff);
	DrawString(widthPos + 50, heightPos + 50 * 2, "���g���C�i�������j", 0xffffff);
	DrawString(widthPos + 50, heightPos + 50 * 3, "�^�C�g���i�������j", 0xffffff);

	//�|�[�Y�E�C���h�E�g��
	DrawBox(widthPos, heightPos,
		widthPos + width, heightPos + height,
		0xffffff, false);
}
