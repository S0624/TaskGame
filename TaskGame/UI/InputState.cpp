#include "InputState.h"
#include<DxLib.h>
#include<cassert>

InputState::InputState()
{
	//次へ
	m_defaultMapTable[InputType::next] = { {InputCategory::keybd,KEY_INPUT_RETURN},
										{InputCategory::pad,PAD_INPUT_1} };		//スタートボタン

	//ポーズ
	m_defaultMapTable[InputType::pause] = { {InputCategory::keybd,KEY_INPUT_P},
									{InputCategory::pad,PAD_INPUT_8} };			//セレクト

	////キーコンフィグ
	//defaultMapTable_[InputType::keyconf] = { {InputCategory::keybd,KEY_INPUT_K},
	//								{InputCategory::pad,PAD_INPUT_Y} };			//左ショルダー
	//								//{InputCategory::pad,PAD_INPUT_4} };			//左ショルダー

	////変更
	//defaultMapTable_[InputType::change] = { {InputCategory::keybd,KEY_INPUT_C},
	//								{InputCategory::pad,PAD_INPUT_Z} };			//右ショルダー
	//							//{InputCategory::pad,PAD_INPUT_4} };			//右ショルダー

	//上
	m_defaultMapTable[InputType::up] = { {InputCategory::keybd,KEY_INPUT_UP},
									{InputCategory::pad,PAD_INPUT_UP} };			//上ショルダー

	//下
	m_defaultMapTable[InputType::down] = { {InputCategory::keybd,KEY_INPUT_DOWN},
									{InputCategory::pad,PAD_INPUT_DOWN} };			//下ショルダー
	//左
	m_defaultMapTable[InputType::left] = { {InputCategory::keybd,KEY_INPUT_LEFT},
									{InputCategory::pad,PAD_INPUT_LEFT} };			//下ショルダー

	//右
	m_defaultMapTable[InputType::right] = { {InputCategory::keybd,KEY_INPUT_RIGHT},
									{InputCategory::pad,PAD_INPUT_RIGHT} };			//上ショルダー


	m_inputMapTable = m_defaultMapTable;
	//LoadKeyInfo();

	//位置にマップテーブルにコピー
	m_tempMapTable = m_inputMapTable;

	//入力タイプの名前のテーブルを作る
	m_inputNameTable[InputType::next] = L"next";
	m_inputNameTable[InputType::pause] = L"pause";

	m_currentInput.resize(static_cast<int>(InputType::max));
	m_lastInput.resize(static_cast<int>(InputType::max));
}

bool InputState::IsTrigger(InputType type) const
{
	return IsPressed(type) && !m_lastInput[static_cast<int>(type)];
}

bool InputState::IsPressed(InputType type) const
{
	return m_currentInput[static_cast<int>(type)];
}

void InputState::Update()
{
	m_lastInput = m_currentInput;		//直前の入力情報を記憶しておく
	char keystate[256];				//全キー情報取得
	GetHitKeyStateAll(keystate);

	int padstate = GetJoypadInputState(DX_INPUT_PAD1);		//パッド1紺の情報を所得する
	int mousestate = GetMouseInput();						//マウスの情報

	for (const auto& keymap : m_inputMapTable)		//マップの全情報をループする
	{
		for (const auto& input : keymap.second)		//入力情報配列をループする
		{
			//このInputの中身は、keybd,KEY_INPUT_RETURNなどのセット（Inputinfo）が入っている
			//keymap.firstには、対応するゲーム入力名の"InputType::next"などが入っている
			if (input.cat == InputCategory::keybd)
			{
				m_currentInput[static_cast<int>(keymap.first)] = keystate[input.id];
			}

			else if (input.cat == InputCategory::pad)
			{
				m_currentInput[static_cast<int>(keymap.first)] = padstate & input.id;
			}

			//2つの入力のうちどちらかがtrueだったらもう「入力されている」
			//とみなして、breakする。
			if (m_currentInput[static_cast<int>(keymap.first)])			//上書きされないようにbreakでループを抜ける
			{
				break;
			}
		}
	}
}

