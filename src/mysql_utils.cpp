#include "mysql_utils.hpp"
#include <mysql_driver.h>
#include <cppconn/connection.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <iostream>
#include <vector>
#include <ncurses.h>


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

void logFileOperation(WINDOW *menu_win,const std::string& filename, const std::string& operation) {
    try {
        sql::mysql::MySQL_Driver *driver = sql::mysql::get_mysql_driver_instance();
        std::unique_ptr<sql::Connection> con(driver->connect("tcp://127.0.0.1:3306", "ggordon", "Gordon@18"));
        con->setSchema("encryptor_db");

        std::unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement("INSERT INTO file_logs (filename, operation) VALUES (?, ?)"));
        pstmt->setString(1, filename);
        pstmt->setString(2, operation);
        pstmt->executeUpdate();
        werase(menu_win);  // Limpiar toda la ventana
        box(menu_win, 0, 0);  // Volver a dibujar el borde
 int height, width;
        getmaxyx(menu_win, height, width);

        // Dibujar el marco
        mvwhline(menu_win, 9, 1, '-', width - 2); // Línea horizontal en la fila 9 (0-indexed)
                                                  // // Imprimir mensaje en la ventana de ncurses con color verde
        wattron(menu_win, COLOR_PAIR(6)); // Activar el par de colores 1 (definido como verde)
        mvwprintw(menu_win, 10, 5, "Registro de operación de archivo guardado");
        mvwprintw(menu_win, 11, 5, " en la base de datos.");
        wattroff(menu_win, COLOR_PAIR(6)); // Desactivar el par de colores después de imprimir

        wrefresh(menu_win);  // Actualizar la ventana de ncurses si es necesario
                           //
    } catch (sql::SQLException &e) {
       // Imprimir mensaje de error en la ventana de ncurses con color rojo
        wattron(menu_win, COLOR_PAIR(2)); // Activar el par de colores 2 (definido como rojo)
        mvwprintw(menu_win, 9, 2, "Error al registrar la operación en la base de datos: %s", e.what());
        wattroff(menu_win, COLOR_PAIR(2)); // Desactivar el par de colores después de imprimir

        wrefresh(menu_win);  // Actualizar la ventana de ncurses si es necesario   

    }
}

void logFileDeletion(WINDOW *menu_win,const std::string& filename) {
    logFileOperation(menu_win, filename, "Eliminar");
}
