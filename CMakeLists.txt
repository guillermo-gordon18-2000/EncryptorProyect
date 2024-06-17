cmake_minimum_required(VERSION 3.10)
project(EncryptorProject)

set(CMAKE_CXX_STANDARD 11)

include_directories(include)
add_executable(encryptor
    src/main.cpp
    src/encryption.cpp
    src/file_utils.cpp
    src/key_derivation.cpp
    src/openssl_utils.cpp  # Añade el nuevo archivo aquí
)

target_link_libraries(encryptor ssl crypto)
