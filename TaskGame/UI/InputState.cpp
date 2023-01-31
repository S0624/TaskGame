#include "InputState.h"
#include<DxLib.h>
#include<cassert>

InputState::InputState()
{
	//����
	m_defaultMapTable[InputType::next] = { {InputCategory::keybd,KEY_INPUT_RETURN},
										{InputCategory::pad,PAD_INPUT_1} };		//�X�^�[�g�{�^��

	//�|�[�Y
	m_defaultMapTable[InputType::pause] = { {InputCategory::keybd,KEY_INPUT_P},
									{InputCategory::pad,PAD_INPUT_8} };			//�Z���N�g

	////�L�[�R���t�B�O
	//defaultMapTable_[InputType::keyconf] = { {InputCategory::keybd,KEY_INPUT_K},
	//								{InputCategory::pad,PAD_INPUT_Y} };			//���V�����_�[
	//								//{InputCategory::pad,PAD_INPUT_4} };			//���V�����_�[

	////�ύX
	//defaultMapTable_[InputType::change] = { {InputCategory::keybd,KEY_INPUT_C},
	//								{InputCategory::pad,PAD_INPUT_Z} };			//�E�V�����_�[
	//							//{InputCategory::pad,PAD_INPUT_4} };			//�E�V�����_�[

	//��
	m_defaultMapTable[InputType::up] = { {InputCategory::keybd,KEY_INPUT_UP},
									{InputCategory::pad,PAD_INPUT_UP} };			//��V�����_�[

	//��
	m_defaultMapTable[InputType::down] = { {InputCategory::keybd,KEY_INPUT_DOWN},
									{InputCategory::pad,PAD_INPUT_DOWN} };			//���V�����_�[
	//��
	m_defaultMapTable[InputType::left] = { {InputCategory::keybd,KEY_INPUT_LEFT},
									{InputCategory::pad,PAD_INPUT_LEFT} };			//���V�����_�[

	//�E
	m_defaultMapTable[InputType::right] = { {InputCategory::keybd,KEY_INPUT_RIGHT},
									{InputCategory::pad,PAD_INPUT_RIGHT} };			//��V�����_�[


	m_inputMapTable = m_defaultMapTable;
	//LoadKeyInfo();

	//�ʒu�Ƀ}�b�v�e�[�u���ɃR�s�[
	m_tempMapTable = m_inputMapTable;

	//���̓^�C�v�̖��O�̃e�[�u�������
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
	m_lastInput = m_currentInput;		//���O�̓��͏����L�����Ă���
	char keystate[256];				//�S�L�[���擾
	GetHitKeyStateAll(keystate);

	int padstate = GetJoypadInputState(DX_INPUT_PAD1);		//�p�b�h1���̏�����������
	int mousestate = GetMouseInput();						//�}�E�X�̏��

	for (const auto& keymap : m_inputMapTable)		//�}�b�v�̑S�������[�v����
	{
		for (const auto& input : keymap.second)		//���͏��z������[�v����
		{
			//����Input�̒��g�́Akeybd,KEY_INPUT_RETURN�Ȃǂ̃Z�b�g�iInputinfo�j�������Ă���
			//keymap.first�ɂ́A�Ή�����Q�[�����͖���"InputType::next"�Ȃǂ������Ă���
			if (input.cat == InputCategory::keybd)
			{
				m_currentInput[static_cast<int>(keymap.first)] = keystate[input.id];
			}

			else if (input.cat == InputCategory::pad)
			{
				m_currentInput[static_cast<int>(keymap.first)] = padstate & input.id;
			}

			//2�̓��͂̂����ǂ��炩��true������������u���͂���Ă���v
			//�Ƃ݂Ȃ��āAbreak����B
			if (m_currentInput[static_cast<int>(keymap.first)])			//�㏑������Ȃ��悤��break�Ń��[�v�𔲂���
			{
				break;
			}
		}
	}
}

