#include "DxLib.h"

#include"Scene/SceneTitle.h"
#include"Scene/SceneSelect.h"
#include"Scene/SceneManager.h"
#include"UI/InputState.h"
#include "UI/game.h"

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
    // window���[�h�ݒ�
    ChangeWindowMode(Game::kWindowMode);
    SetWindowSizeChangeEnableFlag(true);//�E�B���h�E���[�h�̊g��k���i�T�C�Y�ύX�j���\�ɂȂ�܂�
    SetAlwaysRunFlag(true);//dxlib.exe�Ƀt�H�[�J�X���킹�Ȃ��Ă��X�V�����𑱂��Ă����֐��ł�

    // �E�C���h�E���ݒ�
    SetMainWindowText(L"�Еt����");
    
    // ��ʃT�C�Y�̐ݒ�
    SetGraphMode(Game::kScreenWindth, Game::kScreenHeight, Game::kColorDepth);

    if (DxLib_Init() == -1)        // �c�w���C�u��������������
    {
        return -1;            // �G���[���N�����璼���ɏI��
    }

    SceneManager* scene;
    InputState* input;

    // �_�u���o�b�t�@���[�h
    SetDrawScreen(DX_SCREEN_BACK);

    input = new InputState;
    scene = new SceneManager;
    scene->ChangeScene(new SceneTitle(*scene));
    //scene->ChangeScene(new SceneSelect(*scene));
    while (ProcessMessage() == 0)
    {
        LONGLONG time = GetNowHiPerformanceCount();

        // ��ʂ̃N���A
        ClearDrawScreen();
        input->Update();
        scene->Update(*input);
        scene->Draw();
        // ����ʂ�\��ʂ����ւ���
        ScreenFlip();

        // esc�L�[����������I������
        if (input->IsPressed(InputType::end))
        {
            break;
        }
        // fps��60�ɌŒ�
        while (GetNowHiPerformanceCount() - time < 16667)
        {

        }
    }
    delete input;
    delete scene;
    DxLib_End();                // �c�w���C�u�����g�p�̏I������

    return 0;                // �\�t�g�̏I��
}