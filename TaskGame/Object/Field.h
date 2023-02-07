#pragma once
#include<vector>

//#include"testField.h"

class testField;

class Field
{
public:
	//盤面のサイズ
	static constexpr int kSize = 48;		//横
	static constexpr int kFieldX = 20;		//横
	static constexpr int kFieldY = 10;		//縦
	static constexpr int kWidth = kSize * 3;		//横幅
	static constexpr int kHeight = kSize * 1.5;		//高さ

	//enum
	//{
	//	empty,		//何も置かれていない
	//	ground,		//床
	//	wall,		//壁
	//	storage,	//置き場所（箱を置く場所）
	//	box,		//箱
	//	input,		//置かれた
	//};

private:
	// 現在の盤面データ
	int m_field[kFieldY][kFieldX];
	int m_emptyHandle;
	int m_boxHandle;
	int m_wallHandle;
	int m_pinHandle;

public:
	Field();
	~Field();

	//初期化
	void Init();
	//更新処理
	void Update();
	//描画処理
	void Draw();

	//動かせるか配列のデータを見る関数
	bool IsMovable(int indexX, int indexY,int x, int y);

	//ゲームクリアか判定
	bool GameClear()const;

	//お試し
	int test(int test[kFieldY][kFieldX]);

};