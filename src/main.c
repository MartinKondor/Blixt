#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


typedef struct Record
{
    /**
    I got this from SO. I have no idea why it works.
    */
    int x, y, z;
} Record;

/**
* Copies the contents of string a to b
*/
void copy_str(char* from_str, char* to_str)
{
    // Clear to_str
    memset(to_str, 0, strlen(to_str));

    for (size_t i = 0; i < strlen(from_str); i++)
    {
        to_str[i] = from_str[i];
    }
}

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
* @return "record.x,record.y,record.z;"
*/
char* record_to_str(Record record)
{
    char* record_str = (char*) malloc(100 * sizeof(char));
    sprintf(record_str, "%d,%d,%d;", record.x, record.y, record.z);
    return record_str;
}

/**
* Compresses file to the given out_file_name
*/
void compress_file(char* file_name, char* out_file_name)
{
    FILE* file_ptr;
    FILE* out_file_ptr;

    // Open files
    file_ptr = fopen(file_name, "rb");
    out_file_ptr = fopen(out_file_name, "w");

    if (!file_ptr)
    {
        perror("Unable to open the input file(s).\n");
        system("pause");
        exit(1);
    }

    fseek(file_ptr, sizeof(Record), SEEK_END);
    rewind(file_ptr);

    // First, write in the file extension
    char* fext = file_extension(file_name);
    fwrite(fext, sizeof(char), strlen(fext) * sizeof(char), out_file_ptr);
    free(fext);
    fwrite(";", 1, 1, out_file_ptr);

    Record record;
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
        // if (record.x == prev_record.x && record.y == prev_record.y && record.z == prev_record.z) fwrite("*", 1, 1, out_file_ptr);
        // printf("%d, %d, %d\n", record.x, record.y, record.z);
        // fwrite(&record, sizeof(struct Record), 1, out_file_ptr);
    }

    fclose(file_ptr);
    fclose(out_file_ptr);
}

/**
* Decompresses file to the given out_file_name
*/
void decompress_file(char* file_name, char* out_file_name)
{
    FILE* file_ptr;

    // Open files
    file_ptr = fopen(file_name, "rt");

    if (!file_ptr)
    {
        perror("Unable to open the input file(s).\n");
        system("pause");
        exit(1);
    }

    char c;
    char file_ext[32];
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

    char* new_out_file_name = (char*) malloc(FILENAME_MAX * sizeof(char));
    sprintf(new_out_file_name, "%s%s", out_file_name, file_ext);

    // Open new out file
    FILE* out_file_ptr;
    out_file_ptr = fopen(new_out_file_name, "wb");

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

            switch (current_record_index)
            {
                case 0:
                    record.x = atoi(current_record_str);
                    break;
                case 1:
                    record.y = atoi(current_record_str);
                    break;
                case 2:
                    record.z = atoi(current_record_str);
                    break;
            }

            memset(current_record_str, 0, strlen(current_record_str));
            current_record_str_index = 0;

            if (c == ';')
            {
                // Write record
                fwrite(&record, sizeof(struct Record), 1, out_file_ptr);
                current_record_index = 0;
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
    free(new_out_file_name);
    free(current_record_str);
}

int main(int argc, char** argv)
{
    // Check for the file's existence
    if (argc < 2 || access(argv[1], F_OK) == -1)
    {
        perror("No input file(s) provided.\n");
        system("pause");
        return 1;
    }

    //compress_file("bin/test.tcm", "bin/test.blx");
    decompress_file("bin/test.blx", "bin/test_decompressed");

    return 0;
}

