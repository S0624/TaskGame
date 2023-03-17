#include<DXLib.h>
#include<assert.h>
#include"GameManager.h"

namespace my
{
	//�摜�̓ǂݍ���
	int MyLoadGraph(const TCHAR* path)
	{
		int handle = LoadGraph(path);
		//�ǂݍ��߂Ă��Ȃ������珈�����~�߂�
		assert(handle >= 0);
		return handle;
	}
	//�摜�̕\��
	int MyDrawRectRotaGraph(int x, int y, int left, int top, int width, int height, float scale, float angle, int handle, bool transFlg)
	{
		return DrawRectRotaGraph(x, y,
			left, top,
			width, height,
			scale, angle,
			handle, transFlg);
	}

	//�t�H���g�̓ǂݍ���
	void MyFontPath(const TCHAR* path)
	{
		LPCWSTR font_path = reinterpret_cast<LPCWSTR>(path); // �ǂݍ��ރt�H���g�t�@�C���̃p�X

		if (AddFontResourceEx(font_path, FR_PRIVATE, NULL) > 0) {
		}
	//�t�H���g�̓ǂݍ��݂����s������ǂݍ��ݎ��s���o��
		else {
			// �t�H���g�Ǎ��G���[����
			MessageBox(NULL, L"�t�H���g�Ǎ����s", L"", MB_OK);
		}

	}



}