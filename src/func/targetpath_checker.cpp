#include <iostream>
#include <windows.h>
#include <filesystem>
#include "../head/targetpath_checker.h"

bool isTargetPath(const std::string& path) {
    return std::filesystem::exists(path);
}
