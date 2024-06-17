
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

// Funciones para manejo de colores en la consola
const std::string reset = "\033[0m";
const std::string red = "\033[31m";
const std::string green = "\033[32m";
const std::string yellow = "\033[33m";
const std::string blue = "\033[34m";
const std::string magenta = "\033[35m";
const std::string cyan = "\033[36m";
const std::string bold = "\033[1m";

void displayMenu() {
    std::cout << cyan << "+----------------------------+" << reset << std::endl;
    std::cout << cyan << "| " << bold << " Bienvenido al programa de cifrado y descifrado " << reset << cyan << " |" << reset << std::endl;
    std::cout << cyan << "+----------------------------+" << reset << std::endl;
    std::cout << yellow << " 1. Cifrar archivo" << reset << std::endl;
    std::cout << yellow << " 2. Descifrar archivo" << reset << std::endl;
    std::cout << yellow << " 3. Salir" << reset << std::endl;
    std::cout << cyan << "+----------------------------+" << reset << std::endl;
}

std::string promptForFilename(const std::string& prompt) {
    std::string filename;
    std::cout << green << prompt << ": " << reset;
    std::cin >> filename;
    return filename;
}

std::string selectFileFromList(const std::vector<std::string>& files) {
    std::cout << blue << "Archivos disponibles:" << reset << std::endl;
    for (size_t i = 0; i < files.size(); ++i) {
        std::cout << magenta << " " << i + 1 << ". " << files[i] << reset << std::endl;
    }
    std::cout << green << "Seleccione el número del archivo: " << reset;
    size_t choice;
    std::cin >> choice;
    if (choice < 1 || choice > files.size()) {
        throw std::runtime_error("Opción inválida.");
    }
    return files[choice - 1];
}

void hidePasswordInput(unsigned char* key, unsigned char* iv) {
    termios tty;
    tcgetattr(STDIN_FILENO, &tty);
    termios tty_old = tty;
    tty.c_lflag &= ~ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &tty);

    std::string password;
    char ch;
    std::cout << green << "Introduce la contraseña: " << reset;

    while (true) {
        ch = getchar();
        if (ch == '\n' || ch == '\r') {
            std::cout << std::endl;
            break;
        } else if (ch == 127 || ch == '\b') {  // Handle backspace
            if (!password.empty()) {
                std::cout << "\b \b";
                password.pop_back();
            }
        } else {
            password.push_back(ch);
            std::cout << '*';
        }
    }

    tcsetattr(STDIN_FILENO, TCSANOW, &tty_old);

    deriveKeyAndIV(password, key, iv);
}

void printError(const std::string& message) {
    std::cout << std::endl;
    std::cout << red << "+----------------------------+" << reset << std::endl;
    std::cerr << red << message << reset << std::endl;
    std::cout << red << "+----------------------------+" << reset << std::endl;
    std::cout << std::endl;
}

int main() {
    unsigned char key[32];  // 256 bits
    unsigned char iv[16];   // 128 bits

    hidePasswordInput(key, iv);

    int choice = 0;
    while (choice != 3) {
        displayMenu();
        std::cout << green << "Seleccione una opción: " << reset;
        std::cin >> choice;

        switch (choice) {
            case 1: {
                try {
                    // Listar archivos disponibles para cifrado
                    auto files = listFiles("data");
                    std::string plaintextFilename = selectFileFromList(files);

                    // Leer archivo de texto
                    std::vector<unsigned char> plaintext = readFile("data/" + plaintextFilename);

                    // Calcular el tamaño del búfer de cifrado
                    size_t ciphertextSize = ((plaintext.size() + AES_BLOCK_SIZE) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE;
                    std::vector<unsigned char> ciphertext(ciphertextSize);

                    // Cifrar el archivo
                    encrypt(plaintext.data(), plaintext.size(), key, iv, ciphertext.data());

                    std::string ciphertextFilename = promptForFilename("Introduzca el nombre del archivo cifrado de salida");
                    writeFile("data/" + ciphertextFilename, ciphertext);

                    std::cout << blue << "Archivo cifrado correctamente." << reset << std::endl;
                } catch (const std::runtime_error& e) {
                    printError("Error al cifrar: " + std::string(e.what()));
                }
                break;
            }
            case 2: {
                try {
                    // Listar archivos disponibles para descifrado
                    auto files = listFiles("data");
                    std::string ciphertextFilename = selectFileFromList(files);

                    // Leer archivo cifrado
                    std::vector<unsigned char> encrypted_data = readFile("data/" + ciphertextFilename);

                    // Calcular el tamaño del búfer de descifrado
                    size_t decryptedSize = ((encrypted_data.size() + AES_BLOCK_SIZE - 1) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE;
                    std::vector<unsigned char> decryptedtext(decryptedSize);

                    // Descifrar el archivo
                    decrypt(encrypted_data.data(), encrypted_data.size(), key, iv, decryptedtext.data());

                    std::string decryptedFilename = promptForFilename("Introduzca el nombre del archivo descifrado de salida");
                    writeFile("data/" + decryptedFilename, decryptedtext);

                    std::cout << blue << "Archivo descifrado correctamente." << reset << std::endl;
                } catch (const std::runtime_error& e) {
                    printError("Error al descifrar: " + std::string(e.what()));
                }
                break;
            }
            case 3:
                std::cout << green << "Saliendo del programa." << reset << std::endl;
                break;
            default:
                printError("Opción inválida. Por favor, seleccione nuevamente.");
                break;
        }
    }

    return 0;
}

