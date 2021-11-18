#ifndef _FILE_PIPE_H_
#define _FILE_PIPE_H_

#include <string>
#include <fstream>
#include <functional>
#include "debug.h"


class FilePipe {
    bool can_start;
    std::string from_file;
    std::string to_file;

    public:
    FilePipe(const std::string _from_file="", std::string _to_file="") : from_file(_from_file), to_file(_to_file) {
        can_start = !from_file.empty();
        debug<std::string>(from_file, "FilePipe.from_file");
        debug<std::string>(to_file, "FilePipe.to_file");
    }

    void start(const std::function<void(void)> func) const {
        if (!can_start) {
            std::cout << "Cannot start file pipe because no input file is provided" << std::endl;
            exit(0);
        }

        // std::ifstream input_file(from_file);
        // std::ofstream ouput_file(to_file);
    }
};

#endif
