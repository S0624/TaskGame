#pragma once
#include "SceneBase.h"

class InputState;
class SceneManager;
//ポーズシーン
class ScenePause :public SceneBase
{
private:
    int m_numCount = 1;
    int m_handle = 0;
    int m_pauseFont = 0;
    int m_guideFont = 0;

public:
    ScenePause(SceneManager& manager);
    ~ScenePause();
    virtual void Update(const InputState& input);
    void Draw();
};

