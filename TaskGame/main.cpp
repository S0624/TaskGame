#include "DxLib.h"

#include"Scene/SceneTitle.h"
#include"Scene/SceneSelect.h"
#include"Scene/SceneManager.h"
#include"UI/InputState.h"
#include "UI/game.h"

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    // windowモード設定
    //ChangeWindowMode(Game::kWindowMode);
    bool isWindowMode = true;
    ChangeWindowMode(isWindowMode);

    // ウインドウ名設定
    SetMainWindowText(L"片付け番");

    // 画面サイズの設定
    SetGraphMode(Game::kScreenWindth, Game::kScreenHeight, Game::kColorDepth);

    if (DxLib_Init() == -1)        // ＤＸライブラリ初期化処理
    {
        return -1;            // エラーが起きたら直ちに終了
    }

    SceneManager* scene;
    InputState* input;
    bool isTriggerEnter = false;

    // ダブルバッファモード
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

        // 画面のクリア
        ClearDrawScreen();
        input->Update();
        scene->Update(*input);
        scene->Draw();
        // 裏画面を表画面を入れ替える
        ScreenFlip();

        // escキーを押したら終了する
        if (input->IsPressed(InputType::end))
        {
            break;
        }
        // fpsを60に固定
        while (GetNowHiPerformanceCount() - time < 16667)
        {

        }
    }
    delete input;
    delete scene;
    DxLib_End();                // ＤＸライブラリ使用の終了処理

    return 0;                // ソフトの終了
}