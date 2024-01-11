#pragma once

namespace magic {
	std::string getFileType(const std::filesystem::path path);
	bool stringContains(const std::string string, const std::string substring);
	bool fileLinesContain(const std::filesystem::path path, const int numberOfLines, const std::string substring);
	bool stringToInteger(const std::string string, int& number, const int defaultValue);
}
