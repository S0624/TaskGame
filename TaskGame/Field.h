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
	int m_height;		//高さ
	int m_width;		//横幅
};

