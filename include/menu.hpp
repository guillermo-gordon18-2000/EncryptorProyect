#ifndef MENU_HPP
#define MENU_HPP

#include <vector>
#include <string>
#include <ncurses.h>
#include <algorithm>
#include <stdexcept>

using namespace std;

void displayEncrypFile(WINDOW *menu_win, const std::vector<std::string>& recentEncryptedFiles, const std::vector<std::string>& recentDecryptedFiles);

void displayMenu(WINDOW *menu_win, const std::vector<std::string>& recentEncryptedFiles, const std::vector<std::string>& recentDecryptedFiles);



std::string selectFileFromList(WINDOW *menu_win, const std::vector<std::string>& files, const std::vector<std::string>& recentDecryptedFiles);

#endif // MENU_HPP
