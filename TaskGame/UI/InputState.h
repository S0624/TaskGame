#pragma once

#include<map>
#include<vector>
#include<string>

enum class InputType {
	next,	//���֍s���{�^��
	back,	//�O�ɖ߂�{�^��
	pause,	//�|�[�Y�{�^��
	up,			//��
	down,		//��
	right,		//�E
	left,		//��
	end,		//�I���
	change,		//�ύX
	max			//�ő���̓C���f�b�N�X
};

/// <summary>
/// ���͑��u�J�e�S��
/// </summary>
enum class InputCategory
{
	keybd,	//�L�[�{�[�h
	pad,	//�Q�[���p�b�h
};

struct InputInfo
{
	InputCategory cat;	//���͑��u�J�e�S��
	int id;	//����ID(KEY_INPUT�`	PAD�`_INPUT		MOUSE�`_INPUT)
};


class InputState
{
private:
	//���z���͏��Ǝ��ۂ̓��̓e�[�u�������
	//�L�[�ifirst�j = InputType
	//�l�isecond�j = std::vector<InputInfo>
	using InputMap_t = std::map<InputType, std::vector<InputInfo>>;		//���ۂ̓��͂ƑΉ��̃{�^��
	InputMap_t m_inputMapTable;		//���ۂ̓��͂ƑΉ��̃{�^��

	//���������悤�̈ꎞ�I��inputMapTable_�̃R�s�[
	//�����Ȃ菑�������Ă��܂�Ȃ��悤��
	InputMap_t m_tempMapTable;

	//���Z�b�g�p�̃}�b�v�e�[�u��
	InputMap_t m_defaultMapTable;

	//���̓^�C�v�Ƃ��̖��O
	std::map<InputType, std::wstring>m_inputNameTable;

	std::vector<bool> m_currentInput;		//���݂̓��͕��@(�����Ă��邩�����Ă��Ȃ���)
	std::vector<bool> m_lastInput;			//���O�̓��͏��(���O�����Ă��邩�����Ă��Ȃ���)

public:
	InputState();
	/// <summary>
	/// �������u�Ԃ�True�ɂȂ�
	/// </summary>
	/// <param name="type">InputType</param>
	/// <returns>�������u�ԂȂ�True�A����ȊO�Ȃ�False</returns>
	bool IsTrigger(InputType type)const;
	/// <summary>
	/// ������Ă���True�ɂȂ�
	/// </summary>
	/// <param name="type">InputType</param>
	/// <returns>������Ă���True�A����ȊO��Flase</returns>
	bool IsPressed(InputType type)const;
	/// <summary>
	/// ���͏�Ԃ��X�V
	/// �i���Ӂj���t���[��Update����΂Ȃ���΍X�V����Ȃ�
	/// </summary>
	void Update();

	/// <summary>
	/// ���͏����X�V
	/// </summary>
	/// <param name="type">�Q�[���ɂ�������͎��</param>
	/// <param name="cat">���̓J�e�S��</param>
	/// <param name="id">���ۂ̓���</param>
	void RewriteInpurInfo(InputType type, InputCategory cat, int id){};

	/// <summary>
	/// ���ݕҏW���̃L�[�R���t�B�O���m�肷��
	/// </summary>
	void CommitChangedInputInfo(){};

	/// <summary>
	/// ���ݕҏW���̃L�[�R���t�B�O�̕ύX���Ȃ��������Ƃɂ���
	/// </summary>
	void RollbackChangedInputInfo(){};
};

