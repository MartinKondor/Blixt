#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


struct Record
{
    /**
    I got this from SO. I have no idea why it works.
    */
    int x, y, z;
};

/**
* @return str's length
*/
size_t strlen(char* str)
{
    size_t i = 0;
    for (i = 0; str[i] != '\0'; ++i);
    return i;
}

/**
* @return file_name's extension
*/
char* file_extension(char* file_name)
{
    char* file_ext = (char*) malloc(strlen(file_name) * sizeof(char));
    int j = 0;

    for (int i = strlen(file_name) - 1; i >= 0; i--)
    {
        if (file_name[i] == '.')
            break;
        file_ext[j++] = file_name[i];
    }
    return file_ext;
}

/**
* @return "record.x,record.y,record.z;"
*/
char* record_to_str(struct Record record)
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
    struct Record record;
    struct Record prev_record;
    FILE* file_ptr = fopen(file_name, "rb");
    FILE* out_file_ptr = fopen(out_file_name, "w");
    char* fext = file_extension(file_name);

    if (!file_ptr)
    {
        perror("Unable to open the input file(s).\n");
        system("pause");
        exit(1);
    }

    fseek(file_ptr, sizeof(struct Record), SEEK_END);
    rewind(file_ptr);

    fwrite(fext, sizeof(char), strlen(fext) * sizeof(char), out_file_ptr);
    fwrite(";", 1, 1, out_file_ptr);
    size_t status = 1;
    char* wirte_str;

    while (status != 0)
    {
        status = fread(&record, sizeof(struct Record), 1, file_ptr);
        wirte_str = record_to_str(record);
        fwrite(wirte_str, sizeof(char), strlen(wirte_str) * sizeof(char), out_file_ptr);

        // If the records are the same put a * in the out_file
        if (record.x == prev_record.x && record.y == prev_record.y && record.z == prev_record.z)
        {
            // fwrite("*", 1, 1, out_file_ptr);
        }

        // printf("%d, %d, %d\n", record.x, record.y, record.z);
        // fwrite(&record, sizeof(struct Record), 1, out_file_ptr);
        prev_record = record;
    }

    fclose(file_ptr);
    fclose(out_file_ptr);
    free(fext);
}

/**
* Decompresses file to the given out_file_name
*/
void decompress_file(char* file_name, char* out_file_name)
{
    FILE* file_ptr = fopen(file_name, "rt");
    FILE* out_file_ptr = fopen(out_file_name, "w");

    if (!file_ptr)
    {
        perror("Unable to open the input file(s).\n");
        system("pause");
        exit(1);
    }

    // Start reading the file
    char c;
    char* read_str;
    struct Record record;

    record.x = 0;
    record.y = 0;
    record.z = 0;

    while ((c = fgetc(file_ptr)) != EOF)
    {
        if (c == ';')
        {
            // fwrite(&record, sizeof(struct Record), 1, out_file_ptr);

            record.x = 0;
            record.y = 0;
            record.z = 0;

            memset(read_str, 0, strlen(read_str));
            continue;
        }
        else if (c == ',')
        {
            int rec = atoi(read_str);
            printf("%d\n", rec);

            memset(read_str, 0, strlen(read_str));
            continue;
        }

        strncat(read_str, &c, 1);
    }

    fclose(file_ptr);
    fclose(out_file_ptr);
    free(read_str);
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

    compress_file("bin/test.txt", "bin/test.blx");
    decompress_file("bin/test.blx", "bin/test_decompressed");

    return 0;
}
