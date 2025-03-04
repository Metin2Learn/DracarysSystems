# add

# Search

		if(m_map_pkPCChr.size())
		{
			auto it = m_map_pkPCChr.find(szName);
			if (m_map_pkPCChr.end() != it)
				m_map_pkPCChr.erase(it);
		}

# add before
# to do find where
#ifdef ENABLE_PVP_CAMERA_MODE
		RemoveCamera(ch);
#endif


#ifdef ENABLE_PVP_CAMERA_MODE
#include "pvp_duel.h"
bool CHARACTER_MANAGER::IsCameraModeMap(const DWORD mapIndex)
{
	if (mapIndex == PVP_DUEL_MAP_INDEX)
		return true;
	return false;
}
void CHARACTER_MANAGER::SetCameraPlayer(LPCHARACTER camera, LPCHARACTER watcher)
{
	auto it = m_cameraMode.find(camera);
	if (it != m_cameraMode.end())
	{
		auto itWatcher = std::find(it->second.begin(), it->second.end(), watcher);
		if (itWatcher == it->second.end())
			it->second.emplace_back(watcher);
	}
	else
	{
		std::vector<LPCHARACTER> m_data;
		m_data.clear();
		m_data.emplace_back(watcher);
		m_cameraMode.emplace(camera, m_data);
	}
}

void CHARACTER_MANAGER::RemoveCamera(LPCHARACTER watcher)
{
	auto isCamera = m_cameraMode.find(watcher);
	if (isCamera != m_cameraMode.end())
	{
		isCamera->second.clear();
		m_cameraMode.erase(isCamera);
		return;
	}

	auto it = m_cameraMode.begin();
	while (it != m_cameraMode.end())
	{
		auto itWatchers = it->second.begin();
		while (itWatchers != it->second.end())
		{
			LPCHARACTER ch = *itWatchers;
			if (ch == watcher)
				itWatchers = it->second.erase(itWatchers);
			else
				++itWatchers;
		}
		++it;
	}
}

void CHARACTER_MANAGER::GetMyWatcher(LPCHARACTER camera, std::vector<LPCHARACTER>& m_data)
{
	m_data.clear();
	auto it = m_cameraMode.find(camera);
	if (it != m_cameraMode.end())
	{
		for(DWORD j=0;j<it->second.size();++j)
			m_data.emplace_back(it->second[j]);
	}
}

#endif