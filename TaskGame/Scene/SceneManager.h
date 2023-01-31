#pragma once

#include<deque>

//�@�v���g�^�C�v�錾
class SceneBase;
class InputState;

class SceneManager
{
private:
	std::deque<SceneBase*> m_scene;

public:
	//�V�[���̐؂�ւ����s������
	void ChangeScene(SceneBase* scene);
	//�V�[������ɋl��
	void PushScene(SceneBase* scene);
	//��ԏ�̃V�[�����폜����
	void PopScene();
	//�X�V���s��
	void Update(const InputState& input);
	//�V�[���̕`��
	void Draw();

};

