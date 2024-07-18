#include "keys/key_encryption.hpp"
#include <iostream>
#include "mysql_utils.hpp"

#include <ncurses.h>
#include <vector>
#include <string>
#include <random>
#include <tuple>

#include <cstring>  // Agregar esta línea\


void encryptKey(const std::string &key) {
    // Implementación de la función para cifrar la llave
}

void decryptKey(const std::string &encryptedKey) {
    // Implementación de la función para descifrar la llave
}

std::vector<std::string> getRecentEncryptedKeys(int limit) {
    // Implementación de la función para obtener llaves cifradas recientes
    return std::vector<std::string>();
}

std::vector<std::string> getRecentDecryptedKeys(int limit) {
    // Implementación de la función para obtener llaves descifradas recientes
    return std::vector<std::string>();
}


std::string generateStrongKey(int length) {
    const char charset[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!@#$%^&*()_+";
    std::string result;
    std::uniform_int_distribution<> dist(0, sizeof(charset) - 2);
    std::default_random_engine rng(std::random_device{}());

    for (int i = 0; i < length; ++i) {
        result += charset[dist(rng)];
    }
    return result;
}



void createKey(WINDOW *menu_win) {
    werase(menu_win);
    box(menu_win, 0, 0);
    mvwprintw(menu_win, 1, 3, "Creando nueva llave...");

    mvwprintw(menu_win, 4, 3, "Ingrese el nombre de la llave: ");
    mvwaddch(menu_win, 5, 3, ACS_DIAMOND); // Diamante
    char key_name[256];
    echo();
    wgetnstr(menu_win, key_name, 255);
    noecho();

    std::string suggested_key;
    bool accept_key = false;

    while (!accept_key) {
        suggested_key = generateStrongKey(16);
        mvwprintw(menu_win, 6, 4, "Sugerencia de llave fuerte: ");
        mvwprintw(menu_win, 7, 4, "%s ", suggested_key.c_str()); // Mostrar la sugerencia
        mvwaddch(menu_win, 7, 3, ACS_DIAMOND); // Diamante al lado de la sugerencia

        mvwprintw(menu_win, 8, 4, "¿Te gusta esta llave? (s/n): ");
        wrefresh(menu_win);

        char response = wgetch(menu_win); // Esperar respuesta del usuario

        if (response == 's' || response == 'S') {
            accept_key = true; // Aceptar la llave
        } else {
            mvwprintw(menu_win, 9, 4, "Generando una nueva llave... "); // Mensaje
            wrefresh(menu_win);
        }
    }

    mvwprintw(menu_win, 10, 4, "Ingrese el valor de la llave: ");
    mvwaddch(menu_win, 11, 3, ACS_DIAMOND); // Diamante
    char key_value[256];
    echo();
    wgetnstr(menu_win, key_value, 255);
    noecho();

    std::string final_key_value = strlen(key_value) > 0 ? key_value : suggested_key;

    mvwprintw(menu_win, 12, 4, "Ingrese el tipo de página: ");
    mvwaddch(menu_win, 13, 3, ACS_DIAMOND); // Diamante
    mvwprintw(menu_win, 13, 4, " "); // Salto de línea
    char page_type[256];
    echo();
    wgetnstr(menu_win, page_type, 255);
    noecho();

    // Confirmar los parámetros antes de la inserción
    werase(menu_win);
    box(menu_win, 0, 0);
    mvwprintw(menu_win, 1, 3, "Confirmar Inserción");
    mvwprintw(menu_win, 2, 4, "Nombre de la llave: %s", key_name);
    mvwprintw(menu_win, 3, 4, "Valor de la llave: %s", final_key_value.c_str());
    mvwprintw(menu_win, 4, 4, "Tipo de página: %s", page_type);
    mvwprintw(menu_win, 5, 4, "¿Desea confirmar la inserción? (s/n): ");
    wrefresh(menu_win);

    char confirm_response = wgetch(menu_win); // Esperar respuesta del usuario

    if (confirm_response == 's' || confirm_response == 'S') {
        // Insertar la llave en la base de datos
        insertKey(key_name, final_key_value, "User", page_type); // Incluyendo el tipo de página
        mvwprintw(menu_win, 6, 4, "Llave insertada con éxito.");
    } else {
        mvwprintw(menu_win, 6, 4, "Inserción cancelada.");
    }

    wrefresh(menu_win);
    wgetch(menu_win);
}

void viewKeys(WINDOW *menu_win) {
    werase(menu_win);
    box(menu_win, 0, 0);
    mvwprintw(menu_win, 1, 1, "Mostrando llaves...");

    // Obtener las llaves
    std::vector<std::tuple<std::string, std::string, std::string, std::string>> keys = getKeys();
    int total_keys = keys.size();
    int current_line = 0; // Línea actual en la lista
    int max_display = 3; // Número máximo de llaves a mostrar

    while (true) {
        werase(menu_win); // Limpiar la ventana
        box(menu_win, 0, 0);
        mvwprintw(menu_win, 1, 1, "Mostrando llaves...");

        // Mostrar las llaves a partir de la línea 4
        for (int i = current_line; i < total_keys && i < current_line + max_display; ++i) {
            int line_offset = 4 + (i - current_line) * 5; // Línea inicial en Y = 4
            mvwprintw(menu_win, line_offset, 3, "Nombre: %s", std::get<0>(keys[i]).c_str());
            mvwprintw(menu_win, line_offset + 1, 3, "Valor: %s", std::get<1>(keys[i]).c_str());
            mvwprintw(menu_win, line_offset + 2, 3, "Creado por: %s", std::get<2>(keys[i]).c_str());
            mvwprintw(menu_win, line_offset + 3, 3, "Tipo de página: %s", std::get<3>(keys[i]).c_str());
            mvwprintw(menu_win, line_offset + 4, 3, "----------------------"); // Separador
        }

        wrefresh(menu_win); // Refrescar la ventana

        int ch = wgetch(menu_win); // Esperar a una entrada

        if (ch == 's' && current_line + max_display < total_keys) {
            current_line += max_display; // Mover hacia abajo
        } else if (ch == 'w' && current_line > 0) {
            current_line -= max_display; // Mover hacia arriba
        } else if (ch == 'q') { // Salir
            break;
        }

        // Limitar el desplazamiento para evitar salir del rango
        if (current_line < 0) {
            current_line = 0;
        } else if (current_line >= total_keys) {
            current_line = total_keys - (total_keys % max_display);
        }
    }
}

void editKey(WINDOW *menu_win) {
    werase(menu_win);
    box(menu_win, 0, 0);
    mvwprintw(menu_win, 1, 1, "Editando llave...");

    // Aquí puedes agregar la lógica para seleccionar y editar una llave.
    mvwprintw(menu_win, 2, 1, "Ingrese la llave a editar: ");
    char key_to_edit[256];
    echo(); // Permitir la entrada del usuario
    wgetnstr(menu_win, key_to_edit, 255);
    noecho(); // Desactivar la entrada del usuario
    // Editar la llave...

    mvwprintw(menu_win, 4, 1, "Llave editada con éxito.");
    wrefresh(menu_win);
    wgetch(menu_win); // Esperar a una entrada para continuar
}

void deleteKey(WINDOW *menu_win) {
    werase(menu_win);
    box(menu_win, 0, 0);
    mvwprintw(menu_win, 1, 4, "Eliminando llave...");

    // Aquí puedes agregar la lógica para seleccionar y eliminar una llave.
    mvwprintw(menu_win, 2, 1, "Ingrese la llave a eliminar: ");
    char key_to_delete[256];
    echo(); // Permitir la entrada del usuario
    wgetnstr(menu_win, key_to_delete, 255);
    noecho(); // Desactivar la entrada del usuario
    // Eliminar la llave...

    mvwprintw(menu_win, 4, 4, "Llave eliminada con éxito.");
    wrefresh(menu_win);
    wgetch(menu_win); // Esperar a una entrada para continuar
}
