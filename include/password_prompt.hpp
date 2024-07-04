#ifndef PASSWORD_PROMPT_HPP
#define PASSWORD_PROMPT_HPP

#include <ncurses.h>
#include <termios.h>  // Para termios, tcgetattr, tcsetattr, ECHO, TCSANOW
#include <unistd.h>   // Para STDIN_FILENO
#include <string>     // Para std::string
#include "key_derivation.hpp"
using namespace std;

void hidePasswordInput(WINDOW *menu_win, unsigned char* key, unsigned char* iv);

#endif // PASSWORD_PROMPT_HPP
