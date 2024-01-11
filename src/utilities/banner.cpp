#include <iostream>
#include <string>
#include <Windows.h>
#include <wincon.h>

#include "banner.h"

namespace banner {
	void banner::display()
	{
		// banner info
		std::string bannerParts[] = {
			" _____                      __              ",
			"|   __| ___  ___  ___  ___ |  |    ___  ___ ",
			"|  |  ||  _|| -_|| -_||   ||  |__ | . || . |",
			"|_____||_|  |___||___||_|_||_____||___||_  |",
			"                                       |___|\n"
		};

		// get output handle
		HANDLE outputHandle = GetStdHandle(STD_OUTPUT_HANDLE);

		// set console foreground color to green
		SetConsoleTextAttribute(outputHandle, (
			FOREGROUND_INTENSITY |
			FOREGROUND_GREEN
		));

		// display banner
		for (std::string part : bannerParts)
		{
			for (int _ = 0; _ < 23; _++)
			{
				std::cout << " ";
			}
			std::cout << part << std::endl;
		}

		// reset console foreground color to white
		SetConsoleTextAttribute(outputHandle, (
			FOREGROUND_INTENSITY |
			FOREGROUND_RED |
			FOREGROUND_GREEN |
			FOREGROUND_BLUE
		));
	}
}
