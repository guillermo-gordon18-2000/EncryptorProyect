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

void moveFileToData(const std::string& filename) {

    std::string sourcePath = "./" + filename;
    std::string destinationPath = "./data/" + filename;

    if (std::rename(sourcePath.c_str(), destinationPath.c_str()) != 0) {
        throw std::runtime_error("Error al mover el archivo a la carpeta data.");
    }
}

// Función para verificar si un archivo está cifrado
bool isFileEncrypted(const std::string &filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Error al abrir el archivo: " + filename);
    }

    constexpr double entropyThreshold = 7.5; // Umbral de entropía para determinar si un archivo parece cifrado

    // Leer el contenido del archivo para calcular la entropía
    file.seekg(0, std::ios::end);
    std::streampos fileSize = file.tellg();
    file.seekg(0, std::ios::beg);

    std::vector<char> buffer(std::min(fileSize, static_cast<std::streampos>(1024)), '\0'); // Leer hasta 1024 bytes
    file.read(buffer.data(), buffer.size());

    // Calcular la entropía
    double entropy = 0.0;
    std::array<int, 256> freq = {0};
    for (char c : buffer) {
        freq[static_cast<unsigned char>(c)]++;
    }
    for (int i = 0; i < 256; ++i) {
        if (freq[i] > 0) {
            double p = static_cast<double>(freq[i]) / buffer.size();
            entropy -= p * log2(p);
        }
    }

    // Comparar la entropía con el umbral
    return entropy >= entropyThreshold;
}

