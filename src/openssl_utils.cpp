// openssl_utils.cpp
#include "openssl_utils.hpp"
#include <openssl/err.h>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <ncurses.h>

void handleErrors() {
    // Inicializar ncurses (si aún no está inicializado)
    if (!has_colors()) {
        initscr();
        start_color(); // Inicializar colores
        cbreak();
        noecho();
        keypad(stdscr, TRUE);

        // Inicializar colores
        init_pair(1, COLOR_RED, COLOR_BLACK);
        init_pair(2, COLOR_GREEN, COLOR_BLACK);
        init_pair(3, COLOR_YELLOW, COLOR_BLACK);
        init_pair(4, COLOR_BLUE, COLOR_BLACK);
        init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
    }

    // Crear una ventana para el menú
    int height = 25;
    int width = 60;
    int starty = (LINES - height) / 2;
    int startx = (COLS - width) / 2;
    WINDOW *menu_win = newwin(height, width, starty, startx);
    box(menu_win, 0, 0);
    refresh();

    // Borrar la ventana
    werase(menu_win);
    box(menu_win, 0, 0);

    // Imprimir todos los errores de la pila de OpenSSL
    unsigned long errCode;
    std::ostringstream oss;
    int line = 1;  // Línea inicial para mostrar los errores

    while ((errCode = ERR_get_error())) {
        char *errMsg = ERR_error_string(errCode, nullptr);
        oss << "OpenSSL error :  " << errCode << ", message: " << errMsg;

        // Mostrar el error en la ventana ncurses
        mvwprintw(menu_win, line++, 2, "%s", oss.str().c_str());

        // Limpiar el flujo de salida para el siguiente error
        oss.str("");
        oss.clear();
    }

    // Actualizar la ventana para mostrar los errores
    wrefresh(menu_win);

    // Esperar a que el usuario presione una tecla antes de abortar
    mvwprintw(menu_win, line++, 2, "Press any key to exit...");
    wrefresh(menu_win);
    wgetch(menu_win);

    // Eliminar la ventana antes de finalizar
    delwin(menu_win);

    // Abortamos el programa después de imprimir los errores
    abort();
}



void printError(WINDOW *menu_win, const string& message) {
    werase(menu_win);  // Limpiar toda la ventana
    box(menu_win, 0, 0);  // Volver a dibujar el borde

    wattron(menu_win, COLOR_PAIR(1)); // Color rojo
    mvwprintw(menu_win, 13, 4, "Error: %s", message.c_str());
    wattroff(menu_win, COLOR_PAIR(1));
    wrefresh(menu_win);
}


