#pragma once

//�N���X�̐錾
class Player;
class Field;
class Box;

class SceneMain
{
public:
	SceneMain();
	~SceneMain();

	//������
	void Init();
	//�X�V����
	void Update();
	//�`�揈��
	void Draw();

private:
	Player* m_pPlayer;		//Player�N���X���|�C���^�Ő錾
	Field* m_pField;		//Field�N���X���|�C���^�Ő錾
	Box* m_pBox;		//Field�N���X���|�C���^�Ő錾
};

