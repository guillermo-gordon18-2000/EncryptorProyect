// openssl_utils.cpp
#include "openssl_utils.hpp"
#include <openssl/err.h>
#include <cstdlib>

void handleErrors() {
    ERR_print_errors_fp(stderr);
    abort();
}
