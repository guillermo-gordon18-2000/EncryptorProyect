//MYSQL_UTILS_HPP
#ifndef MYSQL_UTILS_HPP
#define MYSQL_UTILS_HPP

#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <vector>
#include <string>
#include <ncurses.h> // Incluir ncurses.h para usar WINDOW

// Función para obtener los archivos cifrados más recientes desde la base de datos
std::vector<std::string> getRecentEncryptedFiles(int limit);

// Función para obtener los archivos descifrados más recientes desde la base de datos
std::vector<std::string> getRecentDecryptedFiles(int limit);

// Función para registrar la operación de archivo en la base de datos y mostrar en ncurses
void logFileOperation(WINDOW *menu_win, const std::string& filename, const std::string& operation);

// Nueva función para registrar la eliminación de archivos
void logFileDeletion(WINDOW *menu_win,const std::string& filename);


#endif // MYSQL_UTILS_HPP
