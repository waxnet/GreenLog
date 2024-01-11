#include <filesystem>
#include <fstream>
#include <string>

#include "magic.h"

namespace magic {
	// get the file type/extension
	std::string magic::getFileType(const std::filesystem::path path)
	{
		if (std::filesystem::exists(path))
		{
			std::ifstream file(path);
			if (file.is_open())
			{
				std::string firstLine;
				if (getline(file, firstLine))
				{
					// images
					if (stringContains(firstLine, "PNG"))
						return "png";
					
					// textures
					if (stringContains(firstLine, "KTX 11"))
						return "ktx";

					// audios
					if (stringContains(firstLine, "ID3") && stringContains(firstLine, "TSSE"))
						return "mp3";

					if (stringContains(firstLine, "OggS") && stringContains(firstLine, "vorbis"))
						return "ogg";

					// videos
					if (stringContains(firstLine, "webm"))
						return "webm";

					if (stringContains(firstLine, "matroska"))
						return "mkv";

					if (stringContains(firstLine, "ID3") && stringContains(firstLine, "TPE2"))
						return "mpeg";
				}
			}
		}

		// if file type is not found return "unknown"
		return "unknown";
	}

	// check if a string contains a substring
	bool magic::stringContains(const std::string string, const std::string substring)
	{
		return (string.find(substring) != std::string::npos);
	}

	// check if substring is inside a specific amount of lines
	bool magic::fileLinesContain(const std::filesystem::path path, const int numberOfLines, const std::string substring)
	{
		bool foundSubstring = false;

		if (std::filesystem::exists(path))
		{
			std::ifstream file(path);
			if (file.is_open())
			{
				std::string line;
				int counter = 0;

				while (getline(file, line) && counter < numberOfLines) {
					if (stringContains(line, substring))
					{
						foundSubstring = true;
						break;
					}
					counter++;
				}
			}
		}

		return foundSubstring;
	}

	// convert string to integer
	bool magic::stringToInteger(const std::string string, int& number, const int defaultValue)
	{
		try {
			number = std::stoi(string);
			return true;
		} catch (std::invalid_argument _) {}

		number = defaultValue;
		return false;
	}
}
