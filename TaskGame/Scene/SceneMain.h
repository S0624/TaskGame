#pragma once

//　プロトタイプ宣言
class Player;
class Field;
//class Box;

class SceneMain
{
public:
	SceneMain();
	~SceneMain();

	//初期化
	void Init()const;
	//更新処理
	void Update()const;
	//描画処理
	void Draw()const;

private:
	Player* m_pPlayer;		//Playerクラスをポインタで宣言
	Field* m_pField;		//Fieldクラスをポインタで宣言
	//Box* m_pBox;		//Fieldクラスをポインタで宣言
};

