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

using namespace std;


string promptForFilename(WINDOW *menu_win, const string &prompt, const string &originalFilename, const string &method) {
    string suggestedFilename = originalFilename + "_" + method + "_" + getCurrentDate() + ".txt";

    werase(menu_win);
    box(menu_win, 0, 0);

    wattron(menu_win, COLOR_PAIR(5)); // Color amarillo
    mvwprintw(menu_win, 1, 2, "%s", prompt.c_str());
    wattroff(menu_win, COLOR_PAIR(5)); // Color amarillo

    // Opción 1: Usar el mismo nombre de archivo
    mvwprintw(menu_win, 4, 2, "1. Usar el mismo nombre de archivo:");
    if (originalFilename.length() > 35) {
        // Si el nombre original es muy largo, truncarlo para la impresión
        string truncatedName = originalFilename.substr(0, 14);
        wattron(menu_win, COLOR_PAIR(4)); // Color verde
       mvwprintw(menu_win, 6, 4, "%s...", truncatedName.c_str());
        wattroff(menu_win, COLOR_PAIR(4)); // Color verde
    } else {
        wattron(menu_win, COLOR_PAIR(4)); // Color verde
        mvwprintw(menu_win, 5, 4, "%s", originalFilename.c_str());
        wattroff(menu_win, COLOR_PAIR(4)); // Color Verde
    }


 size_t pos;
    pos = suggestedFilename.find(".txt");
    if (pos != string::npos) {
        suggestedFilename.insert(pos, "_*");
    }

    wattron(menu_win, COLOR_PAIR(5)); // Color amarillo
    // Opción 2: Cambiar nombre de archivo
    mvwprintw(menu_win, 6, 2, "2. Cambiar nombre de archivo");
    wattroff(menu_win, COLOR_PAIR(5)); // Color amarillo

    // Opción 3: Sugerir un nuevo nombre
    wattron(menu_win, COLOR_PAIR(5)); // Color amarillo
    mvwprintw(menu_win, 7, 2, "3. Sugerir un nuevo nombre:");
    wattroff(menu_win, COLOR_PAIR(5)); // Color amarillo

    if (originalFilename.length() > 17) {
        // Truncar el nombre original para la concatenación sugerida
        string truncatedName = originalFilename.substr(0, 7);
        if (originalFilename.find(".txt") != string::npos) {
            // El nombre original ya tiene extensión ".txt"
            suggestedFilename = truncatedName + "_" + method + "_" + getCurrentDate()+ "_" + getCurrentTime() + ".txt";
        } else {
            // El nombre original no tiene extensión ".txt"
            suggestedFilename = truncatedName + "_" + method + "_" + getCurrentDate();
        }
    } else {
        if (originalFilename.find(".txt") != string::npos) {
            // El nombre original ya tiene extensión ".txt"
            suggestedFilename = originalFilename + "_" + method + "_" + getCurrentDate()+ "_" + getCurrentTime() + ".txt";
        } else {
            // El nombre original no tiene extensión ".txt"
            suggestedFilename = originalFilename + "_" + method + "_" + getCurrentDate();
        }
    }

    wattron(menu_win, COLOR_PAIR(4)); // Color amarillo
    mvwprintw(menu_win, 8, 6, "%s", suggestedFilename.c_str());
    wattroff(menu_win, COLOR_PAIR(4)); // Color amarillo

    wrefresh(menu_win);

    int choice;
    echo();
    mvwscanw(menu_win, 10, 2, "%d", &choice);
    noecho();

    string filename;
     //string pos;

    switch (choice) {
        case 1:
          pos = originalFilename.find(".txt");
            if (pos != string::npos) {
                filename = originalFilename.substr(0, pos) + "_*" + originalFilename.substr(pos);
            } else {
                filename = originalFilename + "_*";
            }           
       break;
        case 2:
            mvwprintw(menu_win, 10, 2, "Ingrese el nuevo nombre de archivo: ");
            char newFilename[256];
            echo();
            mvwgetnstr(menu_win, 11, 2, newFilename, 255);
            noecho();
            filename = string(newFilename);
            break;
        case 3:
            filename = suggestedFilename;
            break;
        default:
            filename = originalFilename;
            break;
    }

    return filename;
}







void printError(WINDOW *menu_win, const string& message) {
    werase(menu_win);  // Limpiar toda la ventana
    box(menu_win, 0, 0);  // Volver a dibujar el borde

    wattron(menu_win, COLOR_PAIR(1)); // Color rojo
    mvwprintw(menu_win, 13, 1, "Error: %s", message.c_str());
    wattroff(menu_win, COLOR_PAIR(1));
    wrefresh(menu_win);
}



