// openssl_utils.hpp
#ifndef OPENSSL_UTILS_HPP
#define OPENSSL_UTILS_HPP

#include <openssl/err.h>
#include <ncurses.h>
#include <string>  // Incluir el encabezado <string>


//
//
// Usar el espacio de nombres std para que se reconozca 'std::string'
using std::string;

void handleErrors();

void printError(WINDOW *menu_win, const string& message);

#endif // OPENSSL_UTILS_HPP
