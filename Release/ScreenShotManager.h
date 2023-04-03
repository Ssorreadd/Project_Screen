#pragma once

#include <string>

static public ref class ScreenShotManager
{
	private:
		static std::string CreatePath();
	public:
		static int DoScreenShot();

};

