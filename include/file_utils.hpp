//file_utils_hpp
#ifndef FILE_UTILS_HPP
#define FILE_UTILS_HPP

#include <vector>
#include <string>
#include <cmath>

std::vector<std::string> listFiles(const std::string& directory);
std::vector<unsigned char> readFile(const std::string& filename);
void writeFile(const std::string& filename, const std::vector<unsigned char>& data);


bool isFileEncrypted(const std::string &filename);
void moveFileToData(const std::string& filename);

#endif // FILE_UTILS_HPP
