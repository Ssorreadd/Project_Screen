#include "ThreadManager.h"
#include "ScreenShotManager.h"
#include "ProcessManager.h"
#include <thread>
#include <chrono>
#include <list>
#include <string>

static bool threadIsPerformed = false;

void ThreadManager::ScreenShotThread(std::list<std::string> treckedProceses, int createScreenShotInterval)
{
	while (threadIsPerformed)
	{
		for (string process : treckedProceses)
		{
			if (ProcessManager::GetActiveWindowProccesName()->ToLower() == (gcnew System::String(process.c_str()))->ToLower())
			{
				ScreenShotManager::DoScreenShot();
			}
			if (ProcessManager::GetActiveWindowProccesName()->ToLower() == "explorer.exe")
			{
				ScreenShotManager::DoScreenShot();
			}
		}
		
		std::this_thread::sleep_for(std::chrono::milliseconds(createScreenShotInterval));
	}
}

void ThreadManager::ScreenShotThreadStart(std::list<std::string> treckedProceses, int createScreenShotInterval)
{
	threadIsPerformed = true;

	std::thread th(ScreenShotThread, treckedProceses, createScreenShotInterval);
	
	th.detach();
}

void ThreadManager::ScreenShotThreadClose()
{
	threadIsPerformed = false;
}
