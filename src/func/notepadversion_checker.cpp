#include <iostream>
#include <windows.h>
#include <sstream>
#include <string>
#include "../head/notepadversion_checker.h"

int isNotepadVersion() {
    const wchar_t* notepadPath = L"C:\\Windows\\System32\\notepad.exe";

    DWORD versionSize;
    DWORD dummy;

    versionSize = GetFileVersionInfoSizeW(notepadPath, &dummy);
    if (versionSize == 0) {
        std::cerr << "Failed to get file version info size" << std::endl;
        return -1;
    }

    // Allocate memory for version info
    LPBYTE versionInfo = new BYTE[versionSize];
    if (!GetFileVersionInfoW(notepadPath, 0, versionSize, versionInfo)) {
        std::cerr << "Failed to get file version info" << std::endl;
        delete[] versionInfo;
        return -1;
    }

    // Get fixed file info
    VS_FIXEDFILEINFO* fileInfo;
    UINT len;
    if (!VerQueryValueW(versionInfo, L"\\", reinterpret_cast<void**>(&fileInfo), &len)) {
        std::cerr << "Failed to query file version info" << std::endl;
        delete[] versionInfo;
        return -1;
    }

    // Extract version components
    DWORD versionMS = fileInfo->dwFileVersionMS;
    DWORD versionLS = fileInfo->dwFileVersionLS;
    WORD major = HIWORD(versionMS);
    WORD minor = LOWORD(versionMS);
    WORD build = HIWORD(versionLS);
    WORD revision = LOWORD(versionLS);

    delete[] versionInfo;

    int versionNumber = major * 1000000 + minor * 10000 + build * 100 + revision;
    return versionNumber;
}