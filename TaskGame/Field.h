#pragma once
class Field
{
public:
	Field();
	~Field() {};

	//初期化
	void Init();
	//更新処理
	void Update();
	//描画処理
	void Draw();
private:
	int m_wide;		//仮追加
	int m_hight;	//仮追加
};

