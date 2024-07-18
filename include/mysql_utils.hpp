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

void logFileOperation(WINDOW *menu_win, const std::string& filename, const std::string& operation, const std::string& original_path, const std::string& encrypted_path, const std::vector<unsigned char>& encryption_key, const std::string& algorithm);


// Nueva función para registrar la eliminación de archivos
void logFileDeletion(WINDOW *menu_win, const std::string& filename, const std::string& operation, const std::string& original_path, const std::string& encrypted_path, const std::vector<unsigned char>& encryption_key, const std::string& algorithm);


void insertKey(const std::string& key_name, const std::string& key_value, const std::string& created_by, const std::string& page_type) ;
//void insertKey(const std::string& key_name, const std::string& key_value);

std::vector<std::tuple<std::string, std::string, std::string, std::string>> getKeys();

#endif // MYSQL_UTILS_HPP
