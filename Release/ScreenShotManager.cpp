#include "ScreenShotManager.h"
#include "ProcessManager.h"
#include "FolderManager.h"
#include <Windows.h>
#include <algorithm>
#include <ctime>
#include <string>

using namespace std;

#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_DEPRECATE
#define _CRT_SECURE_NO_DEPRECATE
#pragma warning(disable : 4996)

std::string ScreenShotManager::CreatePath()
{
    time_t now = time(0);

    tm* ltm = localtime(&now);

    const time_t tmDate = time(nullptr);

    char bufDate[64];
    strftime(bufDate, std::size(bufDate), "%d.%m.%Y", localtime(&tmDate));


    char bufTime[64];
    strftime(bufTime, sizeof(bufTime), "%H-%M-%S", ltm);

    System::String^ processName = ProcessManager::GetActiveWindowProccesName();

    string appName;

    for each (char letter in (processName->Remove(processName->Length - 4))->ToCharArray())
    {
        appName += letter;
    }

    FolderManager::CheckFolder(appName);

    FolderManager::CheckFolder(appName + "\\" + bufDate);

    string path = FolderManager::GetMainFolderPath() + appName + "\\" + bufDate + "\\" + bufTime + ".bmp";

    return path;
}

int ScreenShotManager::DoScreenShot()
{
    int x1, y1, x2, y2, w, h;

    if (ProcessManager::GetActiveWindowProccesName()->ToLower() == "screen_project.exe")
    {
        HWND hwndC = GetActiveWindow();

        ShowWindow(hwndC, SW_MINIMIZE);
    }

    HWND hwnd = GetForegroundWindow();

    Sleep(200);

    x1 = GetSystemMetrics(SM_XVIRTUALSCREEN);
    y1 = GetSystemMetrics(SM_YVIRTUALSCREEN);
    x2 = GetSystemMetrics(SM_CXVIRTUALSCREEN);
    y2 = GetSystemMetrics(SM_CYVIRTUALSCREEN);

    HDC hScreen = GetDC(NULL);

    float g_DPIScale = 1.0f;

    float dpi = GetDpiForWindow(hwnd);
    g_DPIScale = dpi / 96.0f;

    w = x2 - x1;
    h = y2 - y1;

    w *= g_DPIScale;
    h *= g_DPIScale;

    HDC hDC = CreateCompatibleDC(hScreen);
    HBITMAP hBitmap = CreateCompatibleBitmap(hScreen, w, h);
    HGDIOBJ old_obj = SelectObject(hDC, hBitmap);
    BOOL bRet = BitBlt(hDC, 0, 0, w, h, hScreen, x1, y1, SRCCOPY);


    SelectObject(hDC, hBitmap);
    TCHAR M[200];

    string path = CreatePath();

    std::wstring stemp = std::wstring(path.begin(), path.end());
    LPCWSTR filePath = stemp.c_str();

    //LPCWSTR filePath = L"C:\\images\\Screenshot%d.bmp";
    wsprintf(M, filePath, 1);

    BitBlt(hDC, 0, 0, w, h, hScreen, 0, 0, SRCCOPY);

    BITMAPINFO bmp_info = { 0 };
    bmp_info.bmiHeader.biSize = sizeof(bmp_info.bmiHeader);
    bmp_info.bmiHeader.biWidth = w;
    bmp_info.bmiHeader.biHeight = h;
    bmp_info.bmiHeader.biPlanes = 1;
    bmp_info.bmiHeader.biBitCount = 24;
    bmp_info.bmiHeader.biCompression = BI_RGB;

    int bmp_padding = (w * 3) % 4;
    if (bmp_padding != 0) bmp_padding = 4 - bmp_padding;

    BYTE* bmp_pixels = new BYTE[(w * 3 + bmp_padding) * h];;
    GetDIBits(hDC, hBitmap, 0, h, bmp_pixels, &bmp_info, DIB_RGB_COLORS);

    BITMAPFILEHEADER bmfHeader;
    HANDLE bmp_file_handle = CreateFile(M, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

    // Add the size of the headers to the size of the bitmap to get the total file size
    DWORD dwSizeofDIB = (w * 3 + bmp_padding) * h + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

    //Offset to where the actual bitmap bits start.
    bmfHeader.bfOffBits = (DWORD)sizeof(BITMAPFILEHEADER) + (DWORD)sizeof(BITMAPINFOHEADER);

    //Size of the file
    bmfHeader.bfSize = dwSizeofDIB;

    //bfType must always be BM for Bitmaps
    bmfHeader.bfType = 0x4D42; //BM

    DWORD dwBytesWritten = 0;
    WriteFile(bmp_file_handle, (LPSTR)&bmfHeader, sizeof(BITMAPFILEHEADER), &dwBytesWritten, NULL);
    WriteFile(bmp_file_handle, (LPSTR)&bmp_info.bmiHeader, sizeof(BITMAPINFOHEADER), &dwBytesWritten, NULL);
    WriteFile(bmp_file_handle, (LPSTR)bmp_pixels, (w * 3 + bmp_padding) * h, &dwBytesWritten, NULL);

    //Close the handle for the file that was created
    CloseHandle(bmp_file_handle);

    //αστεπ ξαμενΰ
    //OpenClipboard(NULL);
    //EmptyClipboard();
    //SetClipboardData(CF_BITMAP, hBitmap);
    //CloseClipboard();

    DeleteDC(hDC);
    DeleteObject(hBitmap);
    ReleaseDC(NULL, hScreen);
    delete[] bmp_pixels;

    return 0;
}
