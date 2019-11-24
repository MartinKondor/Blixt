#include "decompress.h"


void decompress_file(char* file_name)
{
    FILE* file_ptr = fopen(file_name, "rb");
    unsigned int output_buffer_size = 10240;
    unsigned int out_index = 0;
    char* output_buffer = malloc(output_buffer_size);
    char* tmp_output_buffer = NULL;
    char ch = fgetc(file_ptr);

    while (ch != EOF)
    {
        // Allocate more memory if needed
        if (out_index >= output_buffer_size)
        {
            output_buffer_size += 10240;
            tmp_output_buffer = realloc(output_buffer, output_buffer_size);

            if (tmp_output_buffer != NULL)
            {
                output_buffer = tmp_output_buffer;
            }
            else
            {
                printf("Error at reallocating memory.");
                free(output_buffer);
                exit(1);
            }
        }

        output_buffer[out_index++] = ch;
        ch = fgetc(file_ptr);
    }

    fclose(file_ptr);
    output_buffer[out_index] = '\0';  // Adding the terminating character

    // Free up some memory
    memmove(output_buffer, output_buffer - (strlen(output_buffer) - out_index), strlen(output_buffer));

    // Remove blx file extension name
    file_name[strlen(file_name) - 4] = '\0';

    // Processing the compressed file contents
    /// TODO

    free(output_buffer);
    if (tmp_output_buffer != NULL) free(tmp_output_buffer);
}
