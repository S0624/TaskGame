#include"DxLib.h"
#include "Player.h"
#include"Field.h"
#include"../Scene/SceneMain.h"
#include"../UI/Pad.h"
#include"../UI/InputState.h"
#include"../DrawFunc.h"

namespace
{
	// 左右キーのリピートフレーム
	constexpr int kMovementFrame = 10;
}

//プレイヤークラスのコンストラクタ
Player::Player() :
	m_pField(nullptr),
	m_pos(0, 0),
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
	m_stepCount(0),
	m_playerMoveSpeed(0),
	m_playerNextPos(0, 0),
	m_animeFlag(0),
	m_playerMoveNum(0)

{
	m_handle = my::MyLoadGraph("../Date/Player.png");		//画像の読み込み

}

//プレイヤークラスのデストラクタ
Player::~Player()
{
	DeleteGraph(m_handle);		//画像のデリート
}

//初期位置を受け取る
void Player::PosInit(int x, int y)
{
	//位置にサイズをかける
	m_pos.x = x * Field::kSize;
	m_pos.y = y * Field::kSize;

	//初期化
	m_playerNextPos = m_pos;
}


//プレイヤークラスの更新処理
void Player::Update(const InputState& input)
{
	//プレイヤーが動く処理
	MoveFrame();
	//ゲームクリアではなかったらキー入力を受け付ける
	if (!m_pField->GameClear())
	{
		UpdatePlayer(input);				//プレイヤーの移動処理を呼び出す
	}
}


//プレイヤーの動きの処理
void Player::UpdatePlayer(const InputState& input)
{
	Vec2 vel = { 0,0 };
	//アニメーションのフラグ
	bool animetionFlag = false;

	//かくかくする移動にするために使用
	int pad = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	//if (pad & PAD_INPUT_DOWN)
	//if(input.IsTrigger(InputType::down))

	//下を押された時の処理
	//if(input.IsTrigger(InputType::down))
	if (m_playerMoveNum == 0 || m_playerMoveNum == 1)
	{
		if (input.IsPressed(InputType::down))
		{
			animetionFlag = true;				//ボタンが押された時だけフラグを変える
			m_imgidx = 0;						//画像の場所の指定
			++m_moveDown;
		}
		else
		{
			m_moveDown = 0;						//押されなかったら０に戻す
		}
		bool isTriggerDown = (pad & PAD_INPUT_DOWN) && !(m_lastMove & PAD_INPUT_DOWN);
		bool isRepeatDown = false;
		if (m_moveDown >= kMovementFrame)		isRepeatDown = true;
		if (isTriggerDown || isRepeatDown)
		{
			m_moveDown = 0;
			if (IsMoveDown())
			{
				m_playerMoveNum = 1;
				if (IsMovePos(0, 1))
				{
					vel.y = +Field::kSize;		//下に動かす
				}
				m_stepCount++;
			}
		}
	}
	if (m_playerMoveNum == 0 || m_playerMoveNum == 2)
	{
		//上を押された時の処理
		if (input.IsPressed(InputType::up))
		{
			animetionFlag = true;				//ボタンが押された時だけフラグを変える
			m_imgidx = 1;						//画像の場所の指定
			++m_moveUp;
		}
		else
		{
			m_moveUp = 0;						//押されなかったら０に戻す
		}
		bool isTriggerUp = (pad & PAD_INPUT_UP) && !(m_lastMove & PAD_INPUT_UP);
		bool isRepeatUp = false;
		if (m_moveUp >= kMovementFrame)		isRepeatUp = true;
		if (isTriggerUp || isRepeatUp)
		{
			m_moveUp = 0;
			if (IsMoveUp())
			{
				m_playerMoveNum = 2;
				if (IsMovePos(0, -1))
				{
					vel.y = -Field::kSize;		//上に動かす
				}
				m_stepCount++;
			}
		}
	}

	if (m_playerMoveNum == 0 || m_playerMoveNum == 3)
	{
		//左を押された時の処理
		if (input.IsPressed(InputType::left))
		{
			animetionFlag = true;				//ボタンが押された時だけフラグを変える
			m_imgidx = 2;						//画像の場所の指定
			++m_moveLeft;
		}
		else
		{
			m_moveLeft = 0;						//押されなかったら０に戻す
		}
		bool isTriggerLeft = (pad & PAD_INPUT_LEFT) && !(m_lastMove & PAD_INPUT_LEFT);
		bool isRepeatLeft = false;
		if (m_moveLeft >= kMovementFrame)		isRepeatLeft = true;
		if (isTriggerLeft || isRepeatLeft)
		{
			m_moveLeft = 0;
			if (IsMoveLeft())
			{
				m_playerMoveNum = 3;
				if (IsMovePos(-1, 0))
				{
					vel.x = -Field::kSize;		//左に動かす
				}
				m_stepCount++;
			}
		}
	}
	if (m_playerMoveNum == 0 || m_playerMoveNum == 4)
	{
		//右を押された時の処理
		if (input.IsPressed(InputType::right))
		{
			animetionFlag = true;				//ボタンが押された時だけフラグを変える
			m_imgidx = 3;						//画像の場所の指定
			++m_moveRight;
		}
		else
		{
			m_moveRight = 0;					//押されなかったら０に戻す
		}
		bool isTriggerRight = (pad & PAD_INPUT_RIGHT) && !(m_lastMove & PAD_INPUT_RIGHT);
		bool isRepeatRight = false;
		if (m_moveRight >= kMovementFrame)		isRepeatRight = true;
		if (isTriggerRight || isRepeatRight)
		{
			m_moveRight = 0;
			if (IsMoveRight())
			{
				m_playerMoveNum = 4;
				if (IsMovePos(1, 0))
				{
					vel.x = +Field::kSize;		//右に動く
				}
				m_stepCount++;
			}
		}
	}

	//最後に押されたキーを覚えておく
	m_lastMove = pad;

	//アニメーションを行う処理
	AnimetionPlayer(m_animeFlag);

	//動いた数を渡す
	MoveFrame(vel);

}

