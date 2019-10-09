#include "record.h"


char* record_to_str(Record record)
{
    char* record_str = (char*) malloc(100 * sizeof(char));
    sprintf(record_str, "%x,%x,%x;", record.x, record.y, record.z);
    return record_str;
}
