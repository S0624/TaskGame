#pragma once
#include "SceneBase.h"

class InputState;
class SceneManager;
class SceneMain;
//ポーズシーン
class ScenePause :public SceneBase
{
private:
    SceneMain* pMain = 0;
    void SetField(SceneMain* pMain) { pMain = pMain; }
    //int kPauseNum = 1;
    int m_handle = 0;
    int m_enterSESound = 0;
    int m_moveSESound = 0;
    int m_pauseSESound = 0;
    int m_pauseFont = 0;
    int m_guideFont = 0;

    int m_movingX = 375;

public:
    ScenePause(SceneManager& manager);
    ~ScenePause();
    virtual void Update(const InputState& input);
    void Draw();
    int CursolUpdate();
};

