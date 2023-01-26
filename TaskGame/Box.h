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
	void SetField(Field* pField) { m_pField = pField; }
	void SetPlayer(Player* pPlayer) { m_pPlayer = pPlayer; }
	
	// 現在地の取得
	Vec2 GetPos() const { return m_pos; }
	
	//箱の移動処理
	void MoveBox();

	bool IsTouch(int x, int y);

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
	//Playerクラス
	Player* m_pPlayer;
	//プレイヤーの位置
	Vec2 m_pos;
};
