#include"DxLib.h"
#include "Player.h"
#include"Field.h"
//#include"Box.h"
#include"../UI/Pad.h"
#include"../UI/InputState.h"

namespace
{
	//int kLRReoeatFrame = 8;
	// 左右キーのリピートフレーム
	constexpr int kMovementFrame = 10;
}

//プレイヤークラスのコンストラクタ
Player::Player() :
	m_pField(nullptr),
	m_pos(2,2),
	m_handlePos(25),
	m_handle(0),
	m_imgidx(0),
	m_moveDown(0),
	m_moveUp(0),
	m_moveLeft(0),
	m_moveRight(0),
	m_lastMove(0),
	m_animationNumber(0),
	m_animetionFraem(0),
	m_stepCount(0)

{

}

//プレイヤークラスのデストラクタ
Player::~Player()
{
	DeleteGraph(m_handle);		//画像のデリート
}

//プレイヤークラスの初期化
void Player::Init()
{
	m_handle = LoadGraph("../Date/Player.png");		//画像の読み込み
}

//プレイヤークラスの更新処理
void Player::Update(const InputState& input)
{
	if (!m_pField->GameClear())
	{
		MovePlayer(input);				//プレイヤーの移動処理を呼び出す
	}
}

//プレイヤーの動きの処理
void Player::MovePlayer(const InputState& input)
{
	bool animetionFlag = false;

	int pad = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	//かくかくにしたい移動
	//if (pad & PAD_INPUT_DOWN)
	//if(input.IsTrigger(InputType::down))
	if(input.IsPressed(InputType::down))
	{
		animetionFlag = true;
		m_imgidx = 0;						//画像の場所の指定
		++m_moveDown;
	}
	else
	{
		m_moveDown = 0;
	}
	
	bool isTriggerDown = (pad & PAD_INPUT_DOWN) && !(m_lastMove & PAD_INPUT_DOWN);
	bool isRepeatDown = false;
	if (m_moveDown >= kMovementFrame)		isRepeatDown = true;
	
	if (isTriggerDown || isRepeatDown)
	{
		m_moveDown = 0;
		if (IsMoveDown())
		{
			m_pos.y++;
			m_stepCount++;
		}
	}

	if(input.IsPressed(InputType::up))
	{
		animetionFlag = true;
		m_imgidx = 1;						//画像の場所の指定
		++m_moveUp;
	}
	else
	{
		m_moveUp = 0;
	}
	
	bool isTriggerUp = (pad & PAD_INPUT_UP) && !(m_lastMove & PAD_INPUT_UP);
	bool isRepeatUp = false;
	if (m_moveUp >= kMovementFrame)		isRepeatUp = true;
	
	if (isTriggerUp || isRepeatUp)
	{
		m_moveUp = 0;
		if (IsMoveUp())
		{
			m_pos.y--;
			m_stepCount++;
		}
	}

	if(input.IsPressed(InputType::left))
	{
		animetionFlag = true;
		m_imgidx = 2;						//画像の場所の指定
		++m_moveLeft;
	}
	else
	{
		m_moveLeft = 0;
	}
	
	bool isTriggerLeft = (pad & PAD_INPUT_LEFT) && !(m_lastMove & PAD_INPUT_LEFT);
	bool isRepeatLeft = false;
	if (m_moveLeft >= kMovementFrame)		isRepeatLeft = true;
	
	if (isTriggerLeft || isRepeatLeft)
	{
		m_moveLeft = 0;
		if (IsMoveLeft())
		{
			m_pos.x--;
			m_stepCount++;
		}
	}
	if(input.IsPressed(InputType::right))
	{
		animetionFlag = true;
		m_imgidx = 3;						//画像の場所の指定
		++m_moveRight;
	}
	else
	{
		m_moveRight = 0;
	}
	
	bool isTriggerRight = (pad & PAD_INPUT_RIGHT) && !(m_lastMove & PAD_INPUT_RIGHT);
	bool isRepeatRight = false;
	if (m_moveRight >= kMovementFrame)		isRepeatRight = true;
	
	if (isTriggerRight || isRepeatRight)
	{
		m_moveRight = 0;
		if (IsMoveRight())
		{
			m_pos.x++;
			m_stepCount++;
		}
	}
	m_lastMove = pad;
	

	//if (input.IsTrigger(InputType::up))	//上を押された時の処理
	//{
	//	if (IsMoveUp())
	//	{
	//		vec.y = -1.0f;
	//	}
	//	m_imgidx = 1;						//画像の場所の指定
	//}
	//
	//else if (input.IsTrigger(InputType::left))		//左を押された時の処理
	//{
	//	if (IsMoveLeft())
	//	{
	//		vec.x = -1.0f;
	//	}
	//	m_imgidx = 2;						//画像の場所の指定
	//}
	//else if (input.IsTrigger(InputType::right))	//右を押された時の処理
	//{
	//	if (IsMoveRight())
	//	{
	//		vec.x = +1.0f;
	//	}
	//	m_imgidx = 3;						//画像の場所の指定
	//}

	if (animetionFlag == true)
	{
		m_animetionFraem++;
		if (m_animetionFraem > 7)
		{
			m_animationNumber++;
			if (m_animationNumber > 3)
			{
				m_animationNumber = 0;
			}
			if (m_animationNumber == 1)
			{
				m_animationNumber = 2;
			}
			m_animetionFraem = 0;
		}
	}
}

