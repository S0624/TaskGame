#pragma once
#pragma once
#include<vector>

class Field;
class Player;

class Stage1;
class Stage2;
class Stage3;
class Stage4;
class Stage5;

class FieldInformation
{
private:
	Field* m_pField;
	Player* m_pPlayer;
	Stage1* m_pStage1;
	Stage2* m_pStage2;
	Stage3* m_pStage3;
	Stage4* m_pStage4;
	Stage5* m_pStage5;

public:
	FieldInformation();
	~FieldInformation();

	//int Num(int num);
	void Num(int num);

	void SetField(Field* pField) { m_pField = pField; }
	void SetPlayer(Player* pPlayer) { m_pPlayer = pPlayer; }
	void FieldInfo(int field[10][20]);

	void PlayerInfo(int x, int y);

	void Init();
	void FieldInit();
};