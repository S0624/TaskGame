#pragma once
#include<unordered_map>
//#include<string>
class SoundManager
{
private:
	int m_enterSE = 0;
	int m_moveSE = 0;
	int m_pauseOpenSE = 0;
	int m_pauseBackSE = 0;
	int m_clearSE = 0;
	int m_overSE = 0;
	int m_volumeSE = 180;
	int m_volumeBGM = 200;

	std::unordered_map<std::wstring, int>m_nameAndHandleTable;
	//�V���O���x�p�^�[���Ȃ̂ŃR���X�g���N�^��private�ɒu��
	int LoadSoundFile(const wchar_t* fileName);
	SoundManager();
	//�R�s�[��������֎~����
	SoundManager(const SoundManager&) = delete;	//�R�s�[�R���X�g���N�^
	void operator = (const SoundManager&) = delete;	//������֎~
public:
	~SoundManager();
	/// <summary>
	/// SoundManager�g�p�҂�GetInstance()��ʂ����Q�Ƃ��炵�����p�ł��Ȃ�
	/// </summary>
	/// <returns></returns>
	static SoundManager& GetInstance()
	{
		static SoundManager instance;	//�������B��̎���
		return instance;		//����̎Q�Ƃ�Ԃ�
	}

	/// <summary>
	/// �w��̃T�E���h��炷
	/// </summary>
	/// <param name="name"></param>
	void Play(const wchar_t* name);
	void PlayMusic(const wchar_t* path);

	void SetSEVolume(int volume);
	int GetSEVolume() const;

	void SetBGMVolume(int volume);
	int GetBGVolume() const;

	//�T�E���h���ꎞ��~����
	void StopBGMAndSE();
};

