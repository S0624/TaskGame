#include"DxLib.h"
#include "Field.h"
#include"testField.h"
#include<cassert>
#include"../UI/game.h"

namespace
{
	//enum
	//{
	//	ground,		//床
	//	wall,		//壁
	//	storage,	//置き場所（箱を置く場所）
	//	box,		//箱
	//	input,		//置かれた
	//	empty,		//何も置かれていない
	//};
	int kRemaining = 0;
	testField m_test;
}

//フィールドクラスのコンストラクタ
Field::Field() :
	m_emptyHandle(0),
	m_boxHandle(0),
	m_wallHandle(0),
	m_pinHandle(0)
{
	for (int y = 0; y < kFieldY; y++)		//fieldの初期化
	{
		for (int x = 0; x < kFieldX; x++)
		{
			m_field[y][x] = 0;
		}
	}

	//m_field[4][4] = 2;	//仮の置き場所
	//m_field[1][3] = 2;	//仮の置き場所
	//m_field[1][4] = 2;	//仮の置き場所

	//m_field[3][3] = 3;	//仮の置き場所
	//m_field[4][3] = 3;	//仮の置き場所
	//m_field[5][4] = 3;	//仮の置き場所
}

Field::~Field()
{
	DeleteGraph(m_emptyHandle);
	DeleteGraph(m_wallHandle);
	DeleteGraph(m_pinHandle);
	DeleteGraph(m_boxHandle);
}

//フィールドクラスの初期化
void Field::Init()
{	
	m_emptyHandle = LoadGraph("../Date/floor.png");		//画像の読み込み
	m_wallHandle = LoadGraph("../Date/wall.png");		//画像の読み込み
	m_pinHandle = LoadGraph("../Date/pin.png");		//画像の読み込み
	m_boxHandle = LoadGraph("../Date/box.png");		//画像の読み込み
}

//フィールドクラスの更新処理
void Field::Update()
{
	kRemaining = 0;
	for (int y = 0; y < kFieldY; y++)		//fieldにある置き場所のカウント
	{
		for (int x = 0; x < kFieldX; x++)
		{
			if (m_field[y][x] == storage)
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

			if (m_field[y][x] != empty)
			{
				DrawRectRotaGraph(posX + kWidth + (25),
					posY + kHeight + (25),			//表示座標
					0, 0,							//切り取り左上
					16, 16,							//幅、高さ
					3.0f, 0.0f,						//拡大率、回転角度
					m_emptyHandle, true);
			}

			if (m_field[y][x] == wall)
			{

			DrawRectRotaGraph(posX + kWidth + (25),
				posY + kHeight + (25),			//表示座標
				0, 0,							//切り取り左上
				16, 16,							//幅、高さ
				3.0f, 0.0f,						//拡大率、回転角度
				m_wallHandle, true);
			}
			if (m_field[y][x] == storage)
			{
				DrawRectRotaGraph(posX + kWidth + (25),
					posY + kHeight + (25),			//表示座標
					16 * 0, 0,						//切り取り左上
					16, 16,							//幅、高さ
					2.5f, 0.0f,						//拡大率、回転角度
					m_pinHandle, true);
			}
			if (m_field[y][x] == box)
			{
				DrawRectRotaGraph(posX + kWidth + (25),
					posY + kHeight + (25),			//表示座標
					0, 0,							//切り取り左上
					16, 21,							//幅、高さ
					2.5f, 0.0f,						//拡大率、回転角度
					m_boxHandle, true);
			}
			if (m_field[y][x] == input)
			{
				DrawRectRotaGraph(posX + kWidth + (25),
					posY + kHeight + (25),			//表示座標
					16, 0,							//切り取り左上
					16, 21,							//幅、高さ
					2.5f, 0.0f,						//拡大率、回転角度
					m_boxHandle, true);
			}
		}
	}
	DrawFormatString(300, 0, GetColor(255, 255, 255), "残り:%d", kRemaining);
}

//フィールドの中身を見て動けるかを返す処理
bool Field::IsMovable(int x, int y, int posX, int posY)
{
	assert((x >= 0) && (x <= kFieldX - 1));		//アサート
	assert((y >= 0) && (y <= kFieldY - 1));		//範囲外だと処理を止める

	if (m_field[y][x] == empty)	return true;		//何もないとその先に行けなくする
	if (m_field[y][x] == wall)	return true;		//壁だとその先に行けなくする
	
	if (m_field[y][x] == box)						//箱を押したときの処理
	{
		if (m_field[y + posY][x + posX] == ground)	//箱を押してその先に何もない時の処理
		{
			m_field[y][x] = ground;					//現在地に空白を入れる
			m_field[y + posY][x + posX] = box;	//箱をずらす
			return false;
		}
		if (m_field[y + posY][x + posX] == storage)	//箱を押してその先が置き場所だった場合の処理
		{
			m_field[y][x] = ground;					//現在地に空白を入れる
			m_field[y + posY][x + posX] = input;	//箱を入れた時の処理
			return false;
		}
		return true;							//それ以外はtrueを返す
	}
	if (m_field[y][x] == input)						//置かれている箱を動かすときの処理
	{
		if (m_field[y + posY][x + posX] == ground)
		{
			m_field[y][x] = storage;
			m_field[y + posY][x + posX] = box;
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

int Field::test(int test[kFieldY][kFieldX])
{
	for (int i = 0; i < kFieldX; i++)		//fieldの初期化
	{
		for (int j = 0; j < kFieldY; j++)
		{
			m_field[j][i] = test[j][i];
		}
	}
	return 0;
}

