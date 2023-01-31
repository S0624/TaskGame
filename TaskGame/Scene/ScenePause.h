#pragma once
#include "SceneBase.h"

class InputState;
class SceneManager;
//ポーズシーン
class ScenePause :public SceneBase
{
private:
    int m_numCount = 1;

public:
    ScenePause(SceneManager& manager);
    ~ScenePause();
    virtual void Update(const InputState& input);
    void Draw();
};

