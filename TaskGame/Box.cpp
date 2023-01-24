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
	m_pos(3,3)
{

}
Box::~Box()
{
	//DeleteGraph(m_handle);		//画像のデリート
}
void Box::Init()
{
	//m_pos.x = 3;				//プレイヤーの初期位置
	//m_pos.y = 3;				//プレイヤーの初期位置

}

void Box::Update()
{
	MoveBox();				//プレイヤーの移動処理を呼び出す
}

void Box::MoveBox()
{
	Vec2 vec = { 0.0f,0.0f };	//速度ベクトル
	if (!IsPut())
	{
		kIsflag = true;
	}
	else
	{
		kIsflag = false;
	}
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

	m_pos += vec;
}

bool Box::IsMoveUp()
{
	int indexX = m_pos.x;
	int indexY = m_pos.y;
	// すでに一番下にある場合
	if (indexY >= (Field::kFieldY + 1)) return false;

	// 一つ下にブロックが置かれている場合
	if (m_pField->IsMovable(indexX, indexY - 1)) return false;

	return true;
}

bool Box::IsMoveDown()
{
	int indexX = m_pos.x;
	int indexY = m_pos.y;
	// すでに一番下にある場合
	if (indexY >= (Field::kFieldY - 1)) return false;

	// 一つ下にブロックが置かれている場合
	if (m_pField->IsMovable(indexX, indexY + 1)) return false;

	return true;
}

bool Box::IsMoveLeft()
{
	int indexX = m_pos.x;
	int indexY = m_pos.y;
	// すでに一番左にある場合
	if (indexX >= (Field::kFieldX + 1)) return false;

	// 一つ左にブロックが置かれている場合
	if (m_pField->IsMovable(indexX - 1, indexY)) return false;

	return true;
}

bool Box::IsMoveRight()
{
	int indexX = m_pos.x;
	int indexY = m_pos.y;
	// すでに一番右にある場合
	if (indexX >= (Field::kFieldX - 1)) return false;

	// 一つ右にブロックが置かれている場合
	if (m_pField->IsMovable(indexX + 1, indexY)) return false;

	return true;
}

bool Box::IsPut()
{
	int indexX = m_pos.x;
	int indexY = m_pos.y;

	// 箱が置いている場合
	if (m_pField->IsPlaced(indexX, indexY)) return false;

	return true;
}

void Box::Draw()
{
	int posX = Field::kSize * m_pos.x;
	int posY = Field::kSize * m_pos.y;

	DrawBox(posX + Field::kWidth, posY + Field::kHeight,			//表示座標
		(posX + Field::kSize) + Field::kWidth, (posY + Field::kSize) + Field::kHeight,
		GetColor(0, 0, 255), kIsflag);

	//DrawFormatString(0, 40, GetColor(255, 0, 0), "%d", posX);
	//DrawFormatString(0, 60, GetColor(255, 0, 0), "%d", posY);
}