#pragma once
#include"Vec2.h"

class Field;
class Player;

class Box
{
public:
	Box();
	~Box();

	//初期化
	void Init();
	//更新処理
	void Update();
	// 使用するフィールドのデータを設定する
	void setField(Field* pField) { m_pField = pField; }

	//プレイヤーの移動処理
	void MoveBox();

	//上に動けるかどうかの判定処理
	bool IsMoveUp();
	//下に動けるかどうかの判定処理
	bool IsMoveDown();
	//左に動けるかどうかの判定処理
	bool IsMoveLeft();
	//右に動けるかどうかの判定処理
	bool IsMoveRight();

	//指定の場所に置いているかの判定処理
	bool IsPut();

	//描画処理
	void Draw();
private:
	//fieldクラス
	Field* m_pField;
	//プレイヤーの位置
	Vec2 m_pos;
};
