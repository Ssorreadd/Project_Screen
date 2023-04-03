#pragma once

#include <list>
#include <string>

static public ref class ThreadManager
{
	private:
		static void ScreenShotThread(std::list<std::string> treckedProceses, int createScreenShotInterval);
	
	public:
		static void ScreenShotThreadStart(std::list<std::string> treckedProceses, int createScreenShotInterval);

		static void ScreenShotThreadClose();
};

