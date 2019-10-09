#include "decompress.h"


void decompress_file(char* file_name, char* out_file_name)
{
    FILE* file_ptr;

    // Open the input file
    file_ptr = fopen(file_name, "rt");

    if (file_ptr == 0)
    {
        printf("%s :: %s\n", file_name, out_file_name);
        perror("Unable to open the input file(s). (decompressing)\n");
        system("pause");
        exit(1);
    }

    char file_ext[32];
    file_extension_from_blx(file_ptr, &file_ext);

    // Determine the output file name
    char* new_out_file_name = (char*) malloc(FILENAME_MAX * sizeof(char));
    sprintf(new_out_file_name, "%s%s", out_file_name, file_ext);

    // Open new out file
    FILE* out_file_ptr;
    out_file_ptr = fopen(new_out_file_name, "wb");
    free(new_out_file_name);

    char c;
    char* current_record_str = (char*) malloc(128 * sizeof(char));
    int current_record_str_index = 0;
    int current_record_index = 0;
    Record record;

    // Start reading in the records and writing them to the outfile
    while ((c = fgetc(file_ptr)) != EOF)
    {
        if (c == ',' || c == ';')
        {
            current_record_str[current_record_str_index] = '\0';

            // printf("%d\n", (int) strtol(current_record_str, NULL, 16));

            switch (current_record_index)
            {
                case 0:
                    //record.x = atoi(current_record_str);
                    record.x = (int) strtol(current_record_str, NULL, 16);
                    break;
                case 1:
                    //record.y = atoi(current_record_str);
                    record.y = (int) strtol(current_record_str, NULL, 16);
                    break;
                case 2:
                    //record.z = atoi(current_record_str);
                    record.z = (int) strtol(current_record_str, NULL, 16);
                    break;
            }

            memset(current_record_str, 0, strlen(current_record_str));
            current_record_str_index = 0;

            if (c == ';')  // Write record
            {
                fwrite(&record, sizeof(Record), 1, out_file_ptr);
                current_record_index = 0;
                record.x = 0;
                record.y = 0;
                record.z = 0;
            }
            else
            {
                current_record_index++;
            }
            continue;
        }

        current_record_str[current_record_str_index++] = c;
    }

    fclose(out_file_ptr);
    fclose(file_ptr);
    free(current_record_str);
}

void file_extension_from_blx(FILE* file_ptr, char* file_ext)
{
    char c;
    int file_ext_index = 0;

    // First, get the file extension
    while ((c = fgetc(file_ptr)) != EOF)
    {
        if (c == ';')
        {
            break;
        }

        file_ext[file_ext_index++] = c;
    }

    file_ext[file_ext_index] = '\0';
}
