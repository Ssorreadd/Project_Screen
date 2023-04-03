#pragma once

#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <psapi.h>
#include <string>
#include <iostream>
#include <list>

using namespace std;
using namespace System;

static public ref class ProcessManager
{
private:
	static string GetProcessName(DWORD processID);
	public:
		static String^ GetActiveWindowProccesName();
		
		static list<string> GetAllProcesses();

		static string GetUsedProcessTime(string processName);
};
