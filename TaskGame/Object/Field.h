#pragma once
#include<vector>

class Field
{
public:
	//盤面のサイズ
	static constexpr int kSize = 48;		//横
	static constexpr int kFieldX = 6;		//横
	static constexpr int kFieldY = 10;		//縦
	static constexpr int kWidth = 48 * 2;		//横幅
	static constexpr int kHeight = 6 * 10;		//高さ

private:
	//m_field[kFieldY][kFieldX]
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
};