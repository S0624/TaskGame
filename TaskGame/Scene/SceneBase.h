#pragma once

//	�v���g�^�C�v�錾
class SceneManager;
class InputState;

class SceneBase
{
protected:
	SceneManager& m_manager;		//�V�[���}�l�[�W���ւ̎Q��
private:

public:
	SceneBase(SceneManager& manager) : m_manager(manager) {}
	virtual ~SceneBase() {};
	//�V�[�����X�V����
	virtual void Update(const InputState& input) = 0;
	//�V�[����`�悷��
	virtual void Draw() = 0;

};

