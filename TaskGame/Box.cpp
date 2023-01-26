//#include "Box.h"
//#include"DxLib.h"
//#include "Player.h"
//#include"Field.h"
//#include"Pad.h"
//
//namespace
//{
//	bool kIsflag = false;
//	bool kTouchflag = false;
//	int kIscolor = 0;
//}
//
//Box::Box() :
//	m_pField(nullptr),
//	m_pPlayer(nullptr),
//	m_pos(3,3)
//{
//
//}
//Box::~Box()
//{
//	//DeleteGraph(m_handle);		//�摜�̃f���[�g
//}
//void Box::Init()
//{
//
//}
//
//void Box::Update()
//{
//	MoveBox();				//�v���C���[�̈ړ��������Ăяo��
//}
//
//void Box::MoveBox()
//{
//	Vec2 vec = { 0.0f,0.0f };	//���x�x�N�g��
//	
//	if (!IsPut())
//	{
//		kIsflag = true;
//	}
//	else
//	{
//		kIsflag = false;
//	}
//
//	if (kTouchflag)
//	{
//		if (Pad::isTrigger(PAD_INPUT_DOWN))		//���������ꂽ���̏���
//		{
//			if (IsMoveDown())
//			{
//				vec.y = +1.0f;
//			}
//		}
//		else if (Pad::isTrigger(PAD_INPUT_UP))	//��������ꂽ���̏���
//		{
//			if (IsMoveUp())
//			{
//				vec.y = -1.0f;
//			}
//		}
//		else if (Pad::isTrigger(PAD_INPUT_LEFT))		//���������ꂽ���̏���
//		{
//			if (IsMoveLeft())
//			{
//				vec.x = -1.0f;
//			}
//		}
//		else if (Pad::isTrigger(PAD_INPUT_RIGHT))	//�E�������ꂽ���̏���
//		{
//			if (IsMoveRight())
//			{
//				vec.x = +1.0f;
//			}
//		}
//	}
//
//	m_pos += vec;
//}
//
//bool Box::IsTouch(int x,int y)
//{
//	int indexX = m_pos.x;
//	int indexY = m_pos.y;
//	if (indexX == x && indexY == y)
//	{
//		kTouchflag = true;
//		return true;
//	}
//	kTouchflag = false;
//	return false;
//}
//
//bool Box::IsMoveUp()
//{
//	//int indexX = m_pos.x;
//	//int indexY = m_pos.y;
//	//
//	//// ���łɈ�ԉ��ɂ���ꍇ
//	//if (indexY >= (Field::kFieldY + 1)) return false;
//
//	//// ����Ƀu���b�N���u����Ă���ꍇ
//	//if (m_pField->IsMovable(indexX, indexY - 1)) return false;
//
//	return true;
//}
//
//bool Box::IsMoveDown()
//{
//	//int indexX = m_pos.x;
//	//int indexY = m_pos.y;
//	//// ���łɈ�ԉ��ɂ���ꍇ
//	//if (indexY >= (Field::kFieldY - 1)) return false;
//
//	//// ����Ƀu���b�N���u����Ă���ꍇ
//	//if (m_pField->IsMovable(indexX, indexY + 1)) return false;
//
//	return true;
//}
//
//bool Box::IsMoveLeft()
//{
//	//int indexX = m_pos.x;
//	//int indexY = m_pos.y;
//	//// ���łɈ�ԍ��ɂ���ꍇ
//	//if (indexX >= (Field::kFieldX + 1)) return false;
//
//	//// ����Ƀu���b�N���u����Ă���ꍇ
//	//if (m_pField->IsMovable(indexX - 1, indexY)) return false;
//
//	return true;
//}
//
//bool Box::IsMoveRight()
//{
//	//int indexX = m_pos.x;
//	//int indexY = m_pos.y;
//	//// ���łɈ�ԉE�ɂ���ꍇ
//	//if (indexX >= (Field::kFieldX - 1)) return false;
//
//	//// ��E�Ƀu���b�N���u����Ă���ꍇ
//	//if (m_pField->IsMovable(indexX + 1, indexY)) return false;
//
//	return true;
//}
//
//bool Box::IsPut()
//{
//	int indexX = m_pos.x;
//	int indexY = m_pos.y;
//
//	// �����u���Ă���ꍇ
//	if (m_pField->IsPlaced(indexX, indexY)) return false;
//
//	return true;
//}
//
//void Box::Draw()
//{
//	int posX = Field::kSize * m_pos.x;
//	int posY = Field::kSize * m_pos.y;
//
//	DrawBox(posX + Field::kWidth + 5, posY + Field::kHeight + 5,			//�\�����W
//		(posX + Field::kSize) + Field::kWidth - 5, (posY + Field::kSize) + Field::kHeight - 5,
//		GetColor(kIscolor, 255, 0), kIsflag);
//
//	DrawFormatString(0, 100, GetColor(255, 0, 0), "%f", m_pPlayer->GetPos().x);
//	DrawFormatString(0, 120, GetColor(255, 0, 0), "%f", m_pPlayer->GetPos().y);
//}