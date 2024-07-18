#ifndef KEY_MENU_HPP
#define KEY_MENU_HPP

#include <ncurses.h>
#include <vector>
#include <string>

void keyEncryptionMenu(WINDOW *menu_win, unsigned char *key, unsigned char *iv);

#endif // KEY_MENU_HPP
