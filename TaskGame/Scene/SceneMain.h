#pragma once
#include "SceneBase.h"

//�@�v���g�^�C�v�錾
class Field;
class Player;
class MapChip;
class InputState;
class SceneSelect;
class ScenePause;

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

private:
	//static constexpr int m_fadeInterval = 10;
	 static constexpr int m_fadeInterval = 30;
	int m_fadeTimer = m_fadeInterval; //�t�F�[�h�^�C�}�[
	float m_fadeValue = 255; //����`�Ƃ̃u�����h�

	int m_numCount = 0;
	int m_handle = 0;
	int m_backHandle;
	
	int m_enterSESound = 0;
	int m_moveSESound = 0;
	int m_pauseSESound = 0;
	int m_clearSESound = 0;
	int m_gamePlayBgSound = 0;

	int m_clearFont = 0;
	int m_guideFont = 0;
	int m_scoreFont = 0;

	int m_setBlend = 0;

	int m_test = 1;

	int m_stageNum = 0;
	int m_minNum = 0;
	int m_index = 70;

	bool m_fadeColor = false;

	int m_pauseNum = 0;
	
	int m_stepNum = 0;

	bool m_gameOverFlag = false;

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

	//�X�R�A�i���j
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

