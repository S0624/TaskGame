#pragma once
#include<tchar.h>

//�����p���C�u�����p���O���
namespace my
{
	int MyLoadGraph(const TCHAR* path);

	int MyDrawRectRotaGraph(int x, int y, int left, int top,
		int width, int height, float scale, float angle, int handle, bool transFlag);
}
