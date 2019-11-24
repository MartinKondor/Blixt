#ifndef COMPRESSING_H_INCLUDED
#define COMPRESSING_H_INCLUDED

#define _OPEN_SYS_ITOA_EXT
#include <stdio.h>
#include <stdlib.h>

#include "main.h"

/**

Output format:

- Each clone of a byte is counted and the counter value
  is between {counted_value} next to the byte.

Example:

Input: "aabc"
Output: "|a{2}|b|c|;file_extension"

*/
void compress_file(char* file_name);

#endif // COMPRESSING_H_INCLUDED
