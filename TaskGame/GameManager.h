#pragma once
#include<tchar.h>

//�����p���C�u�����p���O���
namespace my
{
	//�摜�̓ǂݍ���
	int MyLoadGraph(const TCHAR* path);

	//�摜�̕\��
	int MyDrawRectRotaGraph(int x, int y, int left, int top,
		int width, int height, float scale, float angle, int handle, bool transFlag);

	//�t�H���g�̓ǂݍ���
	void MyFontPath(const TCHAR* path);
}
