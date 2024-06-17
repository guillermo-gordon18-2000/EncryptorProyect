#ifndef ENCRYPTION_HPP
#define ENCRYPTION_HPP

#include <openssl/evp.h>
#include <vector>

void encrypt(const unsigned char *plaintext, int plaintext_len, const unsigned char *key,
             const unsigned char *iv, unsigned char *ciphertext);

void decrypt(const unsigned char *ciphertext, int ciphertext_len, const unsigned char *key,
             const unsigned char *iv, unsigned char *plaintext);

#endif // ENCRYPTION_HPP