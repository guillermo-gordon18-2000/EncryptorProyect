#ifndef KEY_ENCRYPTION_HPP
#define KEY_ENCRYPTION_HPP

#include <string>
#include <vector>
#include <ncurses.h>

void encryptKey(const std::string &key);
void decryptKey(const std::string &encryptedKey);
std::vector<std::string> getRecentEncryptedKeys(int limit);
std::vector<std::string> getRecentDecryptedKeys(int limit);

// Declarar las funciones del CRUD de llaves
void createKey(WINDOW *menu_win);
void viewKeys(WINDOW *menu_win);
void editKey(WINDOW *menu_win);
void deleteKey(WINDOW *menu_win);

#endif // KEY_ENCRYPTION_HPP
