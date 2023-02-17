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
		LPCSTR font_path = path; // �ǂݍ��ރt�H���g�t�@�C���̃p�X

		if (AddFontResourceEx(font_path, FR_PRIVATE, NULL) > 0) {
		}
		else {
			// �t�H���g�Ǎ��G���[����
			MessageBox(NULL, "�t�H���g�Ǎ����s", "", MB_OK);
		}
		
	}



}