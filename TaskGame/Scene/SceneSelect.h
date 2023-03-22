#pragma once
#include "SceneBase.h"
class MapChip;
class InputState;


class SceneSelect : public SceneBase
{
private:
	MapChip* m_pMap;
	static constexpr int m_fadeInterval = 30;
	int m_fadeTimer = m_fadeInterval; //�t�F�[�h�^�C�}�[
	float m_fadeValue = 255; //����`�Ƃ̃u�����h�

	//�t�F�[�h�C���̎���Updeta�֐�
	void FadeInUpdate(const InputState& input);
	//�ʏ��Ԃ�Update�֐�
	void NormalUpdate(const InputState& input);
	//�t�F�[�h�A�E�g�̎���Update�֐�
	void FadeOutUpdate(const InputState& input);
	//Update�p�����o�֐��|�C���^
	void (SceneSelect::* m_updateFunc)(const InputState& input);

	//int m_test;
	int m_handle;		//�摜
	int m_backHandle;
	int m_BgSound;
	int m_selectFont;	//�t�H���g
	int m_guideFont;	//�������̃t�H���g
	int m_strTitle;		//������̒���
	int m_strEx;		//�������̒���
	int m_strNum;		//������̒���
	int m_fontSize;
	int m_freamAnime = 0;	//�A�j���[�V�������s���t���[��
	int m_freamStop = 0;	//�A�j���[�V�������~�߂Ă���t���[��
	int m_animeNum = 0;			//�A�j���[�V�����̔ԍ�
	int m_countNum = 0;
	int m_displayCount = 0;
	int m_buttonHandle = 0;
	int m_animation = 0;
	int m_boxHandle = 0;
	int m_selectNumIndex = -10;
	int moveindex = 1;
	int frame = 0;

public:
	SceneSelect(SceneManager& manager);
	~SceneSelect();

	void Update(const InputState& input);
	void Draw();
	void DrawBackground();
	void DrawSelectNum();

	int SelectNum(int num);
	//�J�[�\���̈ړ�����
	void MoveCursor(const InputState& input);
	//�C���X�g�̃A�j���[�V����
	void Animation();
};

