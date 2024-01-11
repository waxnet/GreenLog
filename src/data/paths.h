#pragma once

#include <filesystem>

namespace paths {
	using namespace std::filesystem;

	namespace roblox {
		// content folders
		extern const path http;
		extern const path sounds;
	}

	namespace greenlog {
		// base folder
		extern const path gBase;
		
		// temp folder
		extern const path temp;
	}
}
