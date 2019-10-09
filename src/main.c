#include "main.h"


int main(int argc, char** argv)
{
    if (argc != 2)
    {
        perror("No input file(s) provided.\n");
        system("pause");
        return 1;
    }

    char* input_file_name = strdup(argv[1]);
    char* base_folder = dirname(argv[0]);
    char* new_file_name = (char*) malloc(FILENAME_MAX * sizeof(char));

    if (strcmp(file_extension(input_file_name), ".blx") == 0)
    {
        sprintf(new_file_name, "%s\\%s", base_folder, "test_decompressed");
        decompress_file(input_file_name, new_file_name);
        printf("File decompression, done.\n");
        system("pause");
    }
    else
    {
        sprintf(new_file_name, "%s\\%s", base_folder, "test.blx");
        compress_file(input_file_name, new_file_name);
        printf("File compression, done.\n");
        system("pause");
    }

    free(new_file_name);
    return 0;
}

char* file_extension(char* file_name)
{
    char* file_ext = strrchr(file_name, '.');

    if (file_ext == NULL)
    {
        return "";
    }

    return file_ext;
}
