#include "DxLib.h"

#include"Scene/SceneMain.h"
#include"Scene/SceneTitle.h"
#include"Scene/SceneManager.h"
#include"UI/InputState.h"
#include "UI/game.h"

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    // windowモード設定
    ChangeWindowMode(Game::kWindowMode);

    // ウインドウ名設定
    SetMainWindowText("ゲーム名");

    // 画面サイズの設定
    SetGraphMode(Game::kScreenWindth, Game::kScreenHeight, Game::kColorDepth);

    if (DxLib_Init() == -1)        // ＤＸライブラリ初期化処理
    {
        return -1;            // エラーが起きたら直ちに終了
    }
    //SceneMain* main;
    SceneManager* scene;
    InputState* input;

    // ダブルバッファモード
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

        // 画面のクリア
        ClearDrawScreen();
        input->Update();
        //main->Update(*input);
        //main->Draw();
        scene->Update(*input);
        scene->Draw();

        // 裏画面を表画面を入れ替える
        ScreenFlip();

        // escキーを押したら終了する
        if (CheckHitKey(KEY_INPUT_ESCAPE)) break;

        // fpsを60に固定
        while (GetNowHiPerformanceCount() - time < 16667)
        {

        }
    }

    //delete main;
    delete input;
    delete scene;

    DxLib_End();                // ＤＸライブラリ使用の終了処理

    return 0;                // ソフトの終了
}