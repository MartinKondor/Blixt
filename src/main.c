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


int main(const int argc, const char** argv)
{
    // Check for the file's existence
    if (argc < 2 || access(argv[1], F_OK) == -1)
    {
        perror("No input file(s) provided.\n");
        system("pause");
        return 1;
    }

    char* input_file_name = strdup(argv[1]);
    char* base_folder = dirname(argv[0]);  // dirname(argv[1]);
    unsigned int filled_buffer_size = 0;
    unsigned char* in_buffer = (unsigned char*) malloc(BUFFER_SIZE);
    unsigned char* out_buffer;
    unsigned char* new_file_name;
    unsigned int i;

    // Open and read the contents of file
    FILE* file = fopen(input_file_name, "rb");
    fread(in_buffer, BUFFER_SIZE, 1, file);
    fclose(file);


    // Determine the write buffer size
    for (; filled_buffer_size < BUFFER_SIZE; filled_buffer_size++)
    {
        if (in_buffer[filled_buffer_size] == '\0')
        {
            break;
        }
    }

    if (strcmp(file_extension(input_file_name), ".blx") == 0)  // Decompressing
    {
        // Extract the file extension
        char* file_ext = ".txt";

        new_file_name = (unsigned char*) malloc(FILENAME_MAX);
        sprintf(new_file_name, "%s\\%s%s", base_folder, "test_decompressed", file_ext);
        out_buffer = (unsigned char*) malloc(BUFFER_SIZE);

        // Decompressing into the out_buffer
        /// TODO

        free(file_ext);
    }
    else  // Compressing
    {
        new_file_name = (unsigned char*) malloc(FILENAME_MAX);
        sprintf(new_file_name, "%s\\%s", base_folder, "test.blx");

        // Write the file extension in the file
        char* file_ext = file_extension(input_file_name);

        for (i = 0; i < strlen(file_ext); i++)
        {
            in_buffer[filled_buffer_size++] = file_ext[i];
        }

        out_buffer = (unsigned char*) malloc(BUFFER_SIZE);

        // Compressing file contents into out_buffer
        /// TODO
    }

    // Open the new file for reading
    FILE* output_file = fopen(new_file_name, "wb");
    fwrite(in_buffer, filled_buffer_size, 1, output_file);
    fclose(output_file);

    free(in_buffer);
    free(out_buffer);
    free(new_file_name);
    return 0;
}

