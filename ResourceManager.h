#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include "Utilities.h"
#include <string>
#include <map>
#include <fstream>
#include <sstream>

template <typename Derived, typename T>
class ResourceManager
{
public:
	ResourceManager(const std::string& path) {
		loadPaths(path);
	}

	virtual ~ResourceManager() {
		purgeResources();
	}

	T* getResource(const std::string& id)
	{
		auto res = find(id);
		return (res ? res->first : nullptr);
	}

	std::string getPath(const std::string& id)
	{
		auto path = m_paths.find(id);
		return (path != m_paths.end() ? path->second : "");
	}

	bool requireResource(const std::string& id)
	{
		auto res = find(id);
		if (res)
		{
			res->second++;
			return true;
		}
		auto path = m_paths.find(id);
		if (path != m_paths.end())
		{
			T* resource = load(path->second);
			if (!resource) {
				return false;
			}
			m_resources.emplace(id, std::make_pair(resource, 1));
			return true;
		}
		return false;
	}

	bool releaseResource(const std::string& id)
	{
		auto res = find(id);
		if (!res) {
			return false;
		}
		res->second--;
		if (!res->second) {
			unload(id);
		}
		return true;
	}

	void purgeResources()
	{
		for (auto iter = m_resources.begin(); iter != m_resources.end();)
		{
			delete iter->second.first;
			iter->second.first = nullptr;
			iter = m_resources.erase(iter);
		}
	}

	//So the derived classes can use this function
protected:
	T* load(const std::string& path) {
		return static_cast<Derived*>(this)->load(path);
	}

private:
	std::map<std::string, std::pair<T*, unsigned int>> m_resources;
	std::map<std::string, std::string> m_paths;

	std::pair<T*, unsigned int>* find(const std::string& id)
	{
		auto iter = m_resources.find(id);
		return (iter != m_resources.end() ? &iter->second : nullptr);
	}

	bool unload(const std::string& id)
	{
		auto res = m_resources.find(id);
		if (res != m_resources.end())
		{
			delete res->second.first;
			m_resources.erase(res);
			return true;
		}
		return false;
	}

	void loadPaths(const std::string& path)
	{
		std::ifstream stream;
		stream.open(Utils::GetWorkingDirectory() + path);
		if (stream.is_open())
		{
			std::string line;
			while (std::getline(stream, line))
			{
				std::stringstream keyStream;
				std::string path;
				std::string pathFile;
				keyStream >> path;
				keyStream >> pathFile;

				m_paths.emplace(path, pathFile);

			}
			stream.close();
		}
	}
};
#endif // !RESOURCE_MANAGER_H
