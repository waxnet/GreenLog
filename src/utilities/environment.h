#pragma once

#include <filesystem>

namespace environment {
	std::filesystem::path getCurrentPath();
	bool checkPath(const std::filesystem::path path);
	std::filesystem::path getEnv(const char* variable);
	void makeFolder(const std::filesystem::path folder);
	void deleteFolder(const std::filesystem::path folder);
	void cleanFolders(const std::filesystem::path folders[], const int numberOfFolders);
	void parseFolders(const std::filesystem::path folders[], const int numberOfFolders);
}
