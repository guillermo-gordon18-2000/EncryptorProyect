#include "mysql_utils.hpp"
#include <mysql_driver.h>
#include <cppconn/connection.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <iostream>


std::vector<std::string> getRecentEncryptedFiles(int limit) {
    std::vector<std::string> files;

    try {
        sql::mysql::MySQL_Driver *driver = sql::mysql::get_mysql_driver_instance();
        std::unique_ptr<sql::Connection> con(driver->connect("tcp://127.0.0.1:3306", "ggordon", "Gordon@18"));
        con->setSchema("encryptor_db");

        std::unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement(
            "SELECT filename FROM file_logs WHERE operation = 'Cifrar' ORDER BY timestamp DESC LIMIT ?"));

        pstmt->setInt(1, limit);

        std::unique_ptr<sql::ResultSet> res(pstmt->executeQuery());

        while (res->next()) {
            files.push_back(res->getString("filename"));
        }
    } catch (sql::SQLException &e) {
        std::cerr << "Error al obtener archivos cifrados recientes: " << e.what() << std::endl;
    }

    return files;
}


std::vector<std::string> getRecentDecryptedFiles(int limit) {
    std::vector<std::string> files;

    try {
        sql::mysql::MySQL_Driver *driver = sql::mysql::get_mysql_driver_instance();
        std::unique_ptr<sql::Connection> con(driver->connect("tcp://127.0.0.1:3306", "ggordon", "Gordon@18"));
        con->setSchema("encryptor_db");

        std::unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement(
            "SELECT filename FROM file_logs WHERE operation = 'Descifrar' ORDER BY timestamp DESC LIMIT ?"));

        pstmt->setInt(1, limit);

        std::unique_ptr<sql::ResultSet> res(pstmt->executeQuery());

        while (res->next()) {
            files.push_back(res->getString("filename"));
        }
    } catch (sql::SQLException &e) {
        std::cerr << "Error al obtener archivos descifrados recientes: " << e.what() << std::endl;
    }

    return files;
}

void logFileOperation(const std::string& filename, const std::string& operation) {
    try {
        sql::mysql::MySQL_Driver *driver = sql::mysql::get_mysql_driver_instance();
        std::unique_ptr<sql::Connection> con(driver->connect("tcp://127.0.0.1:3306", "ggordon", "Gordon@18"));
        con->setSchema("encryptor_db");

        std::unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement("INSERT INTO file_logs (filename, operation) VALUES (?, ?)"));
        pstmt->setString(1, filename);
        pstmt->setString(2, operation);
        pstmt->executeUpdate();

        std::cout << "Registro de operación de archivo guardado en la base de datos." << std::endl;
    } catch (sql::SQLException &e) {
        std::cerr << "Error al registrar la operación en la base de datos: " << e.what() << std::endl;
    }
}

void logFileDeletion(const std::string& filename) {
    logFileOperation(filename, "Eliminar");
}
