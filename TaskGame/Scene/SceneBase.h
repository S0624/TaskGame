#pragma once

//	�v���g�^�C�v�錾
class SceneManager;

class SceneBase
{
protected:
	SceneManager& manager_;		//�V�[���}�l�[�W���ւ̎Q��
public:
	SceneBase(SceneManager& manager) : manager_(manager) {}
	virtual ~SceneBase() {};
	//�V�[�����X�V����
	//virtual void Update(const InputState& input) = 0;
	//�V�[����`�悷��
	virtual void Draw() = 0;

private:
};

