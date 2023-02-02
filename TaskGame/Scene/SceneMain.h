#pragma once
#include "SceneBase.h"

//�@�v���g�^�C�v�錾
class Player;
class Field;
class InputState;

class SceneMain : public SceneBase
{
//public:
//	//�Ֆʂ̃T�C�Y
//	static constexpr int kSize = 48;		//��
//	static constexpr int kFieldX = 6;		//��
//	static constexpr int kFieldY = 10;		//�c
//	static constexpr int kWidth = 48 * 10;		//����
//	static constexpr int kHeight = 6 * 15;		//����

private:
	Player* m_pPlayer;		//Player�N���X���|�C���^�Ő錾
	Field* m_pField;		//Field�N���X���|�C���^�Ő錾


private:
	//static constexpr int m_fadeInterval = 10;
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
	void (SceneMain::* m_updateFunc)(const InputState& input);

public:
	SceneMain(SceneManager& manager);
	~SceneMain();

	//������
	void Init()const;
	//�X�V����
	void Update(const InputState& input);
	//�`�揈��
	void Draw();

};

