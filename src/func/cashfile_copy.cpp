#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "../head/cashfile_copy.h"

void collectAllCash(const std::string randomName, const char* targetPath) {
    std::ifstream inputFile(targetPath, std::ios::binary);
    if (!inputFile) {
        std::cerr << "Error opening file 1!" << std::endl;
    }

    std::vector<char> buffer(std::istreambuf_iterator<char>(inputFile), {});
    inputFile.close();

    std::ofstream outputFile(randomName, std::ios::binary);
    if (!outputFile) {
        std::cerr << "Error opening file 2!" << std::endl;
    }

    outputFile.write(buffer.data(), buffer.size());
}