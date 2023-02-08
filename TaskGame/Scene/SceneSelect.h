#include "SceneBase.h"

class InputState;
class SceneManager;
//ポーズシーン
class SceneSelect :public SceneBase
{
private:
    int m_numCount = 1;

public:
    SceneSelect(SceneManager& manager);
    ~SceneSelect();
    virtual void Update(const InputState& input);
    void Draw();
};

