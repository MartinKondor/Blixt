#ifndef DECOMPRESS_H
#define DECOMPRESS_H

#include <stdio.h>
#include <stdlib.h>

#include "record.h"


/**
* Decompresses file to the given out_file_name
*/
void decompress_file(char* file_name, char* out_file_name);

/**
* Sets file_ext parameter to the file extension
* read out from the given file.
*/
void file_extension_from_blx(FILE* file_ptr, char* file_ext);

#endif // DECOMPRESS_H
