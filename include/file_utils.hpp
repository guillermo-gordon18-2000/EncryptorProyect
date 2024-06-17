//file_utils_hpp
#ifndef FILE_UTILS_HPP
#define FILE_UTILS_HPP

#include <vector>
#include <string>

std::vector<std::string> listFiles(const std::string& directory);
std::vector<unsigned char> readFile(const std::string& filename);
void writeFile(const std::string& filename, const std::vector<unsigned char>& data);

#endif // FILE_UTILS_HPP
