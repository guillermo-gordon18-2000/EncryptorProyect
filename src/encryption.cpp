#include "encryption.hpp"
#include "openssl_utils.hpp"
#include <openssl/err.h>
#include <openssl/aes.h>
#include <stdexcept>


void encrypt(const unsigned char *plaintext, int plaintext_len, const unsigned char *key,
             const unsigned char *iv, unsigned char *ciphertext) {
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    int len;
    int ciphertext_len;

    if (!EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv)) {
        handleErrors();
    }

    if (!EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext, plaintext_len)) {
        handleErrors();
    }
    ciphertext_len = len;

    if (!EVP_EncryptFinal_ex(ctx, ciphertext + len, &len)) {
        handleErrors();
    }
    ciphertext_len += len;

    EVP_CIPHER_CTX_free(ctx);
}

void decrypt(const unsigned char *ciphertext, int ciphertext_len, const unsigned char *key,
             const unsigned char *iv, unsigned char *plaintext) {
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    int len;
    int plaintext_len;

   if (!EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv)) {
        EVP_CIPHER_CTX_free(ctx);
        throw std::runtime_error("EVP_DecryptInit_ex failed");
    }

    if (!EVP_DecryptUpdate(ctx, plaintext, &len, ciphertext, ciphertext_len)) {
        EVP_CIPHER_CTX_free(ctx);
        throw std::runtime_error("EVP_DecryptUpdate failed");
    }
    plaintext_len = len;

    if (!EVP_DecryptFinal_ex(ctx, plaintext + len, &len)) {
        EVP_CIPHER_CTX_free(ctx);
        throw std::runtime_error("EVP_DecryptFinal_ex failed");
    }
    plaintext_len += len;

    EVP_CIPHER_CTX_free(ctx);
}
