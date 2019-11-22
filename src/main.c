#include <stdio.h>
#include <unistd.h>

#include "main.h"
#include "compress.h"
#include "decompress.h"


/**
* @return file_name's extension
*/
char* file_extension(char* file_name)
{
    char _file_name[FILENAME_MAX];
    strcpy(_file_name, file_name);

    char* file_ext = strrchr(_file_name, '.');

    if (file_ext == NULL)
        return "";

    // Remove dot from the first position
    if (file_ext[0] == '.')
        memmove(file_ext, file_ext + 1, strlen(file_ext));

    return file_ext;
}

void blixt_file(char* file_name)
{
    if (file_extension(file_name) == "blx")
    {
        decompress_file(file_name);
    }
    else
    {
        compress_file(file_name);
    }
}

int main(unsigned int argc, char** argv)
{
    // Check for the file's existence
    if (argc < 2)
    {
        printf("\n");
        printf(" ____  __    ____  _  _  ____\n");
        printf("(  _ \\(  )  (_  _)( \\/ )(_  _)\n");
        printf(" ) _ < )(__  _)(_  )  (   )(\n");
        printf("(____/(____)(____)(_/\\_) (__)\n");
        printf("\n");

        /// TODO: print help text
        return 1;
    }

    char* base_folder = dirname(argv[0]);
    char file_name[FILENAME_MAX];
    unsigned int i;

    for (i = 1; i < argc; i++)
    {
        sprintf(file_name, "%s\\%s", base_folder, basename(argv[i]));

        if (access(file_name, F_OK) == -1)
        {
            printf("Input file (%s) cannot be opened.\n", file_name);
            return 0;
        }

        blixt_file(file_name);
    }

    return 0;
}