int main(int argc, char* argv[]) {
    unsigned char key[32];  // 256 bits
    unsigned char iv[16];   // 128 bits


     createDirectories();

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
    vector<string> recentEncryptedFiles = getRecentEncryptedFiles(30);
    vector<string> recentDecryptedFiles = getRecentDecryptedFiles(30);

   if (argc == 2) {
        string filename = argv[1];

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

            // Actualizar operación de archivo en la base de datos
            logFileOperation(menu_win, ciphertextFilename, "Cifrar", "data/encrypted/" + filename, "data/encrypted/" + ciphertextFilename, std::vector<unsigned char>(key, key + sizeof(key)), "AES");

            // Eliminar archivo original
         // Eliminar archivo original
    if (remove(filename.c_str()) != 0) {
        // Si ocurre un error al eliminar el archivo, lo manejamos aquí
        perror("Error eliminando el archivo original");
    } else {
        logFileDeletion(menu_win, filename, "Cifrar", "data/encrypted/" + filename, "data/encrypted" + ciphertextFilename, std::vector<unsigned char>(key, key + sizeof(key)), "AES");

    }

        //    logFileDeletion(menu_win, filename);

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

            wattron(menu_win, COLOR_PAIR(1)); // Color rojo
            mvwprintw(menu_win, 10, 2, "Error al cifrar: %s", e.what());
            wattroff(menu_win, COLOR_PAIR(1));
            wrefresh(menu_win);  // Actualizar la ventana de ncurses si es necesario
        }


           // encryptOrDecryptFile(menu_win, filename, true);
        } else if (choice == 2) {

            //encryptOrDecryptFile(menu_win, filename, false);
     try {
               std::vector<unsigned char> encrypted_data = readFile(filename);

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
                //return;  // Salir de la función ya que el descifrado falló
            }

            string decryptedFilename = promptForFilename(menu_win, "Introduzca el nombre del archivo descifrado de salida", filename, "Descifrado");
            writeFile("data/decrypted" + decryptedFilename, decryptedtext);

            //remove(("data/" + decryptedFilename).c_str());
            if (remove(filename.c_str()) != 0) {
        // Si ocurre un error al eliminar el archivo, lo manejamos aquí
        perror("Error eliminando el archivo original");
    } else {
        logFileDeletion(menu_win, filename,"Descifrar", "data/decrypted" + filename, "data/decrypted" + decryptedFilename, std::vector<unsigned char>(key, key + sizeof(key)), "AES");
    } 
          // Actualizar operación de archivo en la base de datos
            logFileOperation(menu_win, decryptedFilename, "Descifrar", "data/decrypted" + filename, "data/decrypted" + decryptedFilename, std::vector<unsigned char>(key, key + sizeof(key)), "AES");

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

            wattron(menu_win, COLOR_PAIR(1)); // Color rojo
            mvwprintw(menu_win, 10, 2, "Error al descifrar: %s", e.what());
            wattroff(menu_win, COLOR_PAIR(1));
            wrefresh(menu_win);  // Actualizar la ventana de ncurses si es necesario
        } 


     } else {
            werase(menu_win);
            box(menu_win, 0, 0);
            wattron(menu_win, COLOR_PAIR(5)); // Color rojo
            mvwprintw(menu_win, 1, 2, "Opción no válida.");
            wattroff(menu_win, COLOR_PAIR(5)); // Quitar color rojo
            wrefresh(menu_win);
        }
    } else { 

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
                    auto files = listFiles("data/decrypted/");
                    string plaintextFilename = selectFileFromList(menu_win, files, recentEncryptedFiles);

                    std::vector<unsigned char> plaintext = readFile("data/decrypted/" + plaintextFilename);

                    size_t ciphertextSize = ((plaintext.size() + AES_BLOCK_SIZE) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE;
                    std::vector<unsigned char> ciphertext(ciphertextSize);

                    hidePasswordInput(menu_win,key, iv);  // Solicitar contraseña

                    encrypt(plaintext.data(), plaintext.size(), key, iv, ciphertext.data());

                    std::string ciphertextFilename = promptForFilename(menu_win, "Introduzca el nombre del archivo cifrado de salida", plaintextFilename, "Cifrado");

                    writeFile("data/encrypted/" + ciphertextFilename, ciphertext);

                 
                    // Actualizar operación de archivo en la base de datos
                    logFileOperation(menu_win, ciphertextFilename, "Cifrar", "data/encrypted/" + plaintextFilename, "data/encrypted/" + ciphertextFilename, std::vector<unsigned char>(key, key + sizeof(key)), "AES");

               

                    // Eliminar archivo original
                    remove(("data/decrypted/" + plaintextFilename).c_str());
                    //logFileDeletion(menu_win,plaintextFilename);
                     logFileDeletion(menu_win, plaintextFilename, "Eliminar", "data/encrypted/" + plaintextFilename, "data/encrypted/" + ciphertextFilename, std::vector<unsigned char>(key, key + sizeof(key)), "AES");

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
        auto files = listFiles("data/encrypted/");
          string ciphertextFilename = selectFileFromList(menu_win, files, recentEncryptedFiles);

        vector<unsigned char> encrypted_data = readFile("data/encrypted/" + ciphertextFilename);

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

        string  decryptedFilename = promptForFilename(menu_win, "Introduzca el nombre del archivo descifrado de salida", ciphertextFilename, "Descifrado");
          writeFile("data/decrypted/" + decryptedFilename, decryptedtext);


        remove(("data/encrypted/" + ciphertextFilename).c_str());
        logFileDeletion(menu_win, ciphertextFilename,"Eliminar", "data/encrypted/" + ciphertextFilename, "data/decrypted/" + decryptedFilename, std::vector<unsigned char>(key, key + sizeof(key)), "AES");

        // Actualizar operación de archivo en la base de datos
        logFileOperation(menu_win, decryptedFilename, "Descifrar", "data/encrypted/" + ciphertextFilename, "data/decrypted/" + decryptedFilename, std::vector<unsigned char>(key, key + sizeof(key)), "AES");
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

}
