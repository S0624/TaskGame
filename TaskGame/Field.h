#pragma once
class Field
{
public:
	Field();
	~Field() {};

	//������
	void Init();
	//�X�V����
	void Update();
	//�`�揈��
	void Draw();
private:
	int m_height;		//����
	int m_width;		//����
};

