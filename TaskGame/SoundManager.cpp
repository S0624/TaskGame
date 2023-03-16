#include "SoundManager.h"
#include"DxLib.h"

int SoundManager::LoadSoundFile(const wchar_t* fileName)
{
	std::wstring path = L"../Sound/SE/";
	path += fileName;
	path += L".mp3";
	int handle = LoadSoundMem(path.c_str());
	m_nameAndHandleTable[fileName] = handle;
	return handle;
}

SoundManager::SoundManager()
{
	m_enterSE = LoadSoundFile(L"SE1");
	m_moveSE = LoadSoundFile(L"SE2");
	m_pauseOpenSE = LoadSoundFile(L"Pause1");
	m_pauseBackSE = LoadSoundFile(L"Pause2");
	m_clearSE = LoadSoundFile(L"GameClear");
	m_overSE = LoadSoundFile(L"GameOver");
	m_overSE = LoadSoundFile(L"fireflower");
	SetSEVolume(m_volumeSE);
	SetBGMVolume(m_volumeBGM);
}
SoundManager::~SoundManager()
{
	DeleteSoundMem(m_enterSE);
	DeleteSoundMem(m_moveSE);
	DeleteSoundMem(m_pauseOpenSE);
	DeleteSoundMem(m_pauseBackSE);
	DeleteSoundMem(m_clearSE);
	DeleteSoundMem(m_overSE);
	DeleteSoundMem(m_fireSE);
}

void SoundManager::Play(const wchar_t* name)
{
	//if (CheckSoundMem(m_nameAndHandleTable[name]) == 0)
	//{
		PlaySoundMem(m_nameAndHandleTable[name], DX_PLAYTYPE_BACK);
	//}
}

void SoundManager::PlayMusic(const wchar_t* path)
{
	DxLib::PlayMusic(path, DX_PLAYTYPE_LOOP);
	SetVolumeMusic(m_volumeBGM);
}

void SoundManager::SetSEVolume(int volume)
{
	for (auto& record : m_nameAndHandleTable) {
		ChangeVolumeSoundMem(volume, record.second);
	}
	m_volumeSE = volume;
}

int SoundManager::GetSEVolume() const
{
	return m_volumeSE;
}

void SoundManager::SetBGMVolume(int volume)
{
	SetVolumeMusic(volume);
	m_volumeBGM = volume;
}

int SoundManager::GetBGVolume() const
{
	return m_volumeBGM;
}

void SoundManager::StopBGMAndSE()
{
	StopSoundMem(m_overSE);
	StopSoundMem(m_clearSE);
	StopSoundMem(m_fireSE);
}
