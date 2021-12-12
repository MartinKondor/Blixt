#ifndef _FILE_PIPE_H_
#define _FILE_PIPE_H_

#include <iostream>
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
        can_start = !from_file.empty() && !from_file.empty();
    }

    void start(const std::function<std::string(std::string)> &func) const {
        if (!can_start) {
            std::cout << "Cannot start file pipe because no input file is provided" << std::endl;
            exit(0);
        }

        std::ifstream input_file(from_file);
        std::ofstream ouput_file(to_file);

        if (!input_file.is_open() || !ouput_file.is_open()) {
            std::cout << "Cannot open input or output file." << std::endl;
            exit(0);
        }

        std::string word;
        while (input_file.good()) {
            std::getline(input_file, word);

            if (word.length() != 0) {
                ouput_file << func(word) + "\n";
            }
        }

        ouput_file.close();
        input_file.close();

    }
};

#endif
