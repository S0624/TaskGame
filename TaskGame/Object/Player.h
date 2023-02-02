#pragma once
#include"../UI/Vec2.h"

//　プロトタイプ宣言
class Field;
class InputState;
//class Box;

class Player
{
private:
	//fieldクラス
	Field* m_pField;
	//Boxクラスをポインタで宣言
	//Box* m_pBox;		

	//プレイヤーの位置
	Vec2 m_pos;
	//プレイヤーの画像をずらす
	int m_handlePos;
	//プレイヤーの画像
	int m_handle;
	//プレイヤーの画像の表示を変更する変数
	int m_imgidx;

	//お試しども
	int m_moveDown;
	int m_moveUp;
	int m_moveLeft;
	int m_moveRight;
	int m_lastMove;

	int m_animationNumber;
	int m_animetionFraem;

	int m_stepCount;
public:
	Player();
	~Player();

	//初期化
	void Init();
	//更新処理
	void Update(const InputState& input);
	// 使用するフィールドのデータを設定する
	void SetField(Field* pField) { m_pField = pField; }
	//void SetBox(Box* pBox) { m_pBox = pBox; }

	// 現在地の取得
	Vec2 GetPos() const { return m_pos; }

	//プレイヤーの移動処理
	void MovePlayer(const InputState& input);

	//上に動けるかどうかの判定処理
	bool IsMoveUp()const;
	//下に動けるかどうかの判定処理
	bool IsMoveDown()const;
	//左に動けるかどうかの判定処理
	bool IsMoveLeft()const;
	//右に動けるかどうかの判定処理
	bool IsMoveRight()const;

	//描画処理
	void Draw()const;
};