//プレイヤーが動くために必要な情報を持つ関数
void Player::MoveFrame(Vec2 vel)
{
	//移動スピードの設定
	m_playerMoveSpeed = 3.0;
	//次の場所に移動する分の数値を入れる
	m_playerNextPos += vel;

}

//プレイヤーが動く処理
void Player::MoveFrame()
{
	if (m_playerMoveNum == 1)
	{
		// 毎フレーム緩やかに目標に近づく
		if (m_pos.y != m_playerNextPos.y)
		{
			m_animeFlag = true;
			m_pos.y += m_playerMoveSpeed;
			// 目標に合致したら止める
			if (m_pos.y >= m_playerNextPos.y)
			{
				m_pos.y = m_playerNextPos.y;
				m_animeFlag = false;
				m_playerMoveNum = 0;
			}
		}
	}
	if (m_playerMoveNum == 2)
	{
		// 毎フレーム緩やかに目標に近づく
		if (m_pos.y != m_playerNextPos.y)
		{
			m_animeFlag = true;
			m_pos.y -= m_playerMoveSpeed;
			// 目標に合致したら止める
			if (m_pos.y <= m_playerNextPos.y)
			{
				m_pos.y = m_playerNextPos.y;
				m_animeFlag = false;
				m_playerMoveNum = 0;
			}
		}
	}

	// 毎フレーム緩やかに目標に近づく
	if (m_playerMoveNum == 3)
	{
		if (m_pos.x != m_playerNextPos.x)
		{
			m_animeFlag = true;
			m_pos.x -= m_playerMoveSpeed;
			// 目標に合致したら止める
			if (m_pos.x <= m_playerNextPos.x)
			{
				m_pos.x = m_playerNextPos.x;
				m_animeFlag = false;
				m_playerMoveNum = 0;
			}
		}
	}
	if (m_playerMoveNum == 4)
	{
		if (m_pos.x != m_playerNextPos.x)
		{
			m_animeFlag = true;
			m_pos.x += m_playerMoveSpeed;
			// 目標に合致したら止める
			if (m_pos.x >= m_playerNextPos.x)
			{
				m_pos.x = m_playerNextPos.x;
				m_animeFlag = false;
				m_playerMoveNum = 0;
			}
		}
	}
}

//次に動く場所が動けるかをチェックする処理
bool Player::IsMovePos(int x, int y) const
{
	int indexPosX = static_cast<int>(m_playerNextPos.x) / Field::kSize;
	int indexPosY = static_cast<int>(m_playerNextPos.y) / Field::kSize;
	int posX = 0;
	int posY = 0;
	posX = x;
	posY = y;
	// すでに一番下にある場合
	if (indexPosX <= 0) return false;
	if (indexPosY <= 0) return false;
	if (indexPosX >= (Field::kFieldX - 1)) return false;
	if (indexPosY >= (Field::kFieldY - 1)) return false;

	// 一つ下にブロックが置かれている場合
	if (m_pField->IsMovablePos(indexPosX + posX, indexPosY + posY)) return false;

	return true;
}

//プレイヤーの下に行けるかの判定
bool Player::IsMoveDown()const
{
	int indexX = static_cast<int>(m_pos.x) / Field::kSize;
	int indexY = static_cast<int>(m_pos.y) / Field::kSize;
	int x = 0;
	int y = 1;
	// すでに一番下にある場合
	if (indexY >= (Field::kFieldY - 1)) return false;

	// 一つ下にブロックが置かれている場合
	if (m_pField->IsMovable(indexX, indexY + y, x, y)) return false;

	return true;
}

//プレイヤーの上に行けるかの判定
bool Player::IsMoveUp()const
{
	int indexX = static_cast<int>(m_pos.x) / Field::kSize;
	int indexY = static_cast<int>(m_pos.y) / Field::kSize;
	int x = 0;
	int y = -1;
	// すでに一番上にある場合
	if (indexY <= 0) return false;

	// 一つ下にブロックが置かれている場合
	if (m_pField->IsMovable(indexX, indexY + y, x, y)) return false;

	return true;
}

//プレイヤーの左に行けるかの判定
bool Player::IsMoveLeft()const
{
	int indexX = static_cast<int>(m_pos.x) / Field::kSize;
	int indexY = static_cast<int>(m_pos.y) / Field::kSize;
	int x = -1;
	int y = 0;

	// すでに一番左にある場合
	if (indexX <= 0) return false;

	// 一つ下にブロックが置かれている場合
	if (m_pField->IsMovable(indexX + x, indexY, x, y)) return false;

	return true;
}

//プレイヤーの右に行けるかの判定
bool Player::IsMoveRight()const
{
	int indexX = static_cast<int>(m_pos.x) / Field::kSize;
	int indexY = static_cast<int>(m_pos.y) / Field::kSize;
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
	int posX = static_cast<int>(m_pos.x);
	int posY = static_cast<int>(m_pos.y);

	my::MyDrawRectRotaGraph(posX + Field::kWidth + m_handlePos,
		posY + Field::kHeight + m_handlePos,			//表示座標
		48 * m_animationNumber, 48 * m_imgidx,			//切り取り左上
		48, 48,							//幅、高さ
		2.5f, 0.0f,						//拡大率、回転角度
		m_handle, true);
}

//アニメーションを行う処理
const void Player::AnimetionPlayer(bool anime)
{
	//動いている間だけアニメーションを行う
	if (m_animeFlag == true)
	{
		//アニメーションのインターバル
		m_animetionFraem++;
		if (m_animetionFraem > 7)
		{
			//アニメーションを変える
			m_animationNumber++;
			//設定値より大きくなったら一番最初のコマに戻す
			if (m_animationNumber > 3)
			{
				m_animationNumber = 0;
			}
			//特定のコマを飛ばす
			if (m_animationNumber == 1)
			{
				m_animationNumber = 2;
			}
			//インターバルを元に戻す
			m_animetionFraem = 0;
		}
	}
	//動いていなかったら止まっている（立っている）画像に戻す
	else
	{
		m_animationNumber = 0;
	}
}
