#include "SoundSettingScene.h"
#include"../UI/InputState.h"
#include"../SoundManager.h"
#include"DxLib.h"
#include"SceneManager.h"

namespace
{
    constexpr int init_wait_interval = 60;  //�L�[���͒��Ԋu�����l
    constexpr int wait_interval_decrement_period = 5;  //���͒��Ԋu�������Ă������o
}

void SoundSettingScene::AcceleraChangeBGMVolume(const InputState& input, InputType inputtype, int changeVal)
{
    //auto& soundMgr = SoundManager::GetInstance();
    //if (input.IsPressed(inputtype))
    //{
    //    if (input.IsTrigger(inputtype)) //�������u��
    //    {
    //        m_pressTimer = 0;
    //        m_waitInterval = init_wait_interval;
    //    }
    //    if (m_pressTimer % m_waitInterval == 0)
    //    {
    //        soundMgr.SetBGMVolume(std::min(soundMgr.GetBGVolume() + changeVal, 255));
    //    }
    //    if (m_pressTimer % wait_interval_decrement_period == 0)
    //    {
    //        m_waitInterval = std::max(m_waitInterval - 1, 1);
    //    }
    //    m_pressTimer++;
    //}
}

void SoundSettingScene::AcceleraChangeSEVolume(const InputState& input, InputType inputtype, int changeVal)
{
    //auto& soundMgr = SoundManager::GetInstance();
    //if (input.IsPressed(inputtype))
    //{
    //    if (input.IsTriggered(inputtype)) //�������u��
    //    {
    //        m_pressTimer = 0;
    //        m_waitInterval = init_wait_interval;
    //    }
    //    if (m_pressTimer % m_waitInterval == 0)
    //    {
    //        soundMgr.SetSEVolume(std::min(soundMgr.GetSEVolume() + changeVal, 255));
    //    }
    //    if (m_pressTimer % wait_interval_decrement_period == 0)
    //    {
    //        m_waitInterval = std::max(m_waitInterval - 1, 1);
    //    }
    //    m_pressTimer++;
    //}
}

SoundSettingScene::SoundSettingScene(SceneManager& manager) :
    SceneBase(manager)
{

}

SoundSettingScene::~SoundSettingScene()
{

}

void SoundSettingScene::Update(const InputState& input)
{
    auto& soundMgr = SoundManager::GetInstance();
    //soundMgr.StopBGMAndSE();
    //BGM
    AcceleraChangeBGMVolume(input, InputType::up, +1);
    AcceleraChangeBGMVolume(input, InputType::down, -1);
    //SE
    AcceleraChangeSEVolume(input, InputType::right, +1);
    AcceleraChangeSEVolume(input, InputType::left, -1);

    if (input.IsTrigger(InputType::pause))
    {
        m_manager.PopScene();
        //soundMgr.SaveSoundConfig();
    }
}

void SoundSettingScene::Draw()
{
    constexpr int pw_width = 450;                            //�L�[�R���t�B�O�g�̕�
    constexpr int pw_height = 350;                            //�L�[�R���t�B�O�g�̍���
    constexpr int pw_start_x = (640 - pw_width) / 2 + 50;    //�L�[�R���t�B�O�g�ɍ�
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
