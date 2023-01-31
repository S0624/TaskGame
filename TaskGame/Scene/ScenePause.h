#pragma once
#include "SceneBase.h"

class InputState;
class SceneManager;
//ポーズシーン
class ScenePause :public SceneBase
{
private:

public:
    ScenePause(SceneManager& manager);
    ~ScenePause();
    virtual void Update(const InputState& input);
    void Draw();
};

