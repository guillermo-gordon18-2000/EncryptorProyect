#include "file_utils.hpp"
#include <fstream>
#include <iterator>

// Implementación de la función para leer archivos
std::vector<unsigned char> readFile(const std::string &filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Cannot open file: " + filename);
    }
    
    // Usamos el constructor del vector para inicializarlo con los datos del archivo
    return std::vector<unsigned char>((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
}

// Implementación de la función para escribir archivos
void writeFile(const std::string &filename, const std::vector<unsigned char> &data) {
    std::ofstream file(filename, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Cannot create file: " + filename);
    }
    
    // Escribimos los datos en el archivo
    file.write(reinterpret_cast<const char *>(data.data()), data.size());
}
