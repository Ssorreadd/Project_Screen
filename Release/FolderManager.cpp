#include "FolderManager.h"

#include <filesystem>
#include <string>

using namespace std;

void FolderManager::CheckFolder(string folderName)
{
	string folderPath = GetMainFolderPath() + folderName;

	filesystem::create_directory(GetMainFolderPath());

	filesystem::create_directory(folderPath);
}

string FolderManager::GetMainFolderPath()
{
	return "C:\\ScreenProjectScreens\\";
}
