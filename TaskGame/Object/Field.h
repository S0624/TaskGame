#pragma once

class Field
{
public:
	//盤面のサイズ
	static constexpr int kSize = 50;		//横
	static constexpr int kFieldX = 6;		//横
	static constexpr int kFieldY = 10;		//縦
	static constexpr int kWidth = 100;		//横幅
	static constexpr int kHeight = 50;		//高さ

private:
	// 現在の盤面データ
	int m_field[kFieldY][kFieldX];

public:
	Field();
	~Field() {};

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