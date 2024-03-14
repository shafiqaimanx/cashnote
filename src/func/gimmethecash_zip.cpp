#include <iostream>
#include <vector>
#include <fstream>
#include "../minizip/zip.h"
#include "../minizip/unzip.h"
#include "../head/gimmethecash_zip.h"

bool addFileToZip(const std::string& zipFileName, const std::vector<const char*>& fileNamesToAdd) {
    // Open the zip file for writing
    zipFile zf = zipOpen(zipFileName.c_str(), APPEND_STATUS_CREATE);

    if (!zf) {
        std::cerr << "Error: Could not open " << zipFileName << " for writing\n";
        return false;
    }

    for (const char* fileName : fileNamesToAdd) {
        // Open the file to add to the zip archive
        FILE* file = fopen(fileName, "rb");

        if (!file) {
            std::cerr << "Error: Could not open " << fileName << " for reading\n";
            zipClose(zf, nullptr);
            return false;
        }

        // Allocate memory for file data
        const size_t bufferSize = 1024;
        void* buffer = malloc(bufferSize);

        if (!buffer) {
            std::cerr << "Error: Memory allocation failed\n";
            fclose(file);
            zipClose(zf, nullptr);
            return false;
        }

        // Get file size
        fseek(file, 0, SEEK_END);
        size_t fileSize = ftell(file);
        fseek(file, 0, SEEK_SET);

        // Add the file to the zip archive
        int result = zipOpenNewFileInZip(zf, fileName, nullptr, nullptr, 0, nullptr, 0, nullptr, Z_DEFLATED, Z_DEFAULT_COMPRESSION);

        if (result != ZIP_OK) {
            std::cerr << "Error: Failed to open " << fileName << " in " << zipFileName << "\n";
            free(buffer);
            fclose(file);
            zipClose(zf, nullptr);
            return false;
        }

        // Read file data into buffer and write to zip
        while (fileSize > 0) {
            const size_t bytesRead = fread(buffer, 1, bufferSize, file);
            if (zipWriteInFileInZip(zf, buffer, bytesRead) < 0) {
                std::cerr << "Error: Failed to write data to " << zipFileName << "\n";
                free(buffer);
                fclose(file);
                zipClose(zf, nullptr);
                return false;
            }
            fileSize -= bytesRead;
        }

        // Close the file in the zip archive
        zipCloseFileInZip(zf);

        // Clean up
        free(buffer);
        fclose(file);
    }

    zipClose(zf, nullptr);
    return true;
}