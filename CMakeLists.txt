cmake_minimum_required(VERSION 3.10)
project(EncryptorProject)

set(CMAKE_CXX_STANDARD 11)

# Incluir directorios de encabezado
include_directories(include)

# Incluye directorios de encabezados de OpenSSL
find_package(OpenSSL REQUIRED)
include_directories(${OPENSSL_INCLUDE_DIR})

# Incluye directorios de encabezados de Boost
find_package(Boost REQUIRED COMPONENTS filesystem)
include_directories(${Boost_INCLUDE_DIRS})

add_executable(encryptor
    src/main.cpp
    src/encryption.cpp
    src/file_utils.cpp
    src/key_derivation.cpp
    src/openssl_utils.cpp
)

# Enlaza con OpenSSL y Boost
target_link_libraries(encryptor ${OPENSSL_LIBRARIES} ${Boost_LIBRARIES})
