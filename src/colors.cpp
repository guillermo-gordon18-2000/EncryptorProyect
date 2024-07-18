// colors.hpp
#ifndef COLORS_HPP
#define COLORS_HPP

#include <ncurses.h>
#include <string>  


const std::string reset = "\033[0m";
const std::string red = "\033[31m";
const std::string green = "\033[32m";
const std::string yellow = "\033[33m";
const std::string blue = "\033[34m";
const std::string magenta = "\033[35m";
const std::string cyan = "\033[36m";
const std::string bold = "\033[1m";

void initializeColors() {
    init_pair(1, COLOR_RED, COLOR_BLACK);     // Color rojo para errores
    init_pair(2, COLOR_CYAN, COLOR_BLACK);    // Color cian para archivos cifrados recientes
    init_pair(3, COLOR_WHITE, COLOR_BLACK);   // Color blanco para archivos descifrados recientes
    init_pair(4, COLOR_GREEN, COLOR_BLACK);   // Color verde para el mensaje de bienvenida
    init_pair(5, COLOR_YELLOW, COLOR_BLACK);  // Color amarillo para las opciones del menú
    init_pair(6, COLOR_BLUE, COLOR_BLACK);    // Color azul para los nombres de archivos cifrados
    init_pair(7, COLOR_MAGENTA, COLOR_BLACK); // Color magenta para los nombres de archivos descifrados
}

#endif
