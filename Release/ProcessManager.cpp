#include "ProcessManager.h"
#include "FolderManager.h"
#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <psapi.h>
#include <string>
#include <iostream>
#include <list>
#include <ctime>
#include <filesystem>

using namespace std;
using namespace System;
using namespace filesystem;

string ProcessManager::GetProcessName(DWORD processID)
{
    TCHAR szProcessName[MAX_PATH] = L"<unknown>";

    // Get a handle to the process.

    HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION |
        PROCESS_VM_READ,
        FALSE, processID);

    // Get the process name.

    if (hProcess != NULL)
    {
        HMODULE hMod;
        DWORD cbNeeded;

        if (EnumProcessModules(hProcess, &hMod, sizeof(hMod),
            &cbNeeded))
        {
            GetModuleBaseName(hProcess, hMod, szProcessName,
                sizeof(szProcessName) / sizeof(TCHAR));
        }
    }

    int i = 0;
    string name;
    while (szProcessName[i] != '\0')
    {
        name += szProcessName[i];
        i++;
    }

    /*_tprintf(TEXT("%s  (PID: %u)\n"), szProcessName, processID);*/
       // Release the handle to the process.

    CloseHandle(hProcess);

    return name;

}


System::String^ ProcessManager::GetActiveWindowProccesName()
{
    HWND hwnd;

    hwnd = GetForegroundWindow();

    Sleep(250); 

    DWORD pid;
    GetWindowThreadProcessId(GetForegroundWindow(), &pid);
    HANDLE hProc = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ,
        FALSE, pid);

    TCHAR nameP[MAX_PATH] = L"<unknown>";
    /*  GetProcessImageFileName(hProc, nameP, 256);*/

    HMODULE hMod;
    DWORD cbNeeded;

    if (EnumProcessModules(hProc, &hMod, sizeof(hMod), &cbNeeded))
    {
        GetModuleBaseName(hProc, hMod, nameP, sizeof(nameP) / sizeof(TCHAR));
    }

    int i = 0;
    System::String^ name;
    while (nameP[i] != '\0')
    {
        name += nameP[i];
        i++;
    }

    return (System::String^)name;
}

list<string> ProcessManager::GetAllProcesses()
{
    list<string> tmpList;

    DWORD aProcesses[1024], cbNeeded{}, cProcesses;
    unsigned int i;

    if (!EnumProcesses(aProcesses, sizeof(aProcesses), &cbNeeded))
    {
        return tmpList;
    }

    cProcesses = cbNeeded / sizeof(DWORD);

    for (i = 0; i < cProcesses; i++)
    {
        if (aProcesses[i] != 0)
        {
            auto name = GetProcessName(aProcesses[i]);


            tmpList.emplace_back(name);

       
        }
    }

    list<string> processesList;

    for (string process : tmpList)
    {
        if (process != "<unknown>")
        {
            processesList.emplace_back(process);
        }
    }

    processesList.unique();

    return processesList;
}

string ProcessManager::GetUsedProcessTime(string processName)
{
    time_t timeNow = time(0);

    tm* currentTime = localtime(&timeNow);

    const time_t tmDate = time(nullptr);

    char bufDate[64];
    strftime(bufDate, std::size(bufDate), "%d.%m.%Y", localtime(&tmDate));


    string folderPath = FolderManager::GetMainFolderPath() + processName + "\\" + bufDate + "\\";

    string processFile;

    try
    {
        for (auto& p : directory_iterator(folderPath))
        {
            path path = p;
            processFile = path.generic_string();

            break;
        }
    }
    catch (const std::exception&)
    {
        return "00:00:00";
    }

    string fileCreateTimeStr = "";
    processFile = processFile.substr(processFile.find_last_of("/") + 1, string::npos);

    for (int i = 0; i < processFile.size() - 4; i++)
    {
        fileCreateTimeStr += processFile[i];
    }

    tm* fileCreateTime = new tm;

    int hyphenCount = 0;
    string tmp = "";

    int sizee = fileCreateTimeStr.size();

    for (int i = 0; i < sizee; i++)
    {
        if (fileCreateTimeStr[i] == '-' && i != sizee - 1)
        {
            switch (hyphenCount)
            {
                case 0:
                    fileCreateTime->tm_hour = stoi(tmp);
                    break;
                case 1:
                    fileCreateTime->tm_min = stoi(tmp);
                    break;
            }

            hyphenCount++;
   
            tmp = "";

            continue;
        }

        if (i == sizee - 1)
        {
            fileCreateTime->tm_sec = stoi(tmp + fileCreateTimeStr[i]);
        }

        tmp += fileCreateTimeStr[i];
    }

    timeNow -= fileCreateTime->tm_hour * 3600;
    timeNow -= fileCreateTime->tm_min * 60;
    timeNow -= fileCreateTime->tm_sec;

    struct tm* usedTime = localtime(&timeNow);

    strftime(bufDate, sizeof(bufDate), "%H:%M:%S", usedTime);
    
    return bufDate;
}
