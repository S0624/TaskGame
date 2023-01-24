#include "Box.h"
#include"DxLib.h"
#include "Player.h"
#include"Field.h"
#include"Pad.h"

namespace
{
	bool kIsflag = false;
}

Box::Box() :
	m_pField(nullptr),
	m_pos()
{

}
Box::~Box()
{
	//DeleteGraph(m_handle);		//画像のデリート
}
void Box::Init()
{
	m_pos.x = 3;				//プレイヤーの初期位置
	m_pos.y = 3;				//プレイヤーの初期位置
	//m_pos.x = 175;				//プレイヤーの初期位置
	//m_pos.y = 125;				//プレイヤーの初期位置

	//m_handle = LoadGraph("../Date/Box.png");		//画像の読み込み
}

void Box::Update()
{
	MoveBox();				//プレイヤーの移動処理を呼び出す
}

void Box::MoveBox()
{
	constexpr float speed = 2.0f;		//プレイヤーの移動速度

	Vec2 vec = { 0.0f,0.0f };	//速度ベクトル

	Pad::update();

	////かくかくにしたい移動
	//if (Pad::isTrigger(PAD_INPUT_DOWN))		//下を押された時の処理
	//{
	//	if (IsMoveDown())
	//	{
	//		vec.y = +1.0f;
	//	}
	//	//m_imgidx = 0;						//画像の場所の指定
	//}
	//else if (Pad::isTrigger(PAD_INPUT_UP))	//上を押された時の処理
	//{
	//	if (IsMoveUp())
	//	{
	//		vec.y = -1.0f;
	//	}
	//	//m_imgidx = 1;						//画像の場所の指定
	//}
	//if (Pad::isTrigger(PAD_INPUT_LEFT))		//左を押された時の処理
	//{
	//	if (IsMoveLeft())
	//	{
	//		vec.x = -1.0f;
	//	}
	//	//m_imgidx = 2;						//画像の場所の指定
	//}
	//else if (Pad::isTrigger(PAD_INPUT_RIGHT))	//右を押された時の処理
	//{
	//	if (IsMoveRight())
	//	{
	//		vec.x = +1.0f;
	//	}
	//	//m_imgidx = 3;						//画像の場所の指定
	//}

	////if (vec.length() > 0.0f)
	////{
	////	vec.normalize();		//方向にかかわらず大きさを一にする
	////	vec *= speed;			//1の方向にスピードを乗算する
	////}
	//m_pos += vec;
}

bool Box::IsMoveUp()
{
	int indexX = m_pos.x;
	int indexY = m_pos.y;
	// すでに一番下にある場合
	if (indexY >= (Field::kFieldY + 1)) return false;

	// 一つ下にブロックが置かれている場合
	if (m_pField->IsBlockDate(indexX, indexY - 1)) return false;

	return true;
}

bool Box::IsMoveDown()
{
	int indexX = m_pos.x;
	int indexY = m_pos.y;
	// すでに一番下にある場合
	if (indexY >= (Field::kFieldY - 1)) return false;

	// 一つ下にブロックが置かれている場合
	if (m_pField->IsBlockDate(indexX, indexY + 1)) return false;

	return true;
}

bool Box::IsMoveLeft()
{
	int indexX = m_pos.x;
	int indexY = m_pos.y;
	// すでに一番左にある場合
	if (indexX >= (Field::kFieldX + 1)) return false;

	// 一つ左にブロックが置かれている場合
	if (m_pField->IsBlockDate(indexX - 1, indexY)) return false;

	return true;
}

bool Box::IsMoveRight()
{
	int indexX = m_pos.x;
	int indexY = m_pos.y;
	// すでに一番右にある場合
	if (indexX >= (Field::kFieldX - 1)) return false;

	// 一つ右にブロックが置かれている場合
	if (m_pField->IsBlockDate(indexX + 1, indexY)) return false;

	return true;
}

void Box::Draw()
{
	//int posX = Field::kSize * m_pos.x;
	//int posY = Field::kSize * m_pos.y;

	//DrawBox(posX + Field::kWidth, posY + Field::kHeight,			//表示座標
	//	(posX + Field::kSize) + Field::kWidth, (posY + Field::kSize) + Field::kHeight,
	//	GetColor(0, 0, 255), true);

	DrawBox((3 * 50) + 100, (3 * 50) + 50,			//表示座標
		((3 * 50) + 50) + 100, ((3 * 50) + 50) + 50,
		GetColor(0, 255, 255), kIsflag);

	//DrawRectRotaGraph(posX + Field::kWidth + m_handlePos,
	//	posY + Field::kHeight + m_handlePos,			//表示座標
	//	48 * 0, 48 * m_imgidx,							//切り取り左上
	//	48, 48,							//幅、高さ
	//	2.5f, 0.0f,						//拡大率、回転角度
	//	m_handle, true);


	//DrawFormatString(0, 40, GetColor(255, 0, 0), "%d", posX);
	//DrawFormatString(0, 60, GetColor(255, 0, 0), "%d", posY);
}