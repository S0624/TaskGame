#include "testField.h"

testField::testField()
{
	for (int x = 0; x < 20; x++)		//���ŕǂ̒ǉ�
	{
		for (int y = 0; y < 10; y++)		//���ŕǂ̒ǉ�
		{
			m_stage[y][x] = 0;
		}
	}
	//for (int x = 0; x < 20; x++)		//���ŕǂ̒ǉ�
	//{
	//	m_stage[0][x] = 1;
	//	m_stage[10 - 1][x] = 1;
	//}
	//for (int y = 0; y < 10; y++)		//���ŕǂ̒ǉ�
	//{
	//	m_stage[y][0] = 1;
	//	m_stage[y][6 - 1] = 1;
	//}
	//m_stage[4][4] = 2;	//���̒u���ꏊ
	//m_stage[1][3] = 2;	//���̒u���ꏊ
	//m_stage[1][4] = 2;	//���̒u���ꏊ


	//m_stage[3][3] = 3;	//���̒u���ꏊ
	//m_stage[4][3] = 3;	//���̒u���ꏊ
	//m_stage[5][4] = 3;	//���̒u���ꏊ
}
