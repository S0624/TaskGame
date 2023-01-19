#include"DxLib.h"
#include "Field.h"
Field::Field() 
{

}
void Field::Init()
{


}

void Field::Update()
{

}

void Field::Draw()
{
	DrawBox(100, 50,
		450,  400, GetColor(255, 255, 255), false);
}