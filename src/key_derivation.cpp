// key_derivation.cpp
#include "key_derivation.hpp"
#include "openssl_utils.hpp"
#include <openssl/evp.h>

void deriveKeyAndIV(const std::string &password, unsigned char *key, unsigned char *iv) {
    const unsigned char salt[] = "12345678";
    if (!PKCS5_PBKDF2_HMAC(password.c_str(), password.size(), salt, sizeof(salt), 10000, EVP_sha256(), 32, key)) {
        handleErrors();
    }
    if (!PKCS5_PBKDF2_HMAC(password.c_str(), password.size(), salt, sizeof(salt), 10000, EVP_sha256(), 16, iv)) {
        handleErrors();
    }
}