//プレイヤーの上に行けるかの判定
bool Player::IsMoveUp()const
{
	int indexX = static_cast<int>(m_pos.x);
	int indexY = static_cast<int>(m_pos.y);
	int x = 0;
	int y = -1;
	// すでに一番下にある場合
	if (indexY >= (Field::kFieldY + 1)) return false;

	// 一つ下にブロックが置かれている場合
	if (m_pField->IsMovable(indexX, indexY + y, x, y)) return false;


	return true;
}

//プレイヤーの下に行けるかの判定
bool Player::IsMoveDown()const
{
	int indexX = static_cast<int>(m_pos.x);
	int indexY = static_cast<int>(m_pos.y);
	int x = 0;
	int y = 1;
	// すでに一番下にある場合
	if (indexY >= (Field::kFieldY - 1)) return false;

	// 一つ下にブロックが置かれている場合
	if (m_pField->IsMovable(indexX, indexY + y,x,y)) return false;

	return true;
}

//プレイヤーの左に行けるかの判定
bool Player::IsMoveLeft()const
{
	int indexX = static_cast<int>(m_pos.x);
	int indexY = static_cast<int>(m_pos.y);
	int x = -1;
	int y = 0;

	// すでに一番左にある場合
	if (indexX >= (Field::kFieldX + 1)) return false;

	// 一つ下にブロックが置かれている場合
	if (m_pField->IsMovable(indexX + x, indexY, x, y)) return false;

	return true;
}

//プレイヤーの右に行けるかの判定
bool Player::IsMoveRight()const
{
	int indexX = static_cast<int>(m_pos.x);
	int indexY = static_cast<int>(m_pos.y);
	int x = 1;
	int y = 0;
	// すでに一番右にある場合
	if (indexX >= (Field::kFieldX - 1)) return false;

	// 一つ右にブロックが置かれている場合
	if (m_pField->IsMovable(indexX + x, indexY, x, y)) return false;

	return true;
}

//プレイヤークラスの描画処理
void Player::Draw()const
{
	//m_pField->Draw();		//フィールドクラスの描画処理
	int posX = Field::kSize * static_cast<int>(m_pos.x);
	int posY = Field::kSize * static_cast<int>(m_pos.y);

	//DrawBox(posX + Field::kWidth, posY + Field::kHeight,			//表示座標
	//	(posX + Field::kSize) + Field::kWidth, (posY + Field::kSize) + Field::kHeight,
	//	GetColor(255,0,255),true);


	DrawRectRotaGraph(posX + Field::kWidth + m_handlePos,
		posY + Field::kHeight + m_handlePos,			//表示座標
		48 * m_animationNumber, 48 * m_imgidx,			//切り取り左上
		48, 48,							//幅、高さ
		2.5f, 0.0f,						//拡大率、回転角度
		m_handle, true);

	//DrawFormatString(200, 0, 0xffff00, "%d", m_animationNumber);
	//DrawFormatString(200, 20, 0xffff00, "%d", m_animetionFraem);
	//DrawFormatString(200, 40, 0x00ff0f, "%d", m_stepCount);
}