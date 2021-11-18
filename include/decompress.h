#ifndef _DECOMPRESS_H_
#define _DECOMPRESS_H_

#include <functional>
#include "FilePipe.h"


void decompress(const std::string cwd, const std::string file_name) {
    std::string file_path = cwd + "/" + file_name;
    FilePipe pipe(file_path, file_path + ".blx");
    // pipe.start([]() {});
}

#endif
