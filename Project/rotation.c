#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include "libgd/src/gd.h"

struct buff rightRotate(struct buff a)
{
    char input[100];
    printf("Enter name of buffer: \n");
    gets(input);
    struct buff temp = a;
    temp.isLibgd = 1;
    temp.height = a.width;
    temp.width = a.height;
    strcpy(temp.name, input);
    gdImagePtr out = gdImageRotateInterpolated(a.imrgb, 270.0, 0);
    temp.imrgb = out;

    printf("Done rotating!\n");

    return temp;
}

struct buff leftRotate(struct buff a)
{
    char input[100];
    printf("Enter name of buffer: \n");
    gets(input);
    struct buff temp = a;
    temp.isLibgd = 1;
    temp.height = a.width;
    temp.width = a.height;
    strcpy(temp.name, input);
    gdImagePtr out = gdImageRotateInterpolated(a.imrgb, 90.0, 0);
    temp.imrgb = out;

    printf("Done rotating!\n");

    return temp;
}

struct buff horizontalFlip(struct buff a)
{
    char input[100];
    printf("Enter name of buffer: \n");
    gets(input);
    struct buff temp = a;
    gdImageFlipHorizontal(temp.imrgb);
    temp.isLibgd = 1;
    strcpy(temp.name, input);
    strcpy(temp.imageName, "flipH.jpg");
    return temp;
}

struct buff verticalFlip(struct buff a)
{
    char input[100];
    printf("Enter name of buffer: \n");
    gets(input);
    struct buff temp = a;
    int rows = temp.height / 2;
    int row_stride = temp.width * temp.channels;
    unsigned char *temp_row = (unsigned char *)malloc(row_stride);
    int source_offset, target_offset;
    for (int rowIndex = 0; rowIndex < rows; rowIndex++)
    {
        source_offset = rowIndex * row_stride;
        target_offset = (temp.height - rowIndex - 1) * row_stride;

        memcpy(temp_row, temp.img + source_offset, row_stride);
        memcpy(temp.img + source_offset, temp.img + target_offset, row_stride);
        memcpy(temp.img + target_offset, temp_row, row_stride);
    }
    strcpy(temp.name, input);
    strcpy(temp.imageName, "flipV.jpg");
    return temp;
}
