#include "compress.h"


void compress_file(char* file_name)
{
    FILE* file_ptr;
    file_ptr = fopen(file_name, "rb");

    if (file_ptr == NULL)
    {
        printf("Cannot open file (%s).\n", file_name);
        exit(0);
    }

    char ch = fgetc(file_ptr);
    char prev_ch = '\0';
    char* output_buffer = malloc(1024);
    unsigned int counter = 0;
    unsigned int out_index = 0;

    while (ch != EOF)
    {
        if (ch == prev_ch)
        {
            counter++;
        }
        else
        {
            // Write character to buffer
            if (counter > 0)
            {
                // Write counter to buffer
                char* counter_str = malloc(16);  // The counter can have max 16 digits
                sprintf(counter_str, "{%u}", counter + 1);

                // Add counter string char by char
                for (unsigned int i = 0; i < strlen(counter_str); i++)
                {
                    output_buffer[out_index++] = counter_str[i];
                }

                free(counter_str);
            }

            output_buffer[out_index++] = '|';
            output_buffer[out_index++] = ch;
            prev_ch = ch;
            counter = 0;
        }
        ch = fgetc(file_ptr);
    }

    fclose(file_ptr);
    output_buffer[out_index] = '\0';  // Adding the terminating character

    // Write the original file extension
    // into the output buffer
    char* file_ext = file_extension(file_name);
    sprintf(output_buffer, "%s;%s", output_buffer, file_ext);
    out_index += strlen(file_ext) + 1;

    // Free up some memory
    memmove(output_buffer, output_buffer - (strlen(output_buffer) - out_index), strlen(output_buffer));

    // Write output buffer to a new file
    // FILE* output_file_ptr;
    printf(output_buffer);

    free(output_buffer);
    // char* file_ext = file_extension(file_name);
    // printf("%s, %s", file_name, file_ext);
}
