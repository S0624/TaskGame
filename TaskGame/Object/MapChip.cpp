#include "MapChip.h"
#include"DxLib.h"
#include<string>
#include<cassert>

void MapChip::TransposeMapData(int layerId)
{
	auto temp = m_mapData[layerId];	//��������R�s�[���Ă���
//���R�Ƃ��Ă̓R�s�[�����ɓ]�u���悤�Ƃ���ƌ��̃f�[�^��������	

	for (int Y = 0; Y < m_mapHeight; ++Y)
	{
		for (int X = 0; X < m_mapWidth; ++X)
		{
			//�ʏ��XY�w��̏ꍇ
			//Y * mapWidth_ + X �Ƃ������ɂȂ�B
			//����ɁA��200�c15�͈ێ�����K�v������
			//�c�ɕ��ׂĂ�������
			//�O�ׂ̗�1�i���ɂ�����	
			int idxSrc = Y * m_mapWidth + X;		//Source Index
			int idxDst = Y + m_mapHeight * X;	//Destination Index
			m_mapData[layerId][idxDst] = temp[idxSrc];

		}
	}
}

void MapChip::Load(const wchar_t* filepath)
{
	ChipData chip;
	int handle = FileRead_open(filepath);
	//int handle = FileRead_open(filepath);
	FileRead_read(&chip, sizeof(chip), handle);

	m_mapWidth = chip.m_mapWidth;
	m_mapHeight = chip.m_mapHeight;
	int layerCount = chip.m_layerCount;		// ���C���[1������̃T�C�Y���v�Z����
	// �}�b�v�̕�*�}�b�v�̍���*(�`�b�v1������̃o�C�g��)
	int layerDataSize = chip.m_mapWidth * chip.m_mapHeight * (chip.m_bitCount / 8);
	m_mapData.resize(layerCount);
	for (auto& layer : m_mapData)
	{
		layer.resize(layerDataSize);
		FileRead_read(layer.data(), layerDataSize, handle);
	}
	FileRead_close(handle);


	//���s���������������̂��߂ɁA�f�[�^�����H
	for (int layerIdx = 0; layerIdx < layerCount; ++layerIdx)
	{
		//TransposeMapData(layerIdx);
	}
}

const MapData& MapChip::GetMapData() const
{
	return m_mapData;
}

const int MapChip::GetChipId(int layerId, int chipX, int chipY) const
{
	auto address = chipY * m_mapWidth + chipX;
	return m_mapData[layerId][address];
}

void MapChip::GetMapSize(int& width, int& height)
{
	width = m_mapWidth;
	height = m_mapHeight;
}
