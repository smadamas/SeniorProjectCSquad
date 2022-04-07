#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <setjmp.h>
#include "gd.h"
/**
 * Checks for the existence of a non-directory file on the system .
 * \param fileName C-String relative path/to/file
 * 
 * \return returns boolean true if a file is found, otherwise false.
 */
bool checkImageFileExists(char* const fileName)
{
    struct stat st;
    int fileStatus = stat(fileName, &st);
    if(fileStatus == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
/**
 * Checks if a buffer exists based on the value of buff.status.
 * \param bufferStatus string value of a buffer object's status variable.
 * 
 * \return returns boolean true if the status denotes a valid buffer, otherwise false.
 */
bool checkBufferExists(char* const bufferStatus)
{
    if(strcmp("false", bufferStatus) == 0)
        return false;
    else
        return true;
}