#pragma once
#include<vector>

class Field;
class test2;

class testField
{	
private:
	Field* m_pField;
	test2* ktest;

public:
	testField();
	~testField(){};

	void SetField(Field* pField) { m_pField = pField; }
	int test(int test[10][20]);

	void Init();
	void FieldInit();
};