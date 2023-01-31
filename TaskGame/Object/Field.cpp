#include"DxLib.h"
#include "Field.h"
#include<cassert>
#include"../UI/game.h"

namespace
{
	enum
	{
		empty,		//何も置かれていない
		wall,		//壁
		storage,	//置き場所（箱を置く場所）
		box,		//箱
		input,		//置かれた
	};

	int kRemaining = 0;
}

//フィールドクラスのコンストラクタ
Field::Field()
{
	for (int y = 0; y < kFieldY; y++)		//fieldの初期化
	{
		for (int x = 0; x < kFieldX; x++)
		{
			m_field[y][x] = 0;
		}
	}

}

//フィールドクラスの初期化
void Field::Init()
{
	//for (int y = 0; y < kFieldY; y++)		//fieldの初期化
	//{
	//	for (int x = 0; x < kFieldX; x++)
	//	{
	//		m_field[y][x] = 0;
	//	}
	//}

	for (int x = 0; x < kFieldX; x++)		//仮で壁の追加
	{
		m_field[0][x] = 1;
		m_field[kFieldY - 1][x] = 1;
	}
	for (int y = 0; y < kFieldY; y++)		//仮で壁の追加
	{
		m_field[y][0] = 1;
		m_field[y][kFieldX - 1] = 1;
	}
	m_field[4][4] = 2;	//仮の置き場所
	m_field[1][3] = 2;	//仮の置き場所
	
	m_field[3][3] = 3;	//仮の置き場所
	m_field[4][3] = 3;	//仮の置き場所
}

//フィールドクラスの更新処理
void Field::Update()
{
	kRemaining = 0;
	for (int y = 0; y < kFieldY; y++)		//fieldにある置き場所のカウント
	{
		for (int x = 0; x < kFieldX; x++)
		{
			if (m_field[y][x] == 2)
			{
				kRemaining++;
			}
		}
	}
	
}

//フィールドクラスの描画処理
void Field::Draw()
{
	for (int y = 0; y < kFieldY; y++)		//fieldの初期化
	{
		for (int x = 0; x < kFieldX; x++)
		{
			int posX = kSize * x;
			int posY = kSize * y;

			if (m_field[y][x] == 0)
			{
				//DrawBox(posX + m_width, posY + m_height,
					//posX + kSize + m_width, posY + kSize + m_height, GetColor(255, 255, 255), false);
			}
			if (m_field[y][x] == 1)
			{
				DrawBox(posX + kWidth, posY + kHeight,
					posX + kSize + kWidth, posY + kSize + kHeight, GetColor(255, 0, 0), true);
			}
			if (m_field[y][x] == 2)
			{
				DrawCircle(posX + kWidth + kSize / 2,
					posY + kHeight + kSize / 2,
					kSize / 4,
					0xfff000, false);
			}
			if (m_field[y][x] == 3)
			{
				DrawBox(posX + kWidth + 5, posY + kHeight + 5,			//表示座標
					(posX + kSize) + kWidth - 5, (posY +kSize) + kHeight - 5,
					GetColor(100, 255, 0), false);
			}
			if (m_field[y][x] == 4)
			{
				DrawBox(posX + kWidth + 5, posY + kHeight + 5,			//表示座標
					(posX + kSize) + kWidth - 5, (posY +kSize) + kHeight - 5,
					GetColor(100, 255, 0), true );
			}
			DrawBox(posX + kWidth, posY + kHeight,
				posX + kSize + kWidth, posY + kSize + kHeight, GetColor(255, 255, 255), false);
		}
	}
	DrawFormatString(300, 0, GetColor(255, 255, 255), "残り:%d", kRemaining);

	//DrawBox(m_width, m_height,
		//m_width * kFieldX,  m_height * kFieldY, GetColor(255, 255, 255), false);
}

//フィールドの中身を見て動けるかを返す処理
bool Field::IsMovable(int x, int y, int posX, int posY)
{
	assert((x >= 0) && (x <= kFieldX - 1));		//アサート
	assert((y >= 0) && (y <= kFieldY - 1));		//範囲外だと処理を止める

	if (m_field[y][x] == 1)	return true;		//壁だとその先に行けなくする
	
	if (m_field[y][x] == 3)						//箱を押したときの処理
	{
		if (m_field[y + posY][x + posX] == 0)	//箱を押してその先に何もない時の処理
		{
			m_field[y][x] = 0;					//現在地に空白を入れる
			m_field[y + posY][x + posX] = 3;	//箱をずらす
			return false;
		}
		if (m_field[y + posY][x + posX] == 2)	//箱を押してその先が置き場所だった場合の処理
		{
			m_field[y][x] = 0;					//現在地に空白を入れる
			m_field[y + posY][x + posX] = 4;	//箱を入れた時の処理
			return false;
		}
		return true;							//それ以外はtrueを返す
	}
	if (m_field[y][x] == 4)						//置かれている箱を動かすときの処理
	{
		if (m_field[y + posY][x + posX] == 0)
		{
			m_field[y][x] = 2;
			m_field[y + posY][x + posX] = 3;
			return false;
		}
		return true;
	}
	return false;
}

//ゲームクリアかどうかを返す処理
bool Field::GameClear()const
{
	if (kRemaining == 0) return true;
	return false;
}