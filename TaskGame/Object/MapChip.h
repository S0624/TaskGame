#pragma once
#include<vector>

using MapData = std::vector<std::vector<unsigned char>>;
class MapChip
{
private:
	struct ChipData
	{
		uint8_t m_id[4];	// ���ʎq(FMF_)
		uint32_t m_size;// �f�[�^�T�C�Y
		uint32_t m_mapWidth;// �}�b�v�̕�
		uint32_t m_mapHeight;// �}�b�v�̍���
		uint8_t  m_chipWidth;// �`�b�v(�Z��1��)�̕�
		uint8_t  m_chipHeight;// �`�b�v(�Z��1��)�̍���
		uint8_t  m_layerCount;// ���C���[��
		uint8_t  m_bitCount;// 1�Z��������̃r�b�g��(��8�o�C�g��)
	};

	MapData m_mapData;
	int m_mapWidth = 0;
	int m_mapHeight = 0;	
private:
	/// <summary>
	/// �f�[�^�̓��e��XY�]�u����
	/// </summary>
	/// <param name="layerId">���C���[ID</param>
	void TransposeMapData(int layerId);
public:
	void Load(const wchar_t* filePath);
	const MapData& GetMapData()const;
	const int GetChipId(int layerId, int chipX, int chipY)const;
	void GetMapSize(int& width, int& height);

};

