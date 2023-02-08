#include "DxLib.h"

#include"Scene/SceneMain.h"
#include"Scene/SceneTitle.h"
#include"Scene/SceneManager.h"
#include"UI/InputState.h"
#include "UI/game.h"

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    // window���[�h�ݒ�
    ChangeWindowMode(Game::kWindowMode);

    // �E�C���h�E���ݒ�
    SetMainWindowText("�Q�[����");

    // ��ʃT�C�Y�̐ݒ�
    SetGraphMode(Game::kScreenWindth, Game::kScreenHeight, Game::kColorDepth);

    if (DxLib_Init() == -1)        // �c�w���C�u��������������
    {
        return -1;            // �G���[���N�����璼���ɏI��
    }
    //SceneMain* main;
    SceneManager* scene;
    InputState* input;

    // �_�u���o�b�t�@���[�h
    SetDrawScreen(DX_SCREEN_BACK);
   // main = new SceneMain;
    input = new InputState;
    scene = new SceneManager;
   scene->ChangeScene(new SceneTitle(*scene));
   // scene->ChangeScene(new SceneMain(*scene));
    //main->Init();
    while (ProcessMessage() == 0)
    {
        LONGLONG time = GetNowHiPerformanceCount();

        // ��ʂ̃N���A
        ClearDrawScreen();
        input->Update();
        //main->Update(*input);
        //main->Draw();
        scene->Update(*input);
        scene->Draw();

        // ����ʂ�\��ʂ����ւ���
        ScreenFlip();

        // esc�L�[����������I������
        if (CheckHitKey(KEY_INPUT_ESCAPE)) break;

        // fps��60�ɌŒ�
        while (GetNowHiPerformanceCount() - time < 16667)
        {

        }
    }

    //delete main;
    delete input;
    delete scene;

    DxLib_End();                // �c�w���C�u�����g�p�̏I������

    return 0;                // �\�t�g�̏I��
}