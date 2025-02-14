# Add

#ifdef ENABLE_NPC_WEAR_ITEM
#include "PythonBackground.h"
bool CPythonNonPlayer::LoadNPCWear(const char* szNPCWearFile)
{
	m_mapnpcWear.clear();
	CMappedFile File;
	LPCVOID pData;
	if (!CEterPackManager::Instance().Get(File, szNPCWearFile, &pData))
		return false;
	CMemoryTextFileLoader textFileLoader;
	textFileLoader.Bind(File.Size(), pData);
	CTokenVector TokenVector;
	for (DWORD i = 0; i < textFileLoader.GetLineCount(); ++i)
	{
		if (!textFileLoader.SplitLine(i, &TokenVector, "\t"))
			continue;
		else if (TokenVector.size() != NPC_WEAR_MAX+2)
			continue;
		const DWORD npcVnum = atoi(TokenVector[0].c_str());
		std::vector<int> m_vec;
		m_vec.resize(NPC_WEAR_MAX);
		for (BYTE i = 0; i < NPC_WEAR_MAX; ++i)
			m_vec[i] = atoi(TokenVector[i+2].c_str());
		if (m_vec[NPC_WEAR_RACE] > 7)
			continue;
		auto it = m_mapnpcWear.find(TokenVector[1].c_str());
		if (it != m_mapnpcWear.end())
			it->second.emplace(npcVnum, m_vec);
		else
		{
			std::map<DWORD, std::vector<int>> m_map;
			m_map.emplace(npcVnum, m_vec);
			m_mapnpcWear.emplace(TokenVector[1].c_str(), m_map);
		}
	}
	return true;
}
int CPythonNonPlayer::GetNPCWear(const int raceIndex, const BYTE wearIndex)
{
	if (wearIndex >= NPC_WEAR_MAX)
		return -1;
	CPythonBackground& rkBG = CPythonBackground::Instance();
	const auto itSpecial = m_mapnpcWear.find(rkBG.GetWarpMapName());
	if (itSpecial != m_mapnpcWear.end())
	{
		auto itEx = itSpecial->second.find(raceIndex);
		if (itEx != itSpecial->second.end())
			return itEx->second[wearIndex];
	}
	const auto itAll = m_mapnpcWear.find("all");
	if (itAll != m_mapnpcWear.end())
	{
		auto itEx = itAll->second.find(raceIndex);
		if (itEx != itAll->second.end())
			return itEx->second[wearIndex];
	}
	return -1;
}
#endif

