#ifndef _COMPRESS_H_
#define _COMPRESS_H_

#include <functional>
#include "FilePipe.h"


void compress(const std::string cwd, const std::string file_name) {
    std::string file_path = cwd + "/" + file_name;
    FilePipe pipe(file_path, file_path + ".blx");
    // pipe.start([]() {});
}

#endif
