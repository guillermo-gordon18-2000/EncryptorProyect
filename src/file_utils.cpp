// file_utils.cpp

#include "file_utils.hpp"
#include <fstream>
#include <boost/filesystem.hpp> // Incluir Boost.Filesystem en lugar de std::filesystem

namespace fs = boost::filesystem; // Namespace alias para Boost.Filesystem

std::vector<std::string> listFiles(const std::string& directory) {
    std::vector<std::string> files;
    fs::path dirPath(directory);
    if (!fs::exists(dirPath) || !fs::is_directory(dirPath)) {
        throw std::runtime_error("Directory does not exist or is not a directory");
    }

    for (const auto& entry : fs::directory_iterator(dirPath)) {
        if (fs::is_regular_file(entry)) {
            files.push_back(entry.path().filename().string());
        }
    }
    return files;
}

std::vector<unsigned char> readFile(const std::string &filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file: " + filename);
    }
    return std::vector<unsigned char>((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
}

void writeFile(const std::string &filename, const std::vector<unsigned char> &data) {
    std::ofstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file: " + filename);
    }
    file.write(reinterpret_cast<const char *>(data.data()), data.size());
}
