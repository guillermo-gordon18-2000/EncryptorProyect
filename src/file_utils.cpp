// file_utils.cpp

#include "file_utils.hpp"
#include "key_derivation.hpp"
#include "openssl_utils.hpp"
#include "time_utils.hpp"
#include "encryption.hpp"
#include "mysql_utils.hpp"

#include "menu.hpp"
#include "password_prompt.hpp"
#include <vector>

#include <fstream>
#include <boost/filesystem.hpp> // Incluir Boost.Filesystem en lugar de std::filesystem
#include <string>  // Incluir el encabezado <string>
//
//
//
//
//
//
#include <ncurses.h>
#include <ctime>
#include <openssl/err.h>
#include <openssl/aes.h>

using namespace std;
namespace fs = boost::filesystem; // Namespace alias para Boost.Filesystem

std::vector<std::string> listFiles(const std::string& directory) {
    std::vector<std::string> files;
    fs::path dirPath(directory);
    if (!fs::exists(dirPath) || !fs::is_directory(dirPath)) {
        throw std::runtime_error("Directory does not exist or is not a directory");
    }

    for (const auto& entry : fs::directory_iterator(dirPath)) {
        if (fs::is_regular_file(entry)) {
            files.push_back(entry.path().filename().string());
        }
    }
    return files;
}

std::vector<unsigned char> readFile(const std::string &filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file: " + filename);
    }
    return std::vector<unsigned char>((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
}

void writeFile(const std::string &filename, const std::vector<unsigned char> &data) {
    std::ofstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file: " + filename);
    }
    file.write(reinterpret_cast<const char *>(data.data()), data.size());
}

void moveFileToData(const std::string& filename) {

    std::string sourcePath = "./" + filename;
    std::string destinationPath = "./data/" + filename;

    if (std::rename(sourcePath.c_str(), destinationPath.c_str()) != 0) {
        throw std::runtime_error("Error al mover el archivo a la carpeta data.");
    }
}

// Función para verificar si un archivo está cifrado
bool isFileEncrypted(const std::string &filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Error al abrir el archivo: " + filename);
    }

    constexpr double entropyThreshold = 7.5; // Umbral de entropía para determinar si un archivo parece cifrado

    // Leer el contenido del archivo para calcular la entropía
    file.seekg(0, std::ios::end);
    std::streampos fileSize = file.tellg();
    file.seekg(0, std::ios::beg);

    std::vector<char> buffer(std::min(fileSize, static_cast<std::streampos>(1024)), '\0'); // Leer hasta 1024 bytes
    file.read(buffer.data(), buffer.size());

    // Calcular la entropía
    double entropy = 0.0;
    std::array<int, 256> freq = {0};
    for (char c : buffer) {
        freq[static_cast<unsigned char>(c)]++;
    }
    for (int i = 0; i < 256; ++i) {
        if (freq[i] > 0) {
            double p = static_cast<double>(freq[i]) / buffer.size();
            entropy -= p * log2(p);
        }
    }

    // Comparar la entropía con el umbral
    return entropy >= entropyThreshold;
}


string promptForFilename(WINDOW *menu_win, const string &prompt, const string &originalFilename, const string &method) {
    string suggestedFilename = originalFilename + "_" + method + "_" + getCurrentDate() + ".txt";

    werase(menu_win);
    box(menu_win, 0, 0);

    wattron(menu_win, COLOR_PAIR(5)); // Color amarillo
    mvwprintw(menu_win, 1, 2, "%s", prompt.c_str());
    wattroff(menu_win, COLOR_PAIR(5)); // Color amarillo

    // Opción 1: Usar el mismo nombre de archivo
    mvwprintw(menu_win, 4, 2, "1. Usar el mismo nombre de archivo:");
    if (originalFilename.length() > 35) {
        // Si el nombre original es muy largo, truncarlo para la impresión
        string truncatedName = originalFilename.substr(0, 14);
        wattron(menu_win, COLOR_PAIR(4)); // Color verde
       mvwprintw(menu_win, 6, 4, "%s...", truncatedName.c_str());
        wattroff(menu_win, COLOR_PAIR(4)); // Color verde
    } else {
        wattron(menu_win, COLOR_PAIR(4)); // Color verde
        mvwprintw(menu_win, 5, 4, "%s", originalFilename.c_str());
        wattroff(menu_win, COLOR_PAIR(4)); // Color Verde
    }


 size_t pos;
    pos = suggestedFilename.find(".txt");
    if (pos != string::npos) {
        suggestedFilename.insert(pos, "_*");
    }

    wattron(menu_win, COLOR_PAIR(5)); // Color amarillo
    // Opción 2: Cambiar nombre de archivo
    mvwprintw(menu_win, 6, 2, "2. Cambiar nombre de archivo");
    wattroff(menu_win, COLOR_PAIR(5)); // Color amarillo

    // Opción 3: Sugerir un nuevo nombre
    wattron(menu_win, COLOR_PAIR(5)); // Color amarillo
    mvwprintw(menu_win, 7, 2, "3. Sugerir un nuevo nombre:");
    wattroff(menu_win, COLOR_PAIR(5)); // Color amarillo

    if (originalFilename.length() > 17) {
        // Truncar el nombre original para la concatenación sugerida
        string truncatedName = originalFilename.substr(0, 7);
        if (originalFilename.find(".txt") != string::npos) {
            // El nombre original ya tiene extensión ".txt"
            suggestedFilename = truncatedName + "_" + method + "_" + getCurrentDate()+ "_" + getCurrentTime() + ".txt";
        } else {
            // El nombre original no tiene extensión ".txt"
            suggestedFilename = truncatedName + "_" + method + "_" + getCurrentDate();
        }
    } else {
        if (originalFilename.find(".txt") != string::npos) {
            // El nombre original ya tiene extensión ".txt"
            suggestedFilename = originalFilename + "_" + method + "_" + getCurrentDate()+ "_" + getCurrentTime() + ".txt";
        } else {
            // El nombre original no tiene extensión ".txt"
            suggestedFilename = originalFilename + "_" + method + "_" + getCurrentDate();
        }
    }

    wattron(menu_win, COLOR_PAIR(4)); // Color amarillo
    mvwprintw(menu_win, 8, 6, "%s", suggestedFilename.c_str());
    wattroff(menu_win, COLOR_PAIR(4)); // Color amarillo

    wrefresh(menu_win);

    int choice;
    echo();
    mvwscanw(menu_win, 10, 2, "%d", &choice);
    noecho();

    string filename;
     //string pos;

    switch (choice) {
        case 1:
          pos = originalFilename.find(".txt");
            if (pos != string::npos) {
                filename = originalFilename.substr(0, pos) + "_*" + originalFilename.substr(pos);
            } else {
                filename = originalFilename + "_*";
            }           
       break;
        case 2:
            mvwprintw(menu_win, 10, 2, "Ingrese el nuevo nombre de archivo: ");
            char newFilename[256];
            echo();
            mvwgetnstr(menu_win, 11, 2, newFilename, 255);
            noecho();
            filename = string(newFilename);
            break;
        case 3:
            filename = suggestedFilename;
            break;
        default:
            filename = originalFilename;
            break;
    }

    return filename;
}




