#pragma once
#include"Vec2.h"
class Player
{
public:
	Player();
	~Player();

	//初期化
	void Init();
	//更新処理
	void Update();
	//プレイヤーの移動処理
	void MovePlayer();
	
	//描画処理
	void Draw();
private:
	//プレイヤーの位置
	Vec2 m_pos;
	//プレイヤーの画像
	int m_handle;
	//プレイヤーの画像の表示を変更する変数
	int m_imgidx;

	int m_repeatDown;

};

