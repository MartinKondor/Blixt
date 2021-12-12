#ifndef _DECOMPRESS_H_
#define _DECOMPRESS_H_

#include <functional>
#include "FilePipe.h"


char decompress_chunk(const std::string &s) {
    return static_cast<char>(std::bitset<8>(s).to_ulong()); 
}

std::string decompress_string(const std::string &s) {
    std::string result = "";
    std::string chunk = "";

    for (size_t i = 0; i < s.length(); i++) {
        if (s[i] == 'x') {
            result += decompress_chunk(chunk);
            chunk = "";
            continue;
        }
        chunk += s[i];
    }

    return result;
}

void decompress(const std::string cwd, const std::string file_name) {
    std::string file_path = cwd + "/" + file_name.substr(0, file_name.find_last_of("."));
    FilePipe pipe(file_path + ".blx", file_path);

    // Start compressing & encryption
    pipe.start([](const std::string &s) -> std::string {
        return decompress_string(s);
    });
}

#endif
