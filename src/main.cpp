#include <iostream>
#include <vector>
#include <cstring>       // Para strlen
#include "encryption.hpp"
#include "file_utils.hpp"
#include "key_derivation.hpp"
#include <openssl/aes.h>  // Incluir la cabecera de OpenSSL que define AES_BLOCK_SIZE

void displayMenu() {
    std::cout << "Bienvenido al programa de cifrado y descifrado:" << std::endl;
    std::cout << "1. Cifrar archivo" << std::endl;
    std::cout << "2. Descifrar archivo" << std::endl;
    std::cout << "3. Salir" << std::endl;
}

std::string promptForFilename(const std::string& prompt) {
    std::string filename;
    std::cout << prompt << ": ";
    std::cin >> filename;
    return filename;
}

int main() {
    std::string password;
    unsigned char key[32];  // 256 bits
    unsigned char iv[16];   // 128 bits

    std::cout << "Introduce la contraseña: ";
    std::cin >> password;

    // Derivar clave e IV a partir de la contraseña
    deriveKeyAndIV(password, key, iv);

    int choice = 0;
    while (choice != 3) {
        displayMenu();
        std::cout << "Seleccione una opción: ";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                try {
                    std::string plaintextFilename = promptForFilename("Introduzca el nombre del archivo de texto a cifrar");
                    // Leer archivo de texto
                    std::vector<unsigned char> plaintext = readFile(plaintextFilename);
                    std::vector<unsigned char> ciphertext(plaintext.size() + AES_BLOCK_SIZE);

                    // Cifrar el archivo
                    encrypt(plaintext.data(), plaintext.size(), key, iv, ciphertext.data());
                    
                    std::string ciphertextFilename = promptForFilename("Introduzca el nombre del archivo cifrado de salida");
                    writeFile(ciphertextFilename, ciphertext);

                    std::cout << "Archivo cifrado correctamente." << std::endl;
                } catch (const std::runtime_error& e) {
                    std::cerr << "Error al cifrar: " << e.what() << std::endl;
                }
                break;
            }
            case 2: {
                try {
                    std::string ciphertextFilename = promptForFilename("Introduzca el nombre del archivo cifrado a descifrar");
                    // Leer archivo cifrado
                    std::vector<unsigned char> encrypted_data = readFile(ciphertextFilename);
                    std::vector<unsigned char> decryptedtext(encrypted_data.size());

                    // Descifrar el archivo
                    decrypt(encrypted_data.data(), encrypted_data.size(), key, iv, decryptedtext.data());

                    std::string decryptedFilename = promptForFilename("Introduzca el nombre del archivo descifrado de salida");
                    writeFile(decryptedFilename, decryptedtext);

                    std::cout << "Archivo descifrado correctamente." << std::endl;
                } catch (const std::runtime_error& e) {
                    std::cerr << "Error al descifrar: " << e.what() << std::endl;
                }
                break;
            }
            case 3:
                std::cout << "Saliendo del programa." << std::endl;
                break;
            default:
                std::cerr << "Opción inválida. Por favor, seleccione nuevamente." << std::endl;
                break;
        }
    }

    return 0;
}
