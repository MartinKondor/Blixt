#include <iostream>

#ifdef _WIN32
#include <direct.h>
#define getcwd _getcwd
#else
#include <unistd.h>
#endif

#define _DEBUG_
#define MAX_FOLDER_LENGTH 260

#include "decompress.h"
#include "compress.h"
#include "utils.h"
#include "debug.h"


int main(int argc, char** argv) {
    // std::cout << std::endl;
    std::cout << " ____  __    ____  _  _  ____" << std::endl;
    std::cout << "(  _ \\(  )  (_  _)( \\/ )(_  _)" << std::endl;
    std::cout << " ) _ < )(__  _)(_  )  (   )(" << std::endl;
    std::cout << "(____/(____)(____)(_/\\_) (__)" << std::endl;
    std::cout << std::endl;

    // Check for the file's existence
    if (argc < 2) {
        std::cout << "No input file provided. The program stops." << std::endl;
        return 1;
    }

    // Get the current working directory
    char buffer[MAX_FOLDER_LENGTH];
    std::string cwd = getcwd(buffer, sizeof(buffer));
    std::string file_name = argv[1];

    if (get_extension(file_name) == ".blx") {
        debug<std::string>("decompressing...");
        decompress(cwd, file_name);
    }
    else {
        debug<std::string>("compressing...");
        compress(cwd, file_name);
    }
    return 0;
}
