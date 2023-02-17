#include "MapChip.h"
#include"DxLib.h"

void MapChip::Load(const wchar_t* filepath)

{
	ChipData chip;
	int handle = FileRead_open(reinterpret_cast<const TCHAR *>(filepath));
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
