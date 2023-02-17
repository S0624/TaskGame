#include<DXLib.h>
#include<assert.h>
#include"GameManager.h"

namespace my
{
	int MyLoadGraph(const TCHAR* path)
	{
		int handle = LoadGraph(path);
		assert(handle >= 0);
		return handle;
	}
	int MyDrawRectRotaGraph(int x, int y, int left, int top, int width, int height, float scale, float angle, int handle, bool transFlg)
	{
		return DrawRectRotaGraph(x, y,
			left, top,
			width, height,
			scale, angle,
			handle, transFlg);
	}

	void MyFontPath(const TCHAR* path)
	{
		LPCSTR font_path = path; // 読み込むフォントファイルのパス

		if (AddFontResourceEx(font_path, FR_PRIVATE, NULL) > 0) {
		}
		else {
			// フォント読込エラー処理
			MessageBox(NULL, "フォント読込失敗", "", MB_OK);
		}
		
	}



}