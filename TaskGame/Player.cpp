#include"DxLib.h"
#include "Player.h"
#include"Field.h"
#include"Box.h"
#include"Pad.h"

namespace
{
	//int kLRReoeatFrame = 8;
}
Player::Player() :
	m_pField(nullptr),
	m_pBox(nullptr),
	m_pos(2,2),
	m_handlePos(25),
	m_handle(0),
	m_imgidx(0)
{
	m_pBox = new Box;
}
Player::~Player()
{
	DeleteGraph(m_handle);		//画像のデリート
}
void Player::Init()
{
	m_handle = LoadGraph("../Date/Player.png");		//画像の読み込み
}

void Player::Update()
{
	MovePlayer();				//プレイヤーの移動処理を呼び出す
}

void Player::MovePlayer()
{
	//constexpr float speed = 2.0f;		//プレイヤーの移動速度

	Vec2 vec = { 0.0f,0.0f };	//速度ベクトル

	Pad::update();

	//かくかくにしたい移動
	if (Pad::isTrigger(PAD_INPUT_DOWN))		//下を押された時の処理
	{
		if (IsMoveDown())
		{
			vec.y = +1.0f;
		}
		//m_imgidx = 0;						//画像の場所の指定
	}
	else if (Pad::isTrigger(PAD_INPUT_UP))	//上を押された時の処理
	{
		if (IsMoveUp())
		{
			vec.y = -1.0f;
		}
		//m_imgidx = 1;						//画像の場所の指定
	}
	if (Pad::isTrigger(PAD_INPUT_LEFT))		//左を押された時の処理
	{
		if (IsMoveLeft())
		{
			vec.x = -1.0f;
		}
		//m_imgidx = 2;						//画像の場所の指定
	}
	else if (Pad::isTrigger(PAD_INPUT_RIGHT))	//右を押された時の処理
	{
		if (IsMoveRight())
		{
			vec.x = +1.0f;
		}
		//m_imgidx = 3;						//画像の場所の指定
	}

	//if (vec.length() > 0.0f)
	//{
	//	vec.normalize();		//方向にかかわらず大きさを一にする
	//	vec *= speed;			//1の方向にスピードを乗算する
	//}
	m_pos += vec;
}

bool Player::IsMoveUp()
{
	int indexX = m_pos.x;
	int indexY = m_pos.y;
	// すでに一番下にある場合
	if (indexY >= (Field::kFieldY + 1)) return false;

	// 一つ下にブロックが置かれている場合
	if (m_pField->IsMovable(indexX, indexY - 1)) return false;
	
	return true;
}

bool Player::IsMoveDown()
{
	int indexX = m_pos.x;
	int indexY = m_pos.y;
	// すでに一番下にある場合
	if (indexY >= (Field::kFieldY - 1)) return false;

	// 一つ下にブロックが置かれている場合
	if (m_pField->IsMovable(indexX, indexY + 1)) return false;

	return true;
}

bool Player::IsMoveLeft()
{
	int indexX = m_pos.x;
	int indexY = m_pos.y;
	// すでに一番左にある場合
	if (indexX >= (Field::kFieldX + 1)) return false;

	// 一つ左にブロックが置かれている場合
	if (m_pField->IsMovable(indexX - 1, indexY)) return false;

	return true;
}

bool Player::IsMoveRight()
{
	int indexX = m_pos.x;
	int indexY = m_pos.y;
	// すでに一番右にある場合
	if (indexX >= (Field::kFieldX - 1)) return false;

	// 一つ右にブロックが置かれている場合
	if (m_pField->IsMovable(indexX + 1, indexY)) return false;

	return true;
}

void Player::Draw()
{
	int posX = Field::kSize * m_pos.x;
	int posY = Field::kSize * m_pos.y;

	DrawBox(posX + Field::kWidth, posY + Field::kHeight,			//表示座標
		(posX + Field::kSize) + Field::kWidth, (posY + Field::kSize) + Field::kHeight,
		GetColor(255,0,255),true);


	//DrawRectRotaGraph(posX + Field::kWidth + m_handlePos,
	//	posY + Field::kHeight + m_handlePos,			//表示座標
	//	48 * 0, 48 * m_imgidx,							//切り取り左上
	//	48, 48,							//幅、高さ
	//	2.5f, 0.0f,						//拡大率、回転角度
	//	m_handle, true);
	//m_pBox->Draw();
	

	DrawFormatString(0, 0, GetColor(255, 255, 255), "%d", posX);
	DrawFormatString(0, 20, GetColor(255, 255, 255), "%d", posY);
	DrawFormatString(0, 40, GetColor(255, 0, 0), "%f", m_pBox-> GetPos().x);
	DrawFormatString(0, 60, GetColor(255, 0, 0), "%f", m_pBox->GetPos().y);
}