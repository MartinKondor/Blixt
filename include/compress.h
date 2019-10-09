#ifndef COMPRESS_H
#define COMPRESS_H

#include <stdio.h>
#include <stdlib.h>

#include "record.h"


/**
* Compresses file to the given out_file_name
*/
void compress_file(char* file_name, char* out_file_name);

#endif // COMPRESS_H
