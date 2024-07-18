#include "encryption.hpp"
#include "openssl_utils.hpp"
#include "file_utils.hpp"
#include "key_derivation.hpp"
#include "mysql_utils.hpp"
#include "colors.hpp"
#include "directories.hpp"
#include "time_utils.hpp"
#include "menu.hpp"
#include "password_prompt.hpp"
#include "keys/key_menu.hpp"



#include <openssl/err.h>
#include <openssl/aes.h>
#include <iostream>
#include <vector>
#include <cstring>
#include <unistd.h>
#include <algorithm>
#include <ncurses.h>
#include <ctime>
#include <fstream>
#include <cmath>
#include <iomanip>
#include <sstream>

#include <signal.h>
#include <stdlib.h>
#include <locale.h>

using namespace std;

WINDOW *menu_win; // Hacer la ventana global para acceso desde el manejador de señales

//INDOW *menu_win; // Hacer la ventana global para acceso desde el manejador de señales

void resizeHandler(int sig) {
    int height = 25;
    int width = 60;
    int starty, startx;
    getmaxyx(stdscr, starty, startx);
    starty = (starty - height) / 2;
    startx = (startx - width) / 2;

    // Reubicar y redimensionar la ventana del menú
    wresize(menu_win, height, width);
    mvwin(menu_win, starty, startx);
    box(menu_win, 0, 0);
    refresh();

    // Obtener los archivos más recientes desde la base de datos
    vector<string> recentEncryptedFiles; // = getRecentEncryptedFiles(30);
    vector<string> recentDecryptedFiles; // = getRecentDecryptedFiles(30);

    // Mostrar el menú
    displayEncrypFile(menu_win, recentEncryptedFiles, recentDecryptedFiles);
}


void processFile(WINDOW* menu_win, const std::string& filename, unsigned char* key, unsigned char* iv, std::vector<std::string>& recentEncryptedFiles, std::vector<std::string>& recentDecryptedFiles, int width) {
    werase(menu_win);
    box(menu_win, 0, 0);
    wattron(menu_win, COLOR_PAIR(5)); // Color amarillo

    if (isFileEncrypted(filename)) {
        mvwprintw(menu_win, 1, 2, "El archivo está cifrado. ¿Qué desea hacer?");
        mvwprintw(menu_win, 4, 4, "1. Descifrar");
    } else {
        mvwprintw(menu_win, 1, 2, "El archivo no está cifrado. ¿Qué desea hacer?");
        mvwprintw(menu_win, 4, 4, "1. Cifrar");
    }
    wattroff(menu_win, COLOR_PAIR(5)); // Quitar color amarillo
    wrefresh(menu_win);

    int choice;
    echo();
    mvwscanw(menu_win, 8, 2, "%d", &choice);
    noecho();

    if (choice == 1) {
        try {
            std::vector<unsigned char> plaintext = readFile(filename);
            size_t ciphertextSize = ((plaintext.size() + AES_BLOCK_SIZE) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE;
            std::vector<unsigned char> ciphertext(ciphertextSize);

            hidePasswordInput(menu_win, key, iv);  // Solicitar contraseña

            encrypt(plaintext.data(), plaintext.size(), key, iv, ciphertext.data());

            std::string ciphertextFilename = promptForFilename(menu_win, "Introduzca el nombre del archivo cifrado de salida", filename, "Cifrado");

            writeFile("data/encrypted/" + ciphertextFilename, ciphertext);
            if (remove(filename.c_str()) != 0) {
                perror("Error eliminando el archivo original");
            } else {
                logFileDeletion(menu_win, filename, "Eliminar", "data/encrypted/" + filename, "data/decrypted" + ciphertextFilename, std::vector<unsigned char>(key, key + sizeof(key)), "AES");
            }
      
            logFileOperation(menu_win, ciphertextFilename, "Cifrar", "data/encrypted/" + filename, "data/decrypted/" + ciphertextFilename, std::vector<unsigned char>(key, key + sizeof(key)), "AES");


            wattron(menu_win, COLOR_PAIR(6)); // Color azul
            mvwprintw(menu_win, 14, 9, "Archivo cifrado correctamente.");
            wattroff(menu_win, COLOR_PAIR(6));
            mvwhline(menu_win, 16, 1, '-', width - 2);

            if (recentEncryptedFiles.size() >= 4) {
                recentEncryptedFiles.erase(recentEncryptedFiles.begin());
            }
            recentEncryptedFiles.push_back(ciphertextFilename);

        } catch (const std::runtime_error& e) {
            werase(menu_win);
            box(menu_win, 0, 0);

            wattron(menu_win, COLOR_PAIR(1)); // Color rojo
            mvwprintw(menu_win, 10, 2, "Error al cifrar: %s", e.what());
            wattroff(menu_win, COLOR_PAIR(1));
            wrefresh(menu_win);
        }

    } else if (choice == 2) {
        try {
            std::vector<unsigned char> encrypted_data = readFile(filename);
            size_t decryptedSize = ((encrypted_data.size() + AES_BLOCK_SIZE - 1) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE;
            std::vector<unsigned char> decryptedtext(decryptedSize);

            hidePasswordInput(menu_win, key, iv);

            try {
                decrypt(encrypted_data.data(), encrypted_data.size(), key, iv, decryptedtext.data());
            } catch (const std::runtime_error &e) {
                werase(menu_win);
                box(menu_win, 0, 0);

                wattron(menu_win, COLOR_PAIR(1)); // Color rojo
                mvwprintw(menu_win, 10, 2, "Contraseña incorrecta o archivo corrupto.");
                mvwprintw(menu_win, 11, 2, "No se pudo descifrar el archivo.");
                wattroff(menu_win, COLOR_PAIR(1));
                wrefresh(menu_win);
                return;
            }

            std::string decryptedFilename = promptForFilename(menu_win, "Introduzca el nombre del archivo descifrado de salida", filename, "Descifrado");
            writeFile("data/decrypted" + decryptedFilename, decryptedtext);

            if (remove(filename.c_str()) != 0) {
                perror("Error eliminando el archivo original");
            } else {
                logFileDeletion(menu_win, filename, "Eliminar", "data/decrypted" + filename, "data/encrypted" + decryptedFilename, std::vector<unsigned char>(key, key + sizeof(key)), "AES");
            }

            logFileOperation(menu_win, decryptedFilename, "Descifrar", "data/decrypted" + filename, "data/encrypted" + decryptedFilename, std::vector<unsigned char>(key, key + sizeof(key)), "AES");

            wattron(menu_win, COLOR_PAIR(6)); // Color azul
            mvwprintw(menu_win, 14, 9, "Archivo descifrado correctamente.");
            wattroff(menu_win, COLOR_PAIR(6));
            mvwhline(menu_win, 16, 1, '-', width - 2);

            if (recentDecryptedFiles.size() >= 4) {
                recentDecryptedFiles.erase(recentDecryptedFiles.begin());
            }
            recentDecryptedFiles.push_back(decryptedFilename);

        } catch (const std::runtime_error &e) {
            werase(menu_win);
            box(menu_win, 0, 0);

            wattron(menu_win, COLOR_PAIR(1)); // Color rojo
            mvwprintw(menu_win, 10, 2, "Error al descifrar: %s", e.what());
            wattroff(menu_win, COLOR_PAIR(1));
            wrefresh(menu_win);
        }

    } else {
        werase(menu_win);
        box(menu_win, 0, 0);
        wattron(menu_win, COLOR_PAIR(5)); // Color amarillo
        mvwprintw(menu_win, 1, 2, "Opción no válida.");
        wattroff(menu_win, COLOR_PAIR(5)); // Quitar color amarillo
        wrefresh(menu_win);
    }
}

void cleanupNcurses(WINDOW *menu_win) {
    delwin(menu_win);
    endwin();
    refresh();
}


void setupSignalHandler() {
    struct sigaction sa;
    sa.sa_handler = resizeHandler;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGWINCH, &sa, NULL);
}


WINDOW* createMenuWindow(int height, int width) {
    int starty = (LINES - height) / 2;
  
  int startx = (COLS - width) / 2;
    WINDOW *menu_win = newwin(height, width, starty, startx);

    box(menu_win, 0, 0);
    refresh();
    return menu_win;
}

void processEncryptedFiles(WINDOW *menu_win, const vector<string>& recentEncryptedFiles, const vector<string>& recentDecryptedFiles, unsigned char key[], unsigned char iv[], int width) {
    
werase(menu_win);  // Limpiar toda la ventana
                box(menu_win, 0, 0);  // Volver a dibujar el borde
  try {
        auto files = listFiles("data/decrypted/");
        string plaintextFilename = selectFileFromList(menu_win, files, recentEncryptedFiles);

        vector<unsigned char> plaintext = readFile("data/decrypted/" + plaintextFilename);

        size_t ciphertextSize = ((plaintext.size() + AES_BLOCK_SIZE) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE;
        vector<unsigned char> ciphertext(ciphertextSize);

        hidePasswordInput(menu_win, key, iv);

        encrypt(plaintext.data(), plaintext.size(), key, iv, ciphertext.data());

        string ciphertextFilename = promptForFilename(menu_win, "Introduzca el nombre del archivo cifrado de salida", plaintextFilename, "Cifrado");

        writeFile("data/encrypted/" + ciphertextFilename, ciphertext);

        // Crear una copia mutable de recentEncryptedFiles para modificarla
        vector<string> mutableRecentEncryptedFiles(recentEncryptedFiles.begin(), recentEncryptedFiles.end());

        logFileOperation(menu_win, ciphertextFilename, "Cifrar", "data/encrypted/" + plaintextFilename, "data/encrypted/" + ciphertextFilename, vector<unsigned char>(key, key + 32), "AES");

        remove(("data/decrypted/" + plaintextFilename).c_str());
        logFileDeletion(menu_win, plaintextFilename, "Eliminar", "data/encrypted/" + plaintextFilename, "data/encrypted/" + ciphertextFilename, vector<unsigned char>(key, key + 32), "AES");

        wattron(menu_win, COLOR_PAIR(6));
        mvwprintw(menu_win, 14, 9, "Archivo cifrado correctamente.");
        wattroff(menu_win, COLOR_PAIR(6));
        mvwhline(menu_win, 16, 1, '-', width - 2);

        if (mutableRecentEncryptedFiles.size() >= 4) {
            mutableRecentEncryptedFiles.erase(mutableRecentEncryptedFiles.begin());
        }
        mutableRecentEncryptedFiles.push_back(ciphertextFilename);

        // Actualizar recentEncryptedFiles con la nueva lista mutable
        // recuerda mantener el original como constante
        // recentEncryptedFiles = mutableRecentEncryptedFiles;

    } catch (const runtime_error& e) {
        werase(menu_win);
        box(menu_win, 0, 0);
        wattron(menu_win, COLOR_PAIR(1));
        mvwprintw(menu_win, 10, 2, "Error al cifrar: %s", e.what());
        wattroff(menu_win, COLOR_PAIR(1));
        wrefresh(menu_win);
    }
}

void processDecryptedFiles(WINDOW *menu_win, const vector<string>& recentEncryptedFiles, vector<string>& recentDecryptedFiles, unsigned char key[], unsigned char iv[], int width) {
    werase(menu_win);  // Limpiar toda la ventana
    box(menu_win, 0, 0);  // Volver a dibujar el borde

    try {
        auto files = listFiles("data/encrypted/");
        string ciphertextFilename = selectFileFromList(menu_win, files, recentEncryptedFiles);
        vector<unsigned char> ciphertext = readFile("data/encrypted/" + ciphertextFilename);
        size_t decryptedSize = ciphertext.size();
        vector<unsigned char> decrypted(decryptedSize);
        hidePasswordInput(menu_win, key, iv);
        decrypt(ciphertext.data(), ciphertext.size(), key, iv, decrypted.data());
        string decryptedFilename = promptForFilename(menu_win, "Introduzca el nombre del archivo descifrado de salida", ciphertextFilename, "Descifrado");
        writeFile("data/decrypted/" + decryptedFilename, decrypted);
        logFileDeletion(menu_win, ciphertextFilename, "Eliminar", "data/encrypted/" + ciphertextFilename, "data/decrypted/" + decryptedFilename, vector<unsigned char>(key, key + 32), "AES");
        if (recentDecryptedFiles.size() >= 4) {
            recentDecryptedFiles.erase(recentDecryptedFiles.begin()); // Elimina el más antiguo
        }
        recentDecryptedFiles.push_back(decryptedFilename);
        logFileOperation(menu_win, decryptedFilename, "Descifrar", "data/encrypted/" + ciphertextFilename, "data/decrypted/" + decryptedFilename, vector<unsigned char>(key, key + 32), "AES");
        wattron(menu_win, COLOR_PAIR(6));
        mvwprintw(menu_win, 14, 9, "Archivo descifrado correctamente.");
        wattroff(menu_win, COLOR_PAIR(6));
        mvwhline(menu_win, 16, 1, '-', width - 2);

    } catch (const runtime_error& e) {
        werase(menu_win);
        box(menu_win, 0, 0);
        wattron(menu_win, COLOR_PAIR(1));
        mvwprintw(menu_win, 10, 2, "Error al descifrar: %s", e.what());
        wattroff(menu_win, COLOR_PAIR(1));
        wrefresh(menu_win);
    }
}


void encryptingFileMenu(WINDOW* menu_win, unsigned char* key, unsigned char* iv, int argc, char* argv[]) {
    // Obtener los archivos más recientes desde la base de datos
    std::vector<std::string> recentEncryptedFiles = getRecentEncryptedFiles(30);
    std::vector<std::string> recentDecryptedFiles = getRecentDecryptedFiles(30);

    if (argc == 2) {
        std::string filename = argv[1];
        processFile(menu_win, filename, key, iv, recentEncryptedFiles, recentDecryptedFiles, 60);
        wrefresh(menu_win);
        getch();
    } else {
        int choice = 0;
        while (choice != 3) {
            if (!recentDecryptedFiles.empty()) {
                wattron(menu_win, COLOR_PAIR(4)); // Color para archivos descifrados recientes
                mvwprintw(menu_win, 14, 3, "Archivos descifrados recientes:");
                wattroff(menu_win, COLOR_PAIR(4));
                int line = 15;
                int count = 0; // Contador para limitar el número de archivos mostrados
                for (const auto& file : recentDecryptedFiles) {
                    if (count >= 4) break; // Salir del bucle si ya se han mostrado 4 archivos
                    wattron(menu_win, COLOR_PAIR(7)); // Color para archivos descifrados recientes
                    mvwprintw(menu_win, line++, 5, "- %s", file.c_str());
                    wattroff(menu_win, COLOR_PAIR(7));
                    ++count; // Incrementar el contador
                }
            }
            displayEncrypFile(menu_win, recentEncryptedFiles, recentDecryptedFiles);
            wrefresh(menu_win);
            choice = wgetch(menu_win) - '0';  // Convertir carácter a número
            switch (choice) {
                case 1: {
                    processEncryptedFiles(menu_win, recentEncryptedFiles, recentDecryptedFiles, key, iv, COLS);
                    break;
                }
                case 2: {
                    processDecryptedFiles(menu_win, recentEncryptedFiles, recentDecryptedFiles, key, iv, COLS);
                    break;
                }
                case 3:
                    mvwprintw(menu_win, 20, 1, "Saliendo del programa...");
                    break;
                default:
                    mvwprintw(menu_win, 20, 1, "Opción no válida. Intente de nuevo.");
                    break;
            }
            wrefresh(menu_win);
            wgetch(menu_win);  // Esperar a una entrada para continuar
        }
    }
}



void encryptingURLMenu(WINDOW* menu_win) {
    // Lógica para el cifrado de URLs
    mvwprintw(menu_win, 1, 1, "Menu de cifrado de URLs");
    wrefresh(menu_win);
    getch();  // Esperar a una entrada para continuar
}

void printMenu(WINDOW *menu_win, int highlight) {
    const char *choices[] = {
        "1. Menu de Archivos Encriptados",
        "2. Menu de Cifrado de Llaves",
        "3. Menu de Cifrado de URLs",
        "4. Salir"
    };
    int n_choices = sizeof(choices) / sizeof(char *);

    werase(menu_win);  // Limpiar toda la ventana
    box(menu_win, 0, 0);  // Volver a dibujar el borde

    wattron(menu_win, COLOR_PAIR(4)); // Color verde
    wattron(menu_win, A_BOLD);  // Activar negrita
    mvwprintw(menu_win, 1, 3, "Bienvenido al programa de cifrado ");
    wattroff(menu_win, A_BOLD);
    wattroff(menu_win, COLOR_PAIR(4));

    for (int i = 0; i < n_choices; ++i) {
        if (highlight == i + 1) {
            wattron(menu_win, A_REVERSE);
            mvwprintw(menu_win, 4 + i, 3, choices[i]);
            wattroff(menu_win, A_REVERSE);
        } else {
            mvwprintw(menu_win, 4 + i, 3, choices[i]);
        }
    }

    wattron(menu_win, COLOR_PAIR(5)); // Color amarillo
    mvwprintw(menu_win, 21, 3, "Seleccione una opción:");
    wattroff(menu_win, COLOR_PAIR(5));
}

int main(int argc, char* argv[]) {
    unsigned char key[32];  // 256 bits
    unsigned char iv[16];   // 128 bits
    createDirectories();

    initscr();
    start_color(); // Inicializar colores
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);

    int height = 25;
    int width = 47;
    int starty = (LINES - height) / 2;
    int startx = (COLS - width) / 2;
    WINDOW *menu_win = newwin(height, width, starty, startx);

    wbkgd(menu_win, COLOR_PAIR(1));
    box(menu_win, 0, 0);
    refresh();

    initializeColors();
    setupSignalHandler();

    int highlight = 1;
    int choice = 0;
    int c;

    while (1) {
        printMenu(menu_win, highlight);
        c = wgetch(menu_win);

        // Manejo de teclas
        if (c == 'w' || c == 'W' || c == KEY_UP) {
            if (highlight == 1)
                highlight = 4;
            else
                --highlight;
        } else if (c == 's' || c == 'S' || c == KEY_DOWN) {
            if (highlight == 4)
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
                        highlight = 4;
                    else
                        --highlight;
                    break;
                case 'B': // Flecha abajo
                    if (highlight == 4)
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
                    encryptingFileMenu(menu_win, key, iv, argc, argv);
                    break;
                case 2:
                    keyEncryptionMenu(menu_win, key, iv);
                    break;
                case 3:
                    encryptingURLMenu(menu_win);
                    break;
                case 4:
                    mvwprintw(menu_win, 20, 1, "Saliendo del programa...");
                    wrefresh(menu_win);
                    wgetch(menu_win);
                    endwin();
                    return 0;
                default:
                    mvwprintw(menu_win, 20, 1, "Opción no válida. Intente de nuevo.");
                    break;
            }
            choice = 0; // Resetear la elección
        }
    }

    delwin(menu_win);
    endwin();
    return 0;
}
