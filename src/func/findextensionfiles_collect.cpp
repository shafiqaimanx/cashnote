#include <iostream>
#include <filesystem>
#include "../head/findextensionfiles_collect.h"

void collectAllCashExtension(const std::string extension) {
    std::filesystem::path currentDir = std::filesystem::current_path();

    for (const auto& entry: std::filesystem::directory_iterator(currentDir)) {
        if (entry.is_regular_file() && entry.path().extension() == extension) {
            std::cout << entry.path().filename() << std::endl;
        }
    }
}
