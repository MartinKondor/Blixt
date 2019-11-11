#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


const unsigned int BUFFER_SIZE = 1024;


/**
* @return file_name's extension
*/
char* file_extension(char* file_name)
{
    char* file_ext = strrchr(file_name, '.');

    if (file_ext == NULL)
    {
        return "";
    }

    return file_ext;
}

/**
* @return extract a substring from the given string
*/
void substring(char* s, char* sub, unsigned int position, unsigned int length) {
   unsigned int c = 0;

   while (c < length) {
      sub[c] = s[position + c - 1];
      c++;
   }

   sub[c] = '\0';
}

void blixt_file(char* file_name)
{
    char* new_file_name, input_file_name = strdup(file_name);
    unsigned char* out_buffer, in_buffer = (unsigned char*) malloc(BUFFER_SIZE);
    unsigned int i, filled_buffer_size, out_buffer_index = 0;

    // Open and read the contents of file
    FILE* file = fopen(input_file_name, "rb");
    fread(in_buffer, sizeof(char) * BUFFER_SIZE, 1, file);
    fclose(file);

    // Determine the write buffer size
    for (filled_buffer_size = 0; filled_buffer_size < BUFFER_SIZE; filled_buffer_size++)
    {
        if (in_buffer[filled_buffer_size] == '\0')
        {
            break;
        }
    }

    new_file_name = (unsigned char*) malloc(FILENAME_MAX);
    out_buffer = (unsigned char*) malloc(BUFFER_SIZE);

    if (strcmp(file_extension(input_file_name), ".blx") == 0)  // Decompressing
    {
        // Extract the file extension
        unsigned int file_ext_index = 0;
        char* file_ext = ".out.txt";

        /// TODO: First, read out the header
        /// TODO: Decompressing into the out_buffer
        for (i = 0; i < strlen(in_buffer); i++)
        {
            out_buffer[out_buffer_index++] = in_buffer[i];
        }
        out_buffer[out_buffer_index++] = '\0';
        sprintf(new_file_name, "%s%s", file_name, file_ext);
    }
    else  // Compressing
    {
        sprintf(new_file_name, "%s%s", file_name, ".blx");
        char* file_ext = file_extension(input_file_name);

        // Write in a "header" to the compressed file which contains
        // the information about the input files

        // i = 1 to skip the dot in the ".extension" string
        for (i = 1; i < strlen(file_ext); i++)
        {
            out_buffer[out_buffer_index++] = file_ext[i];
        }
        out_buffer[out_buffer_index++] = ';';

        /// TODO: Compressing file contents into out_buffer
        for (i = 0; i < strlen(in_buffer); i++)
        {
            out_buffer[out_buffer_index++] = in_buffer[i];
        }
        out_buffer[out_buffer_index++] = '\0';
    }

    // Open the new file for reading
    FILE* output_file = fopen(new_file_name, "wb");
    fwrite(out_buffer, out_buffer_index - 1, 1, output_file);
    fclose(output_file);

    free(in_buffer);
    free(out_buffer);
    free(new_file_name);
}

int main(unsigned int argc, char** argv)
{
    // Check for the file's existence
    if (argc < 2)
    {
        printf("No input file(s) provided.\n");
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
