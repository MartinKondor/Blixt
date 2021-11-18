#ifndef _UTILS_H_
#define _UTILS_H_

#include <fstream>
#include <string>


std::string get_extension(const std::string file_name) {
    return file_name.substr(file_name.find_last_of('.'), file_name.length());
}

#endif
