#pragma once
#include<vector>

using MapData = std::vector<std::vector<unsigned char>>;
class MapChip
{
//private:
	struct ChipData
	{
		char m_id[4];	// ���ʎq(FMF_)
		unsigned int m_size;// �f�[�^�T�C�Y
		unsigned int m_mapWidth;// �}�b�v�̕�
		unsigned int m_mapHeight;// �}�b�v�̍���
		unsigned char m_chipWidth;// �`�b�v(�Z��1��)�̕�
		unsigned char m_chipHeight;// �`�b�v(�Z��1��)�̍���
		unsigned char m_layerCount;// ���C���[��
		unsigned char m_bitCount;// 1�Z��������̃r�b�g��(��8�o�C�g��)
	};

	MapData m_mapData;
	int m_mapWidth = 0;
	int m_mapHeight = 0;	

public:
	void Load(const wchar_t* filepath);
	const MapData& GetMapData()const;
	const int GetChipId(int layerId, int chipX, int chipY)const;
	void GetMapSize(int& width, int& height);

};

