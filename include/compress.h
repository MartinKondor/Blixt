#ifndef _COMPRESS_H_
#define _COMPRESS_H_

#include <functional>
#include "FilePipe.h"


std::string compress_char(const char ch) {
    return std::bitset<8>(ch).to_string() + "x";
}

std::string compress_string(const std::string &s) {
    std::string result = "";
    for (size_t i = 0; i < s.length(); i++) {
        result += compress_char(s[i]);
    }
    return result;
}

void compress(const std::string cwd, const std::string file_name) {
    std::string file_path = cwd + "/" + file_name;
    FilePipe pipe(file_path, file_path + ".blx");

    // Start compressing & encryption
    pipe.start([](const std::string &s) -> std::string {
        return compress_string(s);
    });
}

#endif
