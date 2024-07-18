#include "keys/key_menu.hpp"
#include "keys/key_encryption.hpp"
#include <vector>
#include <string>
#include <locale>



void printKeyMenu(WINDOW *menu_win, int highlight) {
    const char *choices[] = {
        "1. Crear Llave",
        "2. Ver Llaves",
        "3. Editar Llave",
        "4. Eliminar Llave",
        "5. Regresar al menú principal"
    };
    int n_choices = sizeof(choices) / sizeof(char *);

    werase(menu_win);
    box(menu_win, 0, 0);
    mvwprintw(menu_win, 3, (30 - 24) / 2, "Menu de Cifrado de Llaves");

    mvwaddch(menu_win, 2, 1, ACS_ULCORNER);
    mvwaddch(menu_win, 2, 28, ACS_URCORNER);
    mvwaddch(menu_win, 4, 1, ACS_LLCORNER);
    mvwaddch(menu_win, 4, 28, ACS_LRCORNER);

    for (int i = 2; i < 28; i++) {
        mvwaddch(menu_win, 2, i, ACS_HLINE);
        mvwaddch(menu_win, 4, i, ACS_HLINE);
    }

    for (int i = 3; i < 4; i++) {
        mvwaddch(menu_win, i, 1, ACS_VLINE);
        mvwaddch(menu_win, i, 28, ACS_VLINE);
    }

    for (int i = 0; i < n_choices; ++i) {
        if (highlight == i + 1) {
            wattron(menu_win, A_REVERSE);
            mvwprintw(menu_win, 6 + i, 4, choices[i]);
            wattroff(menu_win, A_REVERSE);
        } else {
            mvwprintw(menu_win, 6 + i, 4, choices[i]);
        }
    }

    wattron(menu_win, COLOR_PAIR(5));
    mvwprintw(menu_win, 20, 3, "Seleccione una opción:");
    wattroff(menu_win, COLOR_PAIR(5));
    wrefresh(menu_win);
}

void keyEncryptionMenu(WINDOW *menu_win, unsigned char *key, unsigned char *iv) {
    setlocale(LC_ALL, "");

    int highlight = 1;
    int choice = 0;
    int c;

    while (1) {
        printKeyMenu(menu_win, highlight);
        c = wgetch(menu_win);

        // Manejo de teclas
        if (c == 'w' || c == 'W' || c == KEY_UP) {
            if (highlight == 1)
                highlight = 5;
            else
                --highlight;
        } else if (c == 's' || c == 'S' || c == KEY_DOWN) {
            if (highlight == 5)
                highlight = 1;
            else
                ++highlight;
        } else if (c == 10) { // Enter key
            choice = highlight;
        } else if (c == '\033') { // Secuencia de escape para teclas de flecha
            getch(); // Ignorar '['
            switch(getch()) {
                case 'A': // Flecha arriba
                    if (highlight == 1)
                        highlight = 5;
                    else
                        --highlight;
                    break;
                case 'B': // Flecha abajo
                    if (highlight == 5)
                        highlight = 1;
                    else
                        ++highlight;
                    break;
                // Otros casos no son necesarios para este menú
            }
        }

        if (choice != 0) { // Opción seleccionada
            switch (choice) {
                case 1:
                    createKey(menu_win);
                    break;
                case 2:
                    viewKeys(menu_win);
                    break;
                case 3:
                    editKey(menu_win);
                    break;
                case 4:
                    deleteKey(menu_win);
                    break;
                case 5:
                    mvwprintw(menu_win, 20, 1, "Regresando al menú principal...");
                    wrefresh(menu_win);
                    wgetch(menu_win);
                    return;  // Volver al menú principal
                default:
                    mvwprintw(menu_win, 18, 1, "Opción no válida. Intente de nuevo.");
                    wrefresh(menu_win);
                    wgetch(menu_win);
                    break;
            }
            choice = 0; // Resetear la elección
        }
    }
}

