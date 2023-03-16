#pragma once
#include "SceneBase.h"
#include <memory>
//�@�v���g�^�C�v�錾
class Field;
class Player;
class MapChip;
class InputState;
class SceneSelect;
class ScenePause;
class CreateEffect;

class FieldInformation;

class SceneMain : public SceneBase
{
private:
	Player* m_pPlayer;		//Player�N���X���|�C���^�Ő錾
	Field* m_pField;		//Field�N���X���|�C���^�Ő錾
	FieldInformation* m_pInformation;
	SceneSelect* m_pSelect;
	MapChip* m_pMap;
	ScenePause* m_pPause = 0;
	std::shared_ptr<CreateEffect> m_pEffect;

private:
	//static constexpr int m_fadeInterval = 10;
	 static constexpr int m_fadeInterval = 30;
	int m_fadeTimer = m_fadeInterval; //�t�F�[�h�^�C�}�[
	float m_fadeValue = 255; //����`�Ƃ̃u�����h�
	int m_numCount = 0;
	int m_handle = 0;
	int m_backHandle;
	int m_clearHandle = 0;
	int m_gamePlayBgSound = 0;
	int m_clearFont = 0;
	int m_guideFont = 0;
	int m_UIFont = 0;
	int m_scoreFont = 0;
	int m_setBlend = 0;
	int m_selectNum = 1;
	int m_stageNum = 0;
	int m_minNum = 0;
	int m_index = 70;
	bool m_fadeColor = false;
	int m_pauseNum = 0;
	bool m_gameOverFlag = false;
	int m_gravity = 1;
	int m_overPosY = 0;
	int m_buttonHandle = 0;
	int m_stepColor = 0xffffff;
	int m_stepNum = 0;
	int m_LimitNum = 0;

	//�t�F�[�h�C���̎���Updeta�֐�
	void FadeInUpdate(const InputState& input);
	//�ʏ��Ԃ�Update�֐�
	void NormalUpdate(const InputState& input);
	//�t�F�[�h�A�E�g�̎���Update�֐�
	void FadeOutUpdate(const InputState& input);
	//Update�p�����o�֐��|�C���^
	void (SceneMain::* m_updateFunc)(const InputState& input);

	//���[�h�n�̊֐��܂Ƃ�
	void InitLoad();
	//�T�E���h�n�̊֐��܂Ƃ�
	void InitSound();

	void DrawBackground();
	//�Q�[���N���A���̉��o
	void DrawGameClear();
	//�Q�[���I�[�o�[���̉��o
	void DrawGameOver();
	//UI�̕\��
	void DrawUI();
	//�X�R�A
	void DrawScore();

public:
	SceneMain(SceneManager& manager);
	~SceneMain();

	//�X�V����
	void Update(const InputState& input);
	
	void CursorUpdate(const InputState& input);

	//�`�揈��
	void Draw();
};

