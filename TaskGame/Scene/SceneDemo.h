//#pragma once
//#include "SceneBase.h"
//#include<memory>	//�u�X�}�[�g�|�C���^�v���g�����߂�include
//class InputState;
//
//class SceneDemo : public SceneBase
//{
//private:
//	//std::shared_ptr<MapChip>m_map;
//	static constexpr int m_fadeInterval = 30;
//	int m_fadeTimer = m_fadeInterval; //�t�F�[�h�^�C�}�[
//	float m_fadeValue = 255; //����`�Ƃ̃u�����h�
//
//	//�t�F�[�h�C���̎���Updeta�֐�
//	void FadeInUpdate(const InputState& input);
//	//�ʏ��Ԃ�Update�֐�
//	void NormalUpdate(const InputState& input);
//	//�t�F�[�h�A�E�g�̎���Update�֐�
//	void FadeOutUpdate(const InputState& input);
//	//Update�p�����o�֐��|�C���^
//	void (SceneDemo::* m_updateFunc)(const InputState& input);
//
//private:
//	int m_animation = 0;
//	int m_backHandle = 0;
//	int m_roomHandle = 0;
//	int m_BgSound = 0;
//	int m_displayCount = 0;
//	int m_demoFont = 0;
//	int m_guideFont = 0;
//	int m_strTitle = 0;
//	int m_strEx = 0;
//	int m_strNum = 0;
//	int m_buttonHandle = 0;
//
//
//public:
//	SceneDemo(SceneManager& manager);
//	~SceneDemo();
//
//	void Update(const InputState& input);
//	void Draw();
//};
//
