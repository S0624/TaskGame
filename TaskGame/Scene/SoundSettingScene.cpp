#include "SoundSettingScene.h"
#include"../UI/InputState.h"
#include"../SoundManager.h"
#include"DxLib.h"
#include"SceneManager.h"

namespace
{
    constexpr int init_wait_interval = 60;  //�L�[���͑҂��Ԋu�����l
    constexpr int wait_interval_decrement_period = 5;  //���͑҂��Ԋu�������Ă������o
}

SoundSettingScene::SoundSettingScene(SceneManager& manager) :
    SceneBase(manager)
{

}
void SoundSettingScene::Update(const InputState& input)
{
    auto& soundMgr = SoundManager::GetInstance();
    if (input.IsTrigger(InputType::pause))
    {
        m_manager.PopScene();
    }
}

void SoundSettingScene::Draw()
{
    constexpr int pw_width = 450;                             //�L�[�R���t�B�O�g�̕�
    constexpr int pw_height = 350;                            //�L�[�R���t�B�O�g�̍���
    constexpr int pw_start_x = (640 - pw_width) / 2 + 50;     //�L�[�R���t�B�O�g�ɍ�
    constexpr int pw_start_y = (480 - pw_height) / 2 + 50;    //�L�[�R���t�B�O�g��
    //�T�E���h�Z�b�e�C���O�Z���t�@��(����)
    DrawBox(pw_start_x, pw_start_y,
        pw_start_x + pw_width,
        pw_start_y + pw_height, 0x008800, true);

    //�L�[�R���t�B�O���b�Z�[�W
    DrawString(pw_start_x + 10, pw_start_y + 10, L"SoundSetting", 0xffffaa);
    auto& soundMgr = SoundManager::GetInstance();
    //BGM�̐ݒ�
    DrawFormatString(pw_start_x + 20, pw_start_y + 40, 0xffffaa, L"SE�@Volume = %d", soundMgr.GetSEVolume());
    //SE�̐ݒ�
    DrawFormatString(pw_start_x + 20, pw_start_y + 80, 0xffffaa, L"BGM�@Volume = %d", soundMgr.GetBGVolume());
    //�T�E���h�Z�b�e�C���O�g��
    DrawBox(pw_start_x, pw_start_y,
        pw_start_x + pw_width,
        pw_start_y + pw_height, 0xffffff, false);
}
