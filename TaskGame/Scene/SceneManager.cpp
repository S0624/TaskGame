#include "SceneManager.h"
#include"SceneBase.h"

void SceneManager::ChangeScene(SceneBase* scene)
{
	if (!m_scene.empty())
	{
		delete m_scene.front();		//top�͂Ă��؂�̗v�f��Ԃ�
		m_scene.pop_front();		//����炷
	}
	m_scene.push_front(scene);		//�������
}

void SceneManager::PushScene(SceneBase* scene)
{
	m_scene.push_front(scene);		//�������
}

void SceneManager::PopScene()
{
	if (m_scene.size() > 1)
	{
		//�|�b�v�̌��ʁA�V�[�����[���ɂȂ�Ȃ��悤�ɂ���	
		delete m_scene.front();
		m_scene.pop_front();
	}
}

void SceneManager::Update(const InputState& input)
{
	m_scene.front()->Update(input);
}

void SceneManager::Draw()
{
	for (int i = m_scene.size() - 1; i >= 0; --i)
	{
		m_scene[i]->Draw();
	}
}
