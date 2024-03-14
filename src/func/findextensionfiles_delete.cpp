#include <iostream>
#include <filesystem>
#include <string>
#include "../head/findextensionfiles_delete.h"

void deleteFilesWithExtension(const std::string& directory, const std::string& extension) {
    for (const auto& entry : std::filesystem::directory_iterator(directory)) {
        if (std::filesystem::is_regular_file(entry)) {
            std::string filename = entry.path().filename().string();
            if (filename.size() >= extension.size() && 
                filename.compare(filename.size() - extension.size(), extension.size(), extension) == 0) {
                std::error_code ec;
                std::filesystem::remove(entry, ec);
            }
        }
    }
}