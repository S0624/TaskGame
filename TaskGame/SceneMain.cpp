#include "SceneMain.h"
#include"Player.h"
#include"Field.h"
#include"Box.h"
//#include"DxLib.h"

namespace {
	//Player* m_pPlayer;		//Playerクラスをポインタで宣言
	//Field* m_pField;		//Fieldクラスをポインタで宣言
}

SceneMain::SceneMain()
{
	m_pPlayer = new Player;
	m_pField = new Field;
	m_pBox = new Box;
}

SceneMain::~SceneMain()
{
	delete m_pPlayer;		//メモリの削除
	delete m_pField;		//メモリの削除
	delete m_pBox;		//メモリの削除
}

void SceneMain::Init()
{
	m_pPlayer->Init();		//プレイヤークラスの初期化
	m_pField->Init();		//フィールドクラスの初期化
	m_pBox->Init();
	m_pPlayer->setField(m_pField);
	m_pBox->setField(m_pField);
}

void SceneMain::Update()
{
	m_pPlayer->Update();	//プレイヤークラスの更新処理
	m_pField->Update();		//フィールドクラスの更新処理
	m_pBox->Update();
}

void SceneMain::Draw()
{
	m_pField->Draw();		//フィールドクラスの描画処理
	m_pPlayer->Draw();		//プレイヤークラスの描画処理
	m_pBox->Draw();
}
