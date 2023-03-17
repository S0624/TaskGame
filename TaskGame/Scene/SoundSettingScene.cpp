#include "SoundSettingScene.h"
#include"../UI/InputState.h"
#include"../SoundManager.h"
#include"DxLib.h"
#include"SceneManager.h"

namespace
{
    constexpr int init_wait_interval = 60;  //キー入力町間隔初期値
    constexpr int wait_interval_decrement_period = 5;  //入力町間隔が落ちていく感覚
}

void SoundSettingScene::AcceleraChangeBGMVolume(const InputState& input, InputType inputtype, int changeVal)
{
    //auto& soundMgr = SoundManager::GetInstance();
    //if (input.IsPressed(inputtype))
    //{
    //    if (input.IsTrigger(inputtype)) //押した瞬間
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
    //    if (input.IsTriggered(inputtype)) //押した瞬間
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
    constexpr int pw_width = 450;                            //キーコンフィグ枠の幅
    constexpr int pw_height = 350;                            //キーコンフィグ枠の高さ
    constexpr int pw_start_x = (640 - pw_width) / 2 + 50;    //キーコンフィグ枠に左
    constexpr int pw_start_y = (480 - pw_height) / 2 + 50;    //キーコンフィグ枠上

    //サウンドセッテイングセロファン(黒い)
    DrawBox(pw_start_x, pw_start_y,
        pw_start_x + pw_width,
        pw_start_y + pw_height, 0x008800, true);

    //キーコンフィグメッセージ
    DrawString(pw_start_x + 10, pw_start_y + 10, L"SoundSetting", 0xffffaa);

    auto& soundMgr = SoundManager::GetInstance();
    //BGMの設定
    DrawFormatString(pw_start_x + 20, pw_start_y + 40, 0xffffaa, L"SE　Volume = %d", soundMgr.GetSEVolume());
    //SEの設定
    DrawFormatString(pw_start_x + 20, pw_start_y + 80, 0xffffaa, L"BGM　Volume = %d", soundMgr.GetBGVolume());


    //サウンドセッテイング枠線
    DrawBox(pw_start_x, pw_start_y,
        pw_start_x + pw_width,
        pw_start_y + pw_height, 0xffffff, false);
}
