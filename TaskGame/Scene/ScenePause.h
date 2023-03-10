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

    int m_pausehandle = 0;

    float m_Increase = 0.1;
    float m_magnification = 0.0f;
    bool m_cursolFlag = false;

public:
    ScenePause(SceneManager& manager);
    ~ScenePause();
    virtual void PauseInit();

    virtual void Update(const InputState& input);
    void Draw();
    int CursolUpdate();
};

