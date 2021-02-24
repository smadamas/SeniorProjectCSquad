#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include "libgd/src/gd.h"

struct buff rightRotate(struct buff a)
{

    struct buff temp = a;
    temp.isLibgd = 1;
    temp.height = a.width;
    temp.width = a.height;
    strcpy(temp.name, "rightR");
    gdImagePtr out = gdImageRotateInterpolated(a.imrgb, 270.0, 0);
    temp.imrgb = out;

    printf("Done rotating!\n");

    return temp;
}

struct buff leftRotate(struct buff a)
{
    struct buff temp = a;
    temp.isLibgd = true;
    temp.height = a.width;
    temp.width = a.height;
    strcpy(temp.name, "leftR");
    gdImagePtr out = gdImageRotateInterpolated(a.imrgb, 90.0, 0);
    temp.imrgb = out;

    printf("Done rotating!\n");

    return temp;
}