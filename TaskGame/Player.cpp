#include"DxLib.h"
#include "Player.h"
#include"Pad.h"

Player::Player() :
	m_pos(),
	m_handle(0),
	m_imgidx(0)
{

}
Player::~Player()
{
	DeleteGraph(m_handle);		//画像のデリート
}
void Player::Init()
{
	m_pos.x = 150;				//プレイヤーの初期位置
	m_pos.y = 100;				//プレイヤーの初期位置

	m_handle = LoadGraph("../Date/Player.png");		//画像の読み込み
}

void Player::Update()
{
	MovePlayer();				//プレイヤーの移動処理を呼び出す
}

void Player::MovePlayer()
{
	constexpr float speed = 2.0f;		//プレイヤーの移動速度

	Vec2 vec = { 0.0f,0.0f };	//速度ベクトル

	Pad::update();

	if (Pad::isPress(PAD_INPUT_DOWN))		//下を押された時の処理
	{
		vec.y = +2.0f;
		m_imgidx = 0;						//画像の場所の指定
	}
	else if (Pad::isPress(PAD_INPUT_UP))	//上を押された時の処理
	{
		vec.y = -2.0f;
		m_imgidx = 1;						//画像の場所の指定
	}
	if (Pad::isPress(PAD_INPUT_LEFT))		//左を押された時の処理
	{
		vec.x = -2.0f;
		m_imgidx = 2;						//画像の場所の指定
	}
	else if (Pad::isPress(PAD_INPUT_RIGHT))	//右を押された時の処理
	{
		vec.x = +2.0f;
		m_imgidx = 3;						//画像の場所の指定
	}

	if (vec.length() > 0.0f)
	{
		vec.normalize();		//方向にかかわらう大きさを一にする
		vec *= speed;			//1の方向にスピードを乗算する
	}
	m_pos += vec;
}

void Player::Draw()
{
	DrawRectRotaGraph(m_pos.x, m_pos.y,			//表示座標
		48 * 0, 48 * m_imgidx,							//切り取り左上
		48, 48,							//幅、高さ
		2.5f, 0.0f,						//拡大率、回転角度
		m_handle, true);


}