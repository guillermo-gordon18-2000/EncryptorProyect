#include "encryption.hpp"
#include "openssl_utils.hpp"
#include <openssl/err.h>
#include <openssl/aes.h>
#include <iostream>
#include <vector>
#include <cstring>
#include "file_utils.hpp"
#include "key_derivation.hpp"
#include <termios.h>
#include <unistd.h>
#include "mysql_utils.hpp"
#include <algorithm>
#include <string>
#include <ncurses.h>

using namespace std;

// Funciones para manejo de colores en la consola
const string reset = "\033[0m";
const string red = "\033[31m";
const string green = "\033[32m";
const string yellow = "\033[33m";
const string blue = "\033[34m";
const string magenta = "\033[35m";
const string cyan = "\033[36m";
const string bold = "\033[1m";

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
        
        int line = 5;
        for (const auto& file : recentEncryptedFiles) {
            wattron(menu_win, COLOR_PAIR(2)); // Color para archivos cifrados recientes
            mvwprintw(menu_win, line++, 5, "- %s", file.c_str());
            wattroff(menu_win, COLOR_PAIR(2));
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
        for (const auto& file : recentDecryptedFiles) {
            wattron(menu_win, COLOR_PAIR(7)); // Color para archivos descifrados recientes
            mvwprintw(menu_win, line++, 5, "- %s", file.c_str());
            wattroff(menu_win, COLOR_PAIR(7));
        }
    }

    wattron(menu_win, COLOR_PAIR(5)); // Color amarillo
    mvwprintw(menu_win, 16, 2, "3. Salir");
    mvwprintw(menu_win, 17, 2, "Seleccione una opción:");
    wattroff(menu_win, COLOR_PAIR(5));

    wrefresh(menu_win);  // Refrescar la ventana para mostrar el nuevo contenido
}

string promptForFilename(WINDOW *menu_win, const string& prompt) {
    werase(menu_win);  // Limpiar toda la ventana
    box(menu_win, 0, 0);  // Volver a dibujar el borde

    char filename[256];
     // mvwprintw(menu_win, 12, 1, "Nombre del archivo:  ");
    // Imprimir el prompt en la posición correcta
   mvwprintw(menu_win, 14, 2, "%s: ", prompt.c_str());
   mvwprintw(menu_win, 15, 2, ":");

    echo();
    wgetnstr(menu_win, filename, sizeof(filename) - 1);
    noecho();

    // Imprimir el nombre del archivo un renglón abajo del prompt
    mvwprintw(menu_win, 16, 1, "Nombre del archivo: %s", filename);

    wrefresh(menu_win);  // Actualizar la ventana de ncurses si es necesario

    return string(filename);
}

string selectFileFromList(WINDOW *menu_win, const vector<string>& files) {
      wattron(menu_win, COLOR_PAIR(5)); // Color verde
 
  mvwprintw(menu_win, 1, 2, "Archivos disponibles:");
    wattron(menu_win, COLOR_PAIR(5)); // Color verde
 
  int line = 2;
    for (size_t i = 0; i < files.size(); ++i) {
         wattron(menu_win, COLOR_PAIR(4)); // Color verde

        mvwprintw(menu_win, line++, 3, "%zu. %s", i + 1, files[i].c_str());
           wattron(menu_win, COLOR_PAIR(4)); // Color verde

    }
     wattron(menu_win, COLOR_PAIR(5)); // Color verde

    mvwprintw(menu_win, line++, 2, "Seleccione el número del archivo: ");
 wattron(menu_win, COLOR_PAIR(5)); // Color verde

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

void hidePasswordInput(WINDOW *menu_win, unsigned char* key, unsigned char* iv) {
      werase(menu_win);  // Limpiar toda la ventana
      box(menu_win, 0, 0);  // Volver a dibujar el borde

  termios tty;
    tcgetattr(STDIN_FILENO, &tty);
    termios tty_old = tty;
    tty.c_lflag &= ~ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &tty);

    string password;
    char ch;
    int x = 2; // Posición de inicio para la contraseña en la ventana
    int y = 13; // Línea en la ventana para la entrada de la contraseña
    
    mvwprintw(menu_win, y, x, "Introduce la contraseña: "); // Verde
    wrefresh(menu_win);

    while (true) {
        ch = wgetch(menu_win);
        if (ch == '\n' || ch == '\r') {
            break;
        } else if (ch == 127 || ch == '\b') {  // Handle backspace
            if (!password.empty()) {
                password.pop_back();
                mvwprintw(menu_win, y, x + password.size() + 27, " "); // Borrar el último asterisco
                mvwprintw(menu_win, y, x + password.size() + 27, "\b \b"); // Mover el cursor hacia atrás
                wrefresh(menu_win);
            }
        } else {
            password.push_back(ch);
            mvwprintw(menu_win, y, x + password.size() + 26, "*"); // Mostrar asterisco
            wrefresh(menu_win);
        }
    }

    tcsetattr(STDIN_FILENO, TCSANOW, &tty_old);

    deriveKeyAndIV(password, key, iv);
}




