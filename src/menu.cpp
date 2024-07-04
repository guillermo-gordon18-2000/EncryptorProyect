#include "menu.hpp"

void displayMenu(WINDOW *menu_win, const vector<string>& recentEncryptedFiles, const vector<string>& recentDecryptedFiles) {
    werase(menu_win);  // Limpiar toda la ventana
    box(menu_win, 0, 0);  // Volver a dibujar el borde

    // Imprimir título del menú en color verde
    wattron(menu_win, COLOR_PAIR(4)); // Color verde
                                      // 
    attron(A_BOLD);  // Activar negrita
    mvwprintw(menu_win, 1, 2, "Bienvenido al programa de cifrado y descifrado");
    wattroff(menu_win, COLOR_PAIR(4));

    // Imprimir opciones del menú en color amarillo
    wattron(menu_win, COLOR_PAIR(5)); // Color amarillo
    mvwprintw(menu_win, 3, 2, "1. Cifrar archivo");
    wattroff(menu_win, COLOR_PAIR(5));

    if (!recentEncryptedFiles.empty()) {
        wattron(menu_win, COLOR_PAIR(4)); // Color para archivos cifrados recientes
        mvwprintw(menu_win, 4, 3, "Archivos cifrados recientes:");
        wattroff(menu_win, COLOR_PAIR(4));
        
        int line = 5;  // Línea vertical en donde iniciará
        int count = 0; // Contador para limitar el número de archivos mostrados  
     for (const auto& file : recentEncryptedFiles) {
        if (count >= 4) break; // Salir del bucle si ya se han mostrado 4 archivos
            wattron(menu_win, COLOR_PAIR(2)); // Color para archivos cifrados recientes
            mvwprintw(menu_win, line++, 5, "- %s", file.c_str());
            wattroff(menu_win, COLOR_PAIR(2));
            ++count; // Incrementar el contador
        }
    }

    wattron(menu_win, COLOR_PAIR(5)); // Color amarillo
    mvwprintw(menu_win, 9, 2, "2. Descifrar archivo");
    wattroff(menu_win, COLOR_PAIR(5));

    if (!recentDecryptedFiles.empty()) {
        wattron(menu_win, COLOR_PAIR(4)); // Color para archivos descifrados recientes
        mvwprintw(menu_win, 10, 3, "Archivos descifrados recientes:");
        wattroff(menu_win, COLOR_PAIR(4));
        
        int line = 11;
        int count = 0; // Contador para limitar el número de archivos mostrados  

        for (const auto& file : recentDecryptedFiles) {
       if (count >= 4) break; // Salir del bucle si ya se han mostrado 4 archivos
            wattron(menu_win, COLOR_PAIR(7)); // Color para archivos descifrados recientes
            mvwprintw(menu_win, line++, 5, "- %s", file.c_str());
            wattroff(menu_win, COLOR_PAIR(7));
            ++count; // Incrementar el contador
        }
    }

    wattron(menu_win, COLOR_PAIR(5)); // Color amarillo
    mvwprintw(menu_win, 16, 2, "3. Salir");
    mvwprintw(menu_win, 17, 2, "Seleccione una opción:");
    wattroff(menu_win, COLOR_PAIR(5));

    wrefresh(menu_win);  // Refrescar la ventana para mostrar el nuevo contenido
}

string selectFileFromList(WINDOW *menu_win, const vector<string>& files, const vector<string>& recentDecryptedFiles) {
    wattron(menu_win, COLOR_PAIR(5)); // Color verde
    mvwprintw(menu_win, 1, 2, "Archivos disponibles:");
    wattroff(menu_win, COLOR_PAIR(5)); // Quitar color verde

    int line = 2;
    for (size_t i = 0; i < files.size(); ++i) {
        // Verificar si el archivo está en la lista de archivos descifrados recientes
        bool isRecentlyDecrypted = std::find(recentDecryptedFiles.begin(), recentDecryptedFiles.end(), files[i]) != recentDecryptedFiles.end();

        if (isRecentlyDecrypted) {
            wattron(menu_win, COLOR_PAIR(6)); // Color azul para archivos descifrados recientemente
        } else {
            wattron(menu_win, COLOR_PAIR(4)); // Otro color para archivos normales
        }

        mvwprintw(menu_win, line++, 3, "%zu. %s", i + 1, files[i].c_str());

        if (isRecentlyDecrypted) {
            wattroff(menu_win, COLOR_PAIR(6)); // Quitar color azul
        } else {
            wattroff(menu_win, COLOR_PAIR(4)); // Quitar otro color
        }
    }

    wattron(menu_win, COLOR_PAIR(5)); // Color verde
    mvwprintw(menu_win, line++, 2, "Seleccione el número del archivo: ");
    wattroff(menu_win, COLOR_PAIR(5)); // Quitar color verde

    wrefresh(menu_win);

    int choice;
    echo(); 
    wscanw(menu_win, "%d", &choice);
    noecho();

    if (choice < 1 || choice > files.size()) {
        throw runtime_error("Opción inválida.");
    }
    return files[choice - 1];
}
