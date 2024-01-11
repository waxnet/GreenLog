#include <filesystem>
#include <Windows.h>
#include <fstream>
#include <string>

#pragma comment(lib, "urlmon.lib")

#include "network.h"

namespace network {
	// build roblox cdn url for the asset from file data
	std::string network::buildUrl(const std::filesystem::path path)
	{
		if (std::filesystem::exists(path))
		{
			std::ifstream file(path);
			if (file.is_open())
			{
				std::string firstLine;
				if (getline(file, firstLine))
				{
					std::string url = "https://" + firstLine.substr(20, 2) + ".rbxcdn.com/";

					for (int number = 0; number < 32; number++)
					{
						url += firstLine.substr((number + 34), 1);
					}

					return url;
				}
			}
		}
		return "";
	}

	// download to file
	bool network::downloadToFile(const char* url, const char* destination)
	{
		return (URLDownloadToFile(NULL, url, destination, 0, NULL) == S_OK);
	}
}
