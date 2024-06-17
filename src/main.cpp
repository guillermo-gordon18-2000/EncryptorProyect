
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
#include <algorithm> // Para std::sort y std::reverse
#include <string>    // Agrega esta línea para usar std::string

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

void displayMenu(const vector<string>& recentEncryptedFiles, const vector<string>& recentDecryptedFiles) {
    cout << cyan << "+----------------------------+" << reset << endl;
    cout << cyan << "| " << bold << " Bienvenido al programa de cifrado y descifrado " << reset << cyan << " |" << reset << endl;
    cout << cyan << "+----------------------------+" << reset << endl;
    cout << yellow << " 1. Cifrar archivo" << reset << endl;
    if (!recentEncryptedFiles.empty()) {
        cout << magenta << "    Archivos cifrados recientes: " << reset << endl;
        for (const auto& file : recentEncryptedFiles) {
            cout << "       - " << blue << file << reset << endl;
        }
    }
    cout << yellow << " 2. Descifrar archivo" << reset << endl;
    if (!recentDecryptedFiles.empty()) {
        cout << magenta << "    Archivos descifrados recientes: " << reset << endl;
        for (const auto& file : recentDecryptedFiles) {
            cout << "       - " << green << file << reset << endl;
        }
    }
    cout << yellow << " 3. Salir" << reset << endl;
    cout << cyan << "+----------------------------+" << reset << endl;
}

string promptForFilename(const string& prompt) {
    string filename;
    cout << green << prompt << ": " << reset;
    cin >> filename;
    return filename;
}

string selectFileFromList(const vector<string>& files) {
    cout << blue << "Archivos disponibles:" << reset << endl;
    for (size_t i = 0; i < files.size(); ++i) {
        cout << magenta << " " << i + 1 << ". " << files[i] << reset << endl;
    }
    cout << green << "Seleccione el número del archivo: " << reset;
    size_t choice;
    cin >> choice;
    if (choice < 1 || choice > files.size()) {
        throw runtime_error("Opción inválida.");
    }
    return files[choice - 1];
}

void hidePasswordInput(unsigned char* key, unsigned char* iv) {
    termios tty;
    tcgetattr(STDIN_FILENO, &tty);
    termios tty_old = tty;
    tty.c_lflag &= ~ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &tty);

    string password;
    char ch;
    cout << green << "Introduce la contraseña: " << reset;

    while (true) {
        ch = getchar();
        if (ch == '\n' || ch == '\r') {
            cout << endl;
            break;
        } else if (ch == 127 || ch == '\b') {  // Handle backspace
            if (!password.empty()) {
                cout << "\b \b";
                password.pop_back();
            }
        } else {
            password.push_back(ch);
            cout << '*';
        }
    }

    tcsetattr(STDIN_FILENO, TCSANOW, &tty_old);

    deriveKeyAndIV(password, key, iv);
}

void printError(const string& message) {
    cout << endl;
    cout << red << "+----------------------------+" << reset << endl;
    cerr << red << message << reset << endl;
    cout << red << "+----------------------------+" << reset << endl;
    cout << endl;
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


      hidePasswordInput(key, iv);


  if (argc == 2) {
        // Si se proporciona un archivo como argumento, cifrarlo y salir
        std::string plaintextFilename = argv[1];
        std::vector<unsigned char> plaintext = readFile(plaintextFilename);

        size_t ciphertextSize = ((plaintext.size() + AES_BLOCK_SIZE) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE;
        std::vector<unsigned char> ciphertext(ciphertextSize);

        encrypt(plaintext.data(), plaintext.size(), key, iv, ciphertext.data());

        std::string ciphertextFilename = promptForFilename("Introduzca el nombre del archivo cifrado de salida");
        writeFile(ciphertextFilename, ciphertext);

        try {
            moveFileToData(ciphertextFilename);
            logFileOperation(ciphertextFilename, "Cifrar");
            std::cout << blue << "Archivo cifrado correctamente y movido a la carpeta data." << reset << std::endl;
        } catch (const std::runtime_error& e) {
            printError("Error al mover el archivo cifrado: " + std::string(e.what()));
        }

        return 0;
    }

    // Obtener los archivos más recientes desde la base de datos
    vector<string> recentEncryptedFiles = getRecentEncryptedFiles(4);
    vector<string> recentDecryptedFiles = getRecentDecryptedFiles(4);

    int choice = 0;
    while (choice != 3) {
        displayMenu(recentEncryptedFiles, recentDecryptedFiles);
        cout << green << "Seleccione una opción: " << reset;
        cin >> choice;

        switch (choice) {
            case 1: {
                try {
                    auto files = listFiles("data");
                    string plaintextFilename = selectFileFromList(files);

                   std::vector<unsigned char> plaintext = readFile("data/" + plaintextFilename);


                    size_t ciphertextSize = ((plaintext.size() + AES_BLOCK_SIZE) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE;

                    std::vector<unsigned char> ciphertext(ciphertextSize);

                   // hidePasswordInput(key, iv);
                    encrypt(plaintext.data(), plaintext.size(), key, iv, ciphertext.data());

                    std::string ciphertextFilename = promptForFilename("Introduzca el nombre del archivo cifrado de salida");

                    writeFile("data/" + ciphertextFilename, ciphertext);

    
                   logFileOperation(ciphertextFilename, "Cifrar");

                    std::cout << blue << "Archivo cifrado correctamente." << reset << std::endl;


                    // Eliminar archivo original
                    remove(("data/" + plaintextFilename).c_str());
                    logFileDeletion(plaintextFilename);

                    // Actualizar archivos cifrados recientes
                    if (recentEncryptedFiles.size() >= 4) {
                        recentEncryptedFiles.erase(recentEncryptedFiles.begin()); // Elimina el más antiguo
                    }
                    recentEncryptedFiles.push_back(ciphertextFilename);

                } catch (const runtime_error& e) {
                    printError("Error al cifrar: " + string(e.what()));
                }
                break;
            }
            case 2: {
                try {
                    auto files = listFiles("data");
                    string ciphertextFilename = selectFileFromList(files);

                    std::vector<unsigned char> encrypted_data = readFile("data/" + ciphertextFilename);

                    size_t decryptedSize = ((encrypted_data.size() + AES_BLOCK_SIZE - 1) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE;
                  
                    std::vector<unsigned char> decryptedtext(decryptedSize);

                  //  hidePasswordInput(key, iv);
                    decrypt(encrypted_data.data(), encrypted_data.size(), key, iv, decryptedtext.data());

                   
                    std::string decryptedFilename = promptForFilename("Introduzca el nombre del archivo descifrado de salida");
                    writeFile("data/" + decryptedFilename, decryptedtext);

                    logFileOperation(decryptedFilename, "Descifrar");

                    cout << green << "Archivo descifrado correctamente." << reset << endl;


                    // Eliminar archivo original
                  //  remove(("data/" + plaintextFilename).c_str());
                   // logFileDeletion(plaintextFilename);

                    // Actualizar archivos descifrados recientes
                    if (recentDecryptedFiles.size() >= 4) {
                        recentDecryptedFiles.erase(recentDecryptedFiles.begin()); // Elimina el más antiguo
                    }
                    recentDecryptedFiles.push_back(decryptedFilename);

                } catch (const runtime_error& e) {
                    printError("Error al descifrar: " + string(e.what()));
                }
                break;
            }
            case 3:
                cout << green << "Saliendo del programa." << reset << endl;
                break;
            default:
                printError("Opción inválida. Por favor, seleccione nuevamente.");
                break;
        }
    }

    return 0;
}
