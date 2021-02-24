#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include "libgd/src/gd.h"

struct buff rightRotate(struct buff a)
{

    printf("Image info: %s\n", a.img);

    struct buff temp = a;
    temp.isLibgd = true;
    temp.height = a.width;
    temp.width = a.height;
    gdImagePtr out = gdImageRotateInterpolated(a.imrgb, 90.0, 0);

    /* I uncommented the following lines */
    char outName[50];
    strcpy(outName, "Right-");
    char *t = strtok(a.imageName, ".");
    strcat(outName, t);

    FILE *output = fopen(strcat(outName, ".png"), "wb");
    gdImagePngEx(out, output, 9);

    printf("Done rotating!\n");

    return temp;
}

/*struct buff leftRotate(struct buff a)
{
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
    strcpy(temp.name, "flipV");
    strcpy(temp.imageName, "flipV.jpg");
    return temp;
}*/