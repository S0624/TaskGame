#pragma once

//	プロトタイプ宣言
class SceneManager;

class SceneBase
{
protected:
	SceneManager& manager_;		//シーンマネージャへの参照
public:
	SceneBase(SceneManager& manager) : manager_(manager) {}
	virtual ~SceneBase() {};
	//シーンを更新する
	//virtual void Update(const InputState& input) = 0;
	//シーンを描画する
	virtual void Draw() = 0;

private:
};

