#pragma once

#include<deque>

//�@�v���g�^�C�v�錾
class SceneBase;

class SceneManager
{
public:
	//�V�[���̐؂�ւ����s������
	void ChangeScene();
	//�V�[��

private:
	std::deque<SceneBase*> m_scene;
};

