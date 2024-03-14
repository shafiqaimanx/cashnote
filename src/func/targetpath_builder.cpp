#include <iostream>
#include "../head/targetpath_builder.h"

std::string targetPathBuilder() {
    const char* enVar = getenv("LOCALAPPDATA");
    const char* halfPath = "\\Packages\\Microsoft.WindowsNotepad_8wekyb3d8bbwe\\LocalState\\TabState\\";
    const std::string result = std::string(enVar) + halfPath;
    return result;
}