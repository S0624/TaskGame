#include "DxLib.h"

#include"Scene/SceneTitle.h"
#include"Scene/SceneSelect.h"
#include"Scene/SceneManager.h"
#include"UI/InputState.h"
#include "UI/game.h"

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    // window���[�h�ݒ�
    //ChangeWindowMode(Game::kWindowMode);
    bool isWindowMode = true;
    ChangeWindowMode(isWindowMode);

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
    bool isTriggerEnter = false;

    // �_�u���o�b�t�@���[�h
    SetDrawScreen(DX_SCREEN_BACK);

    input = new InputState;
    scene = new SceneManager;
    scene->ChangeScene(new SceneTitle(*scene));
    //scene->ChangeScene(new SceneSelect(*scene));
    while (ProcessMessage() == 0)
    {
        LONGLONG time = GetNowHiPerformanceCount();

        if (DxLib::CheckHitKey(KEY_INPUT_LALT))
        {
            if (DxLib::CheckHitKey(KEY_INPUT_RETURN))
            {
                if (!isTriggerEnter)
                {
                    isWindowMode = !isWindowMode;
                    ChangeWindowMode(isWindowMode);

                }
                isTriggerEnter = true;
            }
            else
            {
                isTriggerEnter = false;
            }
        }

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