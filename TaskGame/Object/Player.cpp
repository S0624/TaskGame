#include"DxLib.h"
#include "Player.h"
#include"Field.h"
#include"../Scene/SceneMain.h"
#include"../UI/InputState.h"
#include"../GameManager.h"

//プレイヤーの動きの処理
void Player::UpdatePlayer(const InputState& input)
{
	Vec2 vel = { 0,0 };
	//アニメーションのフラグ
	bool animetionFlag = false;

	//下を押された時の処理
	if (input.IsPressed(InputType::down))
	{
		animetionFlag = true;				//ボタンが押された時だけフラグを変える
		m_imgidx = 0;						//画像の場所の指定
		if (m_playerMoveNum == 0)
		{
			if (IsMoveDown())
			{
				m_playerMoveNum = 1;
				if (IsMoveNextPos(0, 1))
				{
					tempX = m_pos.x;
					tempY = m_pos.y;
					vel.y = +Field::kSize;		//下に動かす
					m_stepCount++;
				}
			}
		}
	}

	//上を押された時の処理
	else if (input.IsPressed(InputType::up))
	{
		animetionFlag = true;				//ボタンが押された時だけフラグを変える
		m_imgidx = 1;						//画像の場所の指定
		if (m_playerMoveNum == 0) 
		{
			if (IsMoveUp())
			{
				m_playerMoveNum = 2;
				if (IsMoveNextPos(0, -1))
				{
					tempX = m_pos.x;
					tempY = m_pos.y;
					vel.y = -Field::kSize;		//上に動かす
					m_stepCount++;
				}
			}
		}
	}
				
	//左を押された時の処理
	else if (input.IsPressed(InputType::left))
	{
		animetionFlag = true;				//ボタンが押された時だけフラグを変える
		m_imgidx = 2;						//画像の場所の指定
		if (m_playerMoveNum == 0)
		{
			if (IsMoveLeft())
			{
				m_playerMoveNum = 3;
				if (IsMoveNextPos(-1, 0))
				{
					tempX = m_pos.x;
					tempY = m_pos.y;
					vel.x = -Field::kSize;		//左に動かす
					m_stepCount++;
				}
			}
		}
	}

	//右を押された時の処理
	else if (input.IsPressed(InputType::right))
	{
		animetionFlag = true;				//ボタンが押された時だけフラグを変える
		m_imgidx = 3;						//画像の場所の指定
		if (m_playerMoveNum == 0)
		{
			if (IsMoveRight())
			{
				m_playerMoveNum = 4;
				if (IsMoveNextPos(1, 0))
				{
					tempX = m_pos.x;
					tempY = m_pos.y;
					vel.x = +Field::kSize;		//右に動く
					m_stepCount++;
				}
			}
		}
	}
	if(!animetionFlag)
	{
		if (input.IsTrigger(InputType::back))
		{
			//m_pos.x = tempX;
			//m_pos.y = tempY;
			//m_playerNextPos.x = tempX;
			//m_playerNextPos.y = tempY;
			//m_animeFlag = false;
		}
	}

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
		m_animetionFraem++;
		if (m_animetionFraem >= 60 * 2)
		{
			m_animetionFraem = 0;
		}

		if (m_animetionFraem / 60 == 1)
		{
			m_animationNumber = 1;
		}
		else
		{
			m_animationNumber = 0;
		}
	}
}

//プレイヤークラスのコンストラクタ
Player::Player() :
	m_pField(nullptr),
	m_pos(200, 300),
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
	m_handle = my::MyLoadGraph(L"../Date/Player.png");		//画像の読み込み
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
	m_pos.x = static_cast<float>(x) * Field::kSize;
	m_pos.y = static_cast<float>(y) * Field::kSize;
	
	//初期化
	m_playerNextPos = m_pos;
}

//プレイヤークラスの更新処理
void Player::Update(const InputState& input)
{
	//プレイヤーが動く処理
	MoveFrame();
	//ゲームクリアではなかったらキー入力を受け付ける
	if (!m_pField->GameClear() && m_stepCount < m_pField->StepLimit())
	//if (!m_pField->GameClear() || !m_pMain->GameOver())
	{
		UpdatePlayer(input);				//プレイヤーの移動処理を呼び出す
	}
}

//次に動く場所が動けるかをチェックする処理
bool Player::IsMoveNextPos(int x, int y) const
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

void Player::TitleUpdate()
{
	//下の移動
	m_animeFlag = true;				//フラグを変える
	if (m_playerMoveNum == 0)
	{
		m_pos.y += m_test;
		if (m_pos.y >= 500)
		{
			m_imgidx = 3;
			m_pos.y = m_posY;
			m_posY = 300;
			m_playerMoveNum = 1;
		}
	}
	if (m_playerMoveNum == 1)
	{
		m_pos.x += m_test;
		if (m_pos.x >= 800)
		{
			m_test *= -1;
			m_imgidx = 1;
			m_pos.x = m_posX;
			m_posX = 300;
			m_playerMoveNum = 2;
		}
	}
	if (m_playerMoveNum == 2)
	{
		m_pos.y += m_test;
		if (m_pos.y <= 300)
		{
			m_imgidx = 2;
			m_pos.y = m_posY;
			m_posY = 500;
			m_playerMoveNum = 3;
		}
	}
	if (m_playerMoveNum == 3)
	{
		m_pos.x += m_test;
		if (m_pos.x <= 300)
		{
			m_test *= -1;
			m_imgidx = 0;
			m_pos.x = m_posX;
			m_posX = 800;
			m_playerMoveNum = 0;
		}
	}
	//アニメーションを行う処理
	AnimetionPlayer(m_animeFlag);
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
	//DrawFormatString(0, 0, 0xffffff, L"X:%f,Y:%f", m_pos.x, m_pos.y);
	//DrawFormatString(0, 20, 0xffffff, L"NX:%f,NY:%f", m_playerNextPos.x, m_playerNextPos.y);
}