#ifndef MYSQL_UTILS_HPP
#define MYSQL_UTILS_HPP

#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <vector>
#include <string>

// Función para obtener los archivos cifrados más recientes desde la base de datos
std::vector<std::string> getRecentEncryptedFiles(int limit);

// Función para obtener los archivos descifrados más recientes desde la base de datos
std::vector<std::string> getRecentDecryptedFiles(int limit);


void logFileOperation(const std::string& filename, const std::string& operation);

#endif // MYSQL_UTILS_HPP
