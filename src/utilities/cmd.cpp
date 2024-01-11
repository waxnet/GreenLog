#include <cstdlib>

#include "cmd.h"

namespace cmd {
	// execute multiple system call/commands
	void cmd::execute(const char* commands[], const int numberOfCommands)
	{
		for (int index = 0; index < numberOfCommands; index++)
		{
			system(commands[index]);
		}
	}
}
