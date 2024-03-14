#include <windows.h>
#include <VersionHelpers.h>
#include "../head/windowsversion_checker.h"

bool isWindowsVersion10() {
    return IsWindows10OrGreater();
}