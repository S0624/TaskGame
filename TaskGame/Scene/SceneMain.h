#pragma once

//�@�v���g�^�C�v�錾
class Player;
class Field;
//class Box;

class SceneMain
{
public:
	SceneMain();
	~SceneMain();

	//������
	void Init()const;
	//�X�V����
	void Update()const;
	//�`�揈��
	void Draw()const;

private:
	Player* m_pPlayer;		//Player�N���X���|�C���^�Ő錾
	Field* m_pField;		//Field�N���X���|�C���^�Ő錾
	//Box* m_pBox;		//Field�N���X���|�C���^�Ő錾
};

