#pragma once
#include<vector>

using MapData = std::vector<std::vector<unsigned char>>;
class MapChip
{
//private:
	struct ChipData
	{
		char m_id[4];	// 識別子(FMF_)
		unsigned int m_size;// データサイズ
		unsigned int m_mapWidth;// マップの幅
		unsigned int m_mapHeight;// マップの高さ
		unsigned char m_chipWidth;// チップ(セル1個)の幅
		unsigned char m_chipHeight;// チップ(セル1個)の高さ
		unsigned char m_layerCount;// レイヤー数
		unsigned char m_bitCount;// 1セル当たりのビット数(÷8バイト数)
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

