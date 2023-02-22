#pragma once
#include "SceneBase.h"

//�@�v���g�^�C�v�錾
class Field;
class Player;
class InputState;

class SceneSelect;

class FieldInformation;

class SceneMain : public SceneBase
{
private:
	Player* m_pPlayer;		//Player�N���X���|�C���^�Ő錾
	Field* m_pField;		//Field�N���X���|�C���^�Ő錾
	FieldInformation* m_pInformation;
	SceneSelect* m_pSelect;

private:
	//static constexpr int m_fadeInterval = 10;
	 static constexpr int m_fadeInterval = 30;
	int m_fadeTimer = m_fadeInterval; //�t�F�[�h�^�C�}�[
	float m_fadeValue = 255; //����`�Ƃ̃u�����h�

	int m_numCount = 0;
	int m_handle = 0;
	int m_ClearFont = 0;
	int m_guideFont = 0;

	int num = 0;

	int test = 0;
		//�t�F�[�h�C���̎���Updeta�֐�
	void FadeInUpdate(const InputState& input);
	//�ʏ��Ԃ�Update�֐�
	void NormalUpdate(const InputState& input);
	//�t�F�[�h�A�E�g�̎���Update�֐�
	void FadeOutUpdate(const InputState& input);
	//Update�p�����o�֐��|�C���^
	void (SceneMain::* m_updateFunc)(const InputState& input);

public:
	SceneMain(SceneManager& manager);
	~SceneMain();

	//�X�V����
	void Update(const InputState& input);
	
	void CursorUpdate(const InputState& input);

	//�`�揈��
	void Draw();
	//�Q�[���N���A���̉��o
	void DrawGameClear();

};

