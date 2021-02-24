#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include "libgd/src/gd.h"

struct buff rightRotate(struct buff a)
{

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

struct buff leftRotate(struct buff a)
{
    struct buff temp = a;
    temp.isLibgd = true;
    temp.height = a.width;
    temp.width = a.height;
    gdImagePtr out = gdImageRotateInterpolated(a.imrgb, 270.0, 0);

    /* I uncommented the following lines */
    char outName[50];
    strcpy(outName, "Left-");
    char *t = strtok(a.imageName, ".");
    strcat(outName, t);

    FILE *output = fopen(strcat(outName, ".png"), "wb");
    gdImagePngEx(out, output, 9);

    printf("Done rotating!\n");

    return temp;
}