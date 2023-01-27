#pragma once

#include<deque>

//　プロトタイプ宣言
class SceneBase;

class SceneManager
{
public:
	//シーンの切り替えを行う処理
	void ChangeScene();
	//シーン

private:
	std::deque<SceneBase*> m_scene;
};

