#include <algorithm>
#include <iostream>
#include <string>

#include "io.h"

namespace io {
	// simpler output function
	void io::out(const std::string text) {
		std::cout << text << std::endl;
	}

	// simpler input function
	std::string io::inp(const std::string text) {
		std::cout << text << " : ";

		std::string output;
		std::getline(std::cin, output);
		std::transform(output.begin(), output.end(), output.begin(), ::tolower);

		return output;
	}
}
