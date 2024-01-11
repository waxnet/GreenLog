#pragma once

namespace process {
	int findProcess(const char* processName);
	void killProcess(const int processID);
	int waitForProcess(const char* processName);
}
