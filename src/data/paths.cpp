#pragma once

#include <filesystem>

#include "../utilities/environment.h"

#include "paths.h"

namespace paths {
	using namespace std::filesystem;

	namespace roblox {
		// base folder
		path rBase = (environment::getEnv("temp") / "Roblox");

		// content folders
		const path http = (rBase / "http");
		const path sounds = (rBase / "sounds");
	}

	namespace greenlog {
		// base folder
		const path gBase = (environment::getCurrentPath() / ".output");

		// temp folder
		const path temp = (gBase / ".temp");
		const path http = (gBase / "http");
		const path sounds = (gBase / "sounds");
	}
}
