#include <iostream>
#include <vector>
#include <cstring>       // Para strlen
#include "encryption.hpp"
#include "file_utils.hpp"
#include "key_derivation.hpp"
#include <openssl/aes.h>  // Incluir la cabecera de OpenSSL que define AES_BLOCK_SIZE
int main() {
    std::string password;
    std::cout << "Introduce la contraseña: ";
    std::cin >> password;

    // Derivar clave e IV a partir de la contraseña
    unsigned char key[32];  // 256 bits
    unsigned char iv[16];   // 128 bits
    deriveKeyAndIV(password, key, iv);

    // Leer archivo de texto
    std::vector<unsigned char> plaintext = readFile("text.txt");
    std::vector<unsigned char> ciphertext(plaintext.size() + AES_BLOCK_SIZE);

    // Cifrar el archivo
    encrypt(plaintext.data(), plaintext.size(), key, iv, ciphertext.data());
    writeFile("ciphertext.txt", ciphertext);

    // Leer archivo cifrado
    std::vector<unsigned char> encrypted_data = readFile("ciphertext.txt");
    std::vector<unsigned char> decryptedtext(encrypted_data.size());

    // Descifrar el archivo
    decrypt(encrypted_data.data(), encrypted_data.size(), key, iv, decryptedtext.data());

    // Escribir archivo descifrado
    writeFile("decrypted.txt", decryptedtext);

    std::cout << "Cifrado y descifrado completados." << std::endl;

    return 0;
}
