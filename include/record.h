#ifndef RECORD_H
#define RECORD_H

#include <stdio.h>
#include <stdlib.h>


typedef struct Record
{
    int x, y, z;
} Record;

/**
* @return "record.x,record.y,record.z;"
*/
char* record_to_str(Record record);

#endif // RECORD_H
