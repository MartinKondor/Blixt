#ifndef _COMPRESS_H_
#define _COMPRESS_H_

#include <functional>
#include "FilePipe.h"


/*
1. Convert char to binary, and that to string
2. Replace 1's and 0's with the number of occurences

Example:
ch = 'a'
bin = "01100001"
result = "0110(3)1"
*/
std::string compress_char(const char ch) {
    std::string result = "";
    std::string bin = std::bitset<8>(ch).to_string();
    char last_ch;
    size_t occurence = 0;

    for (size_t i = 0; i < bin.length(); i++) {
        if (i > 0) {
            if (bin[i] == last_ch) {
                occurence++;
                continue;
            }
            else if (bin[i] != last_ch) {
                result += std::to_string(occurence);
                occurence = 0;
            }
        }

        result += bin[i];
        last_ch = bin[i];
    }

    if (occurence != 0) {
        result += std::to_string(occurence);
    }
    return result + "x";
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
