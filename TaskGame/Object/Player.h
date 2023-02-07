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

	//プレイヤーの位置
	Vec2 m_pos;
	//プレイヤーの画像をずらす
	int m_handlePos;
	//プレイヤーの画像
	int m_handle;
	//プレイヤーの画像の表示を変更する変数
	int m_imgidx;

	//キーボードを押された時に移動に制限をかける
	int m_moveDown;			//下
	int m_moveUp;			//上
	int m_moveLeft;			//左
	int m_moveRight;		//右
	int m_lastMove;			//最後に押されたキーを覚えておく

	int m_animationNumber;		//アニメーションの番号
	int m_animetionFraem;		//アニメーションを変えるインターバル

	//歩いた歩数（お試し）
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

