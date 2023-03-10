#pragma once

namespace Game
{
#ifdef  _DEBUG
    // �E�C���h�E���[�h�ݒ�
    constexpr bool kWindowMode = true;
#else
    constexpr bool kWindowMode = false;
#endif
    // �E�C���h�E��
    const char* const kTitleText = "�Еt����";

    // �E�C���h�E�T�C�Y
    constexpr int kScreenWindth = 1600;
    constexpr int kScreenHeight = 900;

    // �J���[���[�h
    constexpr int kColorDepth = 32;        // 32 or 16
};