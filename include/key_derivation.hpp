#ifndef KEY_DERIVATION_HPP
#define KEY_DERIVATION_HPP

#include <string>

void deriveKeyAndIV(const std::string &password, unsigned char *key, unsigned char *iv);

#endif // KEY_DERIVATION_HPP