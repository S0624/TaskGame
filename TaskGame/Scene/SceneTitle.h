#pragma once
#include "SceneBase.h"

class InputState;
//�^�C�g���V�[��

class SceneTitle : public SceneBase
{
private:
	static constexpr int m_fadeInterval = 30;
	int m_fadeTimer = m_fadeInterval; //�t�F�[�h�^�C�}�[
	int m_fadeValue = 255; //����`�Ƃ̃u�����h�

	//�t�F�[�h�C���̎���Updeta�֐�
	void FadeInUpdate(const InputState& input);
	//�ʏ��Ԃ�Update�֐�
	void NormalUpdate(const InputState& input);
	//�t�F�[�h�A�E�g�̎���Update�֐�
	void FadeOutUpdate(const InputState& input);
	//Update�p�����o�֐��|�C���^
	void (SceneTitle::* m_updateFunc)(const InputState& input);

	//int m_test;
	int m_numCount = 1;
	int m_font;
	int m_strTitle;
	int m_strEx;
	int m_strNum;

public:
	SceneTitle(SceneManager& manager);
	~SceneTitle();

	void Update(const InputState& input);
	void Draw();

	int SelectNum();

};