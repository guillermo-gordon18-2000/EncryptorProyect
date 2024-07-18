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

# Incluye directorios de encabezados de MySQL Connector/C++
set(MySQL_INCLUDE_DIRS "/usr/include/mysql-cppconn")  # Ajusta según tu instalación
include_directories(${MySQL_INCLUDE_DIRS})

# Encuentra la biblioteca ncurses
find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

# Vincula las bibliotecas necesarias
set(MySQL_LIBRARIES "/usr/lib/mysql")  # Ajusta según tu instalación
set(EXTRA_LIBS "-lmysqlcppconn")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${EXTRA_LIBS}")

add_executable(encryptor
    src/main.cpp
    src/encryption.cpp
    src/file_utils.cpp
    src/key_derivation.cpp
    src/openssl_utils.cpp
    src/mysql_utils.cpp
    src/colors.cpp
    src/directories.cpp
    src/password_prompt.cpp
    src/time_utils.cpp
    src/menu.cpp
    src/keys/key_encryption.cpp
    src/keys/key_menu.cpp
    src/urls/url_encryption.cpp
    src/urls/url_menu.cpp

)

# Vincula con OpenSSL, Boost, MySQL y ncurses
target_link_libraries(encryptor ${OPENSSL_LIBRARIES} ${Boost_LIBRARIES} ${EXTRA_LIBS} ${CURSES_LIBRARIES})

# Añadir un objetivo para formatear el código con Prettier
add_custom_target(format
  COMMAND prettier --write "**/*.{js,jsx,ts,tsx,css,scss,md,json,html,yaml}"
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  COMMENT "Formateando el código con Prettier"
)
