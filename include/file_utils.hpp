//file_utils_hpp
#ifndef FILE_UTILS_HPP
#define FILE_UTILS_HPP

#include <vector>
#include <string>
#include <cmath>
#include <ncurses.h>

using std::vector;
using std::string;

std::vector<std::string> listFiles(const std::string& directory);

std::vector<unsigned char> readFile(const std::string& filename);

void writeFile(const std::string& filename, const std::vector<unsigned char>& data);

bool isFileEncrypted(const std::string &filename);

void moveFileToData(const std::string& filename);

std::string promptForFilename(WINDOW *menu_win, const std::string &prompt, const std::string &originalFilename, const std::string &method);


//void processEncryptedFiles(WINDOW *menu_win, const vector<string>& recentEncryptedFiles, const vector<string>& recentDecryptedFiles, unsigned char key[], unsigned char iv[], int width);

//void processDecryptedFiles(WINDOW *menu_win, const vector<string>& recentEncryptedFiles, vector<string>& recentDecryptedFiles, unsigned char key[], unsigned char iv[], int width);
#endif // FILE_UTILS_HPP
