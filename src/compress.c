#include "compress.h"


void compress_file(char* file_name, char* out_file_name)
{
    FILE* file_ptr;
    FILE* out_file_ptr;

    // Open files
    file_ptr = fopen(file_name, "rb");
    out_file_ptr = fopen(out_file_name, "w");

    if (file_ptr == 0 || out_file_ptr == 0)
    {
        printf("%s :: %s\n", file_name, out_file_name);
        perror("Unable to open the input file(s). (compressing)\n");
        system("pause");
        exit(1);
    }

    fseek(file_ptr, sizeof(Record), SEEK_END);
    rewind(file_ptr);

    // First, write in the file's extension
    char* fext = file_extension(file_name);
    fwrite(fext, sizeof(char), strlen(fext) * sizeof(char), out_file_ptr);
    fwrite(";", 1, 1, out_file_ptr);

    Record record;
    Record prev_record;
    size_t status = 1;
    char* wirte_str;

    record.x = 0;
    record.y = 0;
    record.z = 0;

    // Start reading and writing to files
    while (status != 0)
    {
        status = fread(&record, sizeof(Record), 1, file_ptr);
        wirte_str = record_to_str(record);
        fwrite(wirte_str, sizeof(char), strlen(wirte_str) * sizeof(char), out_file_ptr);

        // If the records are the same put a * in the out_file
        if (record.x == prev_record.x && record.y == prev_record.y && record.z == prev_record.z)
        {
            // fwrite("*", 1, 1, out_file_ptr);
        }
        // printf("%d, %d, %d\n", record.x, record.y, record.z);
        // fwrite(&record, sizeof(struct Record), 1, out_file_ptr);

        memcpy(&prev_record, &record, sizeof(record));
    }

    fclose(file_ptr);
    fclose(out_file_ptr);
}
