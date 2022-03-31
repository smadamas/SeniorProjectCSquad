#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <setjmp.h>
#include "gd.h"

bool checkImageFileExists(char* const fileName) //returns true if file exists (stat() returns 0)
{
    struct stat buf;
    int fileStatus = stat(fileName, &buf);
    if(fileStatus == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool checkBufferExists(char* const bufferStatus)
{
    if(strcmp("false", bufferStatus) == 0)
        return false;
    else
        return true;
}