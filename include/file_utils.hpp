#ifndef FILE_UTILS_HPP
#define FILE_UTILS_HPP

#include <string>
#include <vector>

// Declaración de la función para leer archivos
std::vector<unsigned char> readFile(const std::string &filename);

// Declaración de la función para escribir archivos
void writeFile(const std::string &filename, const std::vector<unsigned char> &data);

#endif // FILE_UTILS_HPP
