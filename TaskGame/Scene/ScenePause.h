#pragma once
#include "SceneBase.h"

class InputState;
class SceneManager;
class SceneMain;
//�|�[�Y�V�[��
class ScenePause :public SceneBase
{
private:
    SceneMain* pMain = 0;
    void SetField(SceneMain* pMain) { pMain = pMain; }
    int m_handle = 0;
    int m_pauseFont = 0;
    int m_guideFont = 0;

    int m_pausehandle = 0;

    double m_Increase = 0.1;
    float m_magnification = 0.0f;
    bool m_cursolFlag = false;

public:
    //�R���X�g���N�^
    ScenePause(SceneManager& manager);
    //�f�X�g���N�^
    ~ScenePause();
    //������
    virtual void PauseInit();

    //�X�V����
    virtual void Update(const InputState& input);
    //�`�揈��
    void Draw();
    //�J�[�\���̍X�V����
    int CursolUpdate();
};

