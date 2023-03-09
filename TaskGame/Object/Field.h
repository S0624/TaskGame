#pragma once
#include"../UI/Vec2.h"

//#include"testField.h"

class FieldInformation;

class Field
{
public:
	//盤面のサイズ
	static constexpr int kSize = 48;		//横
	static constexpr int kFieldX = 20;		//横
	static constexpr int kFieldY = 12;		//縦
	static constexpr int kWidth = kSize * 5;		//横幅
	static constexpr int kHeight = kSize * 3;		//高さ

private:
	// 現在の盤面データ
	int m_field[kFieldY][kFieldX];
	int m_groundHandle;				//空の時の画像
	int m_boxHandle;				//箱の画像
	int m_wallHandle;				//壁の画像
	int m_pinHandle;				//置き場所の画像

	int m_storageNum;
	bool m_drawFlag;	//移動中の箱を表示するかどうかのフラグ
	float m_boxMoveSpeed;	//箱の移動スピード
	Vec2 m_pos;			//現在の箱の位置
	Vec2 m_boxNextPos;	//次の箱の場所の位置
	int m_boxType;				//箱のタイプ（普通の箱か、置かれているか）
	bool m_moveBox = false;		//箱が移動中かどうか

	enum
	{
		empty,		//何も置かれていない
		ground,		//床
		wall,		//壁
		storage,	//置き場所（箱を置く場所）
		box,		//箱
		input,		//置かれた
		nextPos,		//置かれた
	};

public:
	Field();
	~Field();

	//更新処理
	void Update();
	//描画処理
	void Draw();

	//プレイヤーが動かせるか配列のデータを見る関数
	bool IsMovable(int posX, int posY, int x, int y);
	//
	//プレイヤーの次の場所が動かせるか配列のデータを見る関数
	bool IsMovablePos(int x, int y);

	//ゲームクリアか判定
	bool GameClear()const;

	//フィールドの情報を持ってくる関数
	int FieldInfo(int field[kFieldY][kFieldX]);

	//箱を移動させるための情報を持つ関数
	void MoveFrame(int posX, int posY, int x, int y, int type);
	//箱を移動させる処理
	void MoveFrame();

	//箱が移動中かどうか判定
	bool MoveBox()const;
};