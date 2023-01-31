#include"DxLib.h"
#include "Player.h"
#include"Field.h"
//#include"Box.h"
#include"../UI/Pad.h"
#include"../UI/InputState.h"

namespace
{
	//int kLRReoeatFrame = 8;
}

//プレイヤークラスのコンストラクタ
Player::Player() :
	m_pField(nullptr),
	m_pos(2,2),
	m_handlePos(25),
	m_handle(0),
	m_imgidx(0)
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
	//constexpr float speed = 2.0f;		//プレイヤーの移動速度

	Vec2 vec = { 0.0f,0.0f };	//速度ベクトル

	Pad::update();

	//かくかくにしたい移動
	if(input.IsTrigger(InputType::down))
	{
		if (IsMoveDown())
		{
			vec.y = +1.0f;
		}
		m_imgidx = 0;						//画像の場所の指定
	}
	else if (input.IsTrigger(InputType::up))	//上を押された時の処理
	{
		if (IsMoveUp())
		{
			vec.y = -1.0f;
		}
		m_imgidx = 1;						//画像の場所の指定
	}
	else if (input.IsTrigger(InputType::left))		//左を押された時の処理
	{
		if (IsMoveLeft())
		{
			vec.x = -1.0f;
		}
		m_imgidx = 2;						//画像の場所の指定
	}
	else if (input.IsTrigger(InputType::right))	//右を押された時の処理
	{
		if (IsMoveRight())
		{
			vec.x = +1.0f;
		}
		m_imgidx = 3;						//画像の場所の指定
	}

	//if (vec.length() > 0.0f)
	//{
	//	vec.normalize();		//方向にかかわらず大きさを一にする
	//	vec *= speed;			//1の方向にスピードを乗算する
	//}
	m_pos += vec;
}

//プレイヤーの上に行けるかの判定
bool Player::IsMoveUp()const
{
	int indexX = m_pos.x;
	int indexY = m_pos.y;
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
	int indexX = m_pos.x;
	int indexY = m_pos.y;
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
	int indexX = m_pos.x;
	int indexY = m_pos.y;
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
	int indexX = m_pos.x;
	int indexY = m_pos.y;
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
	int posX = Field::kSize * m_pos.x;
	int posY = Field::kSize * m_pos.y;

	//DrawBox(posX + Field::kWidth, posY + Field::kHeight,			//表示座標
	//	(posX + Field::kSize) + Field::kWidth, (posY + Field::kSize) + Field::kHeight,
	//	GetColor(255,0,255),true);


	DrawRectRotaGraph(posX + Field::kWidth + m_handlePos,
		posY + Field::kHeight + m_handlePos,			//表示座標
		48 * 0, 48 * m_imgidx,							//切り取り左上
		48, 48,							//幅、高さ
		2.5f, 0.0f,						//拡大率、回転角度
		m_handle, true);

}