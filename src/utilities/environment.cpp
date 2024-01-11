#include <filesystem>
#include <Windows.h>

#include "../data/counter.h"
#include "../data/paths.h"

#include "environment.h"
#include "network.h"
#include "magic.h"

namespace environment {
	// get executable path
	std::filesystem::path environment::getCurrentPath()
	{
		char buffer[MAX_PATH];
		GetModuleFileName(NULL, buffer, sizeof(buffer));

		return std::filesystem::path(buffer).parent_path();
	}

	// check if path exists
	bool environment::checkPath(const std::filesystem::path path)
	{
		return (std::filesystem::exists(path) == true);
	}

	// get environmental variable and convert it to path
	std::filesystem::path environment::getEnv(const char* variableName)
	{
		char* buffer = nullptr;
		size_t numberOfElements = 0;

		if (_dupenv_s(&buffer, &numberOfElements, variableName) == 0 && buffer != nullptr)
		{
			free(buffer);
		}

		return std::filesystem::path(buffer);
	}

	// create a folder if it doesnt exist
	void environment::makeFolder(const std::filesystem::path folder)
	{
		if (!checkPath(folder))
		{
			std::filesystem::create_directories(folder);
		}
	}

	// delete a folder if it exist
	void environment::deleteFolder(const std::filesystem::path folder)
	{
		if (checkPath(folder))
		{
			std::filesystem::remove_all(folder);
		}
	}

	// clean multiple folders
	void environment::cleanFolders(const std::filesystem::path folders[], const int numberOfFolders)
	{
		for (int index = 0; index < numberOfFolders; index++)
		{
			std::filesystem::path currentFolder = folders[index];
			
			if (checkPath(currentFolder))
			{
				std::filesystem::remove_all(currentFolder);
			}
			std::filesystem::create_directories(currentFolder);
		}
	}

	// parse files in multiple folders
	void environment::parseFolders(const std::filesystem::path folders[], const int numberOfFolders)
	{
		for (int index = 0; index < numberOfFolders; index++)
		{
			std::filesystem::path currentFolder = folders[index];

			// check if current folder exists
			if (checkPath(currentFolder))
			{
				// check files in current folder
				for (const auto& entry : std::filesystem::directory_iterator(currentFolder)) {
					std::filesystem::path entryPath = entry.path();

					// check if entry is a regular file
					if (!std::filesystem::is_regular_file(entryPath))
						continue;

					// check if file needs to be downloaded
					if (!magic::stringContains(entryPath.filename().string(), "RBX"))
					{
						// check if file is downloadable
						if (!magic::fileLinesContain(entryPath, 20, "binary/octet-stream"))
							continue;

						// get and check file url
						std::string url = network::buildUrl(entryPath);
						if (url == "")
							continue;

						// create temp folder
						makeFolder(paths::greenlog::temp);

						// download file
						std::filesystem::path downloadPath = (paths::greenlog::temp / "data.txt");
						bool didDownload = network::downloadToFile(
							url.c_str(),
							downloadPath.string().c_str()
						);
						if (!didDownload)
							continue;

						// set entry path to downloaded file path
						entryPath = downloadPath;
					}

					// file type
					std::string fileType = magic::getFileType(entryPath);

					// file name
					counter::increaseValue(fileType);
					std::string fileName = std::to_string(counter::getValue(fileType));

					// file destination
					std::filesystem::path fileDestination(paths::greenlog::gBase / fileType);

					// file extension
					std::string fileExtension = fileType;
					if (fileExtension == "unknown")
						fileExtension = "txt";

					// create file destination path
					makeFolder(fileDestination);

					// rename and move file to new file path
					std::filesystem::path newFilePath = (
						fileDestination /
						std::filesystem::path(
							fileName +
							"." +
							fileExtension
						)
					);
					std::filesystem::rename(entryPath, newFilePath);
				}
			}
		}

		// remove temp folder
		deleteFolder(paths::greenlog::temp);
	}
}
