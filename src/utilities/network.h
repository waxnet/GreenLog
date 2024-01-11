#pragma once

namespace network {
	std::string buildUrl(const std::filesystem::path path);
	bool downloadToFile(const char* url, const char* destination);
}
