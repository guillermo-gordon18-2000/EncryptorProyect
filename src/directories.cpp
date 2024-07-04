#include "directories.hpp"
#include <cstdlib>

// Define the complete paths for the directories
const std::string projectDir = "/home/maverick/Documents/Proyecto/C++/EncryptorProyect/";
const std::string encryptedDir = projectDir + "data/encrypted/";
const std::string decryptedDir = projectDir + "data/decrypted/";

void createDirectories() {
    // Create the encrypted directory if it doesn't exist
    system(("mkdir -p " + encryptedDir).c_str());
    
    // Create the decrypted directory if it doesn't exist
    system(("mkdir -p " + decryptedDir).c_str());
}