void printError(WINDOW *menu_win, const string& message) {
    werase(menu_win);  // Limpiar toda la ventana
    box(menu_win, 0, 0);  // Volver a dibujar el borde

    wattron(menu_win, COLOR_PAIR(1)); // Color rojo
    mvwprintw(menu_win, 13, 1, "Error: %s", message.c_str());
    wattroff(menu_win, COLOR_PAIR(1));
    wrefresh(menu_win);
}

void moveFileToData(const std::string& filename) {

    std::string sourcePath = "./" + filename;
    std::string destinationPath = "./data/" + filename;

    if (std::rename(sourcePath.c_str(), destinationPath.c_str()) != 0) {
        throw std::runtime_error("Error al mover el archivo a la carpeta data.");
    }
}

int main(int argc, char* argv[]) {
    unsigned char key[32];  // 256 bits
    unsigned char iv[16];   // 128 bits

    // Inicializar ncurses
    initscr();
    start_color(); // Inicializar colores
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    // Crear una ventana para el menú
    int height = 25;
    int width = 60;
    int starty = (LINES - height) / 2;
    int startx = (COLS - width) / 2;
    WINDOW *menu_win = newwin(height, width, starty, startx);
    box(menu_win, 0, 0);
    refresh();

    // Definir pares de colores
    init_pair(1, COLOR_RED, COLOR_BLACK);     // Color rojo para errores
    init_pair(2, COLOR_CYAN, COLOR_BLACK);    // Color cian para archivos cifrados recientes
    init_pair(3, COLOR_WHITE, COLOR_BLACK);   // Color blanco para archivos descifrados recientes
    init_pair(4, COLOR_GREEN, COLOR_BLACK);   // Color verde para el mensaje de bienvenida
    init_pair(5, COLOR_YELLOW, COLOR_BLACK);  // Color amarillo para las opciones del menú
    init_pair(6, COLOR_BLUE, COLOR_BLACK);    // Color azul para los nombres de archivos cifrados
    init_pair(7, COLOR_MAGENTA, COLOR_BLACK); // Color magenta para los nombres de archivos descifrados

    // Obtener los archivos más recientes desde la base de datos
    vector<string> recentEncryptedFiles = getRecentEncryptedFiles(4);
    vector<string> recentDecryptedFiles = getRecentDecryptedFiles(4);
    
    int choice = 0;
    while (choice != 3) {
        displayMenu(menu_win, recentEncryptedFiles, recentDecryptedFiles);
        wrefresh(menu_win);

        choice = wgetch(menu_win) - '0';  // Convertir carácter a número

        switch (choice) {
            case 1: {
                werase(menu_win);  // Limpiar toda la ventana
                box(menu_win, 0, 0);  // Volver a dibujar el borde

                try {
                    auto files = listFiles("data");
                    string plaintextFilename = selectFileFromList(menu_win, files);

                    std::vector<unsigned char> plaintext = readFile("data/" + plaintextFilename);

                    size_t ciphertextSize = ((plaintext.size() + AES_BLOCK_SIZE) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE;
                    std::vector<unsigned char> ciphertext(ciphertextSize);

                    hidePasswordInput(menu_win,key, iv);  // Solicitar contraseña

                    encrypt(plaintext.data(), plaintext.size(), key, iv, ciphertext.data());

                    std::string ciphertextFilename = promptForFilename(menu_win, "Introduzca el nombre del archivo cifrado de salida");

                    writeFile("data/" + ciphertextFilename, ciphertext);

                 
                    // Actualizar operación de archivo en la base de datos
                    logFileOperation(menu_win, ciphertextFilename, "Cifrar", "data/" + plaintextFilename, "data/" + ciphertextFilename, std::vector<unsigned char>(key, key + sizeof(key)), "AES");

               

                    // Eliminar archivo original
                    remove(("data/" + plaintextFilename).c_str());
                    logFileDeletion(menu_win,plaintextFilename);

                    wattron(menu_win, COLOR_PAIR(6)); // Color azul
                    mvwprintw(menu_win, 14, 9, "Archivo cifrado correctamente.");
                    wattroff(menu_win, COLOR_PAIR(6));
                    mvwhline(menu_win, 16, 1, '-', width - 2); // Línea horizontal en la fila 9 (0-indexed)


                    // Actualizar archivos cifrados recientes
                    if (recentEncryptedFiles.size() >= 4) {
                        recentEncryptedFiles.erase(recentEncryptedFiles.begin()); // Elimina el más antiguo
                    }
                    recentEncryptedFiles.push_back(ciphertextFilename);

                } catch (const runtime_error& e) {
                      werase(menu_win);  // Limpiar toda la ventana
                     box(menu_win, 0, 0);  // Volver a dibujar el borde


                    // Manejar el error al descifrar (contraseña incorrecta, etc.)
                      wattron(menu_win, COLOR_PAIR(1)); // Color rojo
                     mvwprintw(menu_win, 10, 2, "Error al cifrar: %s", e.what());
                     wattroff(menu_win, COLOR_PAIR(2));
                     wrefresh(menu_win);  // Actualizar la ventana de ncurses si es necesario


                    //printError(menu_win, "Error al cifrar: " + string(e.what()));
                }
                break;
            }
          case 2: {
    werase(menu_win);  // Limpiar toda la ventana
    box(menu_win, 0, 0);  // Volver a dibujar el borde

    try {
        auto files = listFiles("data");
        string ciphertextFilename = selectFileFromList(menu_win, files);

        vector<unsigned char> encrypted_data = readFile("data/" + ciphertextFilename);

        size_t decryptedSize = ((encrypted_data.size() + AES_BLOCK_SIZE - 1) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE;
        vector<unsigned char> decryptedtext(decryptedSize);

        // Solicitar contraseña y descifrar
        hidePasswordInput(menu_win, key, iv);  // Solicitar contraseña

        try {
            decrypt(encrypted_data.data(), encrypted_data.size(), key, iv, decryptedtext.data());
        } catch (const std::runtime_error &e) {
            // Manejar el error de descifrado aquí
            werase(menu_win);  // Limpiar toda la ventana
            box(menu_win, 0, 0);  // Volver a dibujar el borde

            wattron(menu_win, COLOR_PAIR(1)); // Color rojo
            mvwprintw(menu_win, 10, 2, "Contraseña incorrecta o archivo corrupto.");
            mvwprintw(menu_win, 11, 2, "No se pudo descifrar el archivo.");
            wattroff(menu_win, COLOR_PAIR(1));
            wrefresh(menu_win);  // Actualizar la ventana de ncurses si es necesario
            break;  // Salir del caso 2 ya que el descifrado falló
        }

        string decryptedFilename = promptForFilename(menu_win, "Introduzca el nombre del archivo descifrado de salida");
        writeFile("data/" + decryptedFilename, decryptedtext);

        // Actualizar operación de archivo en la base de datos
        logFileOperation(menu_win, decryptedFilename, "Descifrar", "data/" + ciphertextFilename, "data/" + decryptedFilename, std::vector<unsigned char>(key, key + sizeof(key)), "AES");

        wattron(menu_win, COLOR_PAIR(6)); // Color azul
        mvwprintw(menu_win, 14, 9, "Archivo descifrado correctamente.");
        wattroff(menu_win, COLOR_PAIR(6));
        // Dibujar el marco
        mvwhline(menu_win, 16, 1, '-', width - 2); // Línea horizontal en la fila 9 (0-indexed)
        // Actualizar archivos descifrados recientes
        if (recentDecryptedFiles.size() >= 4) {
            recentDecryptedFiles.erase(recentDecryptedFiles.begin()); // Elimina el más antiguo
        }
        recentDecryptedFiles.push_back(decryptedFilename);

    } catch (const runtime_error &e) {
        werase(menu_win);  // Limpiar toda la ventana
        box(menu_win, 0, 0);  // Volver a dibujar el borde

        // Manejar el error al descifrar (contraseña incorrecta, etc.)
        wattron(menu_win, COLOR_PAIR(1)); // Color rojo
        mvwprintw(menu_win, 10, 2, "Error al descifrar: %s", e.what());
        wattroff(menu_win, COLOR_PAIR(1));
        wrefresh(menu_win);  // Actualizar la ventana de ncurses si es necesario
    }
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

    // Limpiar y cerrar ncurses
    delwin(menu_win);
    endwin();
    refresh();

    return 0;
}
