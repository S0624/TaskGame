#include "SceneMain.h"
#include"Player.h"
#include"Field.h"
#include"Box.h"
//#include"DxLib.h"

namespace {
	//Player* m_pPlayer;		//Player�N���X���|�C���^�Ő錾
	//Field* m_pField;		//Field�N���X���|�C���^�Ő錾
}

SceneMain::SceneMain()
{
	m_pPlayer = new Player;
	m_pField = new Field;
	m_pBox = new Box;
}

SceneMain::~SceneMain()
{
	delete m_pPlayer;		//�������̍폜
	delete m_pField;		//�������̍폜
	delete m_pBox;		//�������̍폜
}

void SceneMain::Init()
{
	m_pPlayer->Init();		//�v���C���[�N���X�̏�����
	m_pField->Init();		//�t�B�[���h�N���X�̏�����
	m_pBox->Init();
	m_pPlayer->setField(m_pField);
	m_pBox->setField(m_pField);
}

void SceneMain::Update()
{
	m_pPlayer->Update();	//�v���C���[�N���X�̍X�V����
	m_pField->Update();		//�t�B�[���h�N���X�̍X�V����
	m_pBox->Update();
}

void SceneMain::Draw()
{
	m_pField->Draw();		//�t�B�[���h�N���X�̕`�揈��
	m_pPlayer->Draw();		//�v���C���[�N���X�̕`�揈��
	m_pBox->Draw();
}
