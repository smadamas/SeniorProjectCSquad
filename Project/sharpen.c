#include "libgd/src/gd.h"
struct buff sharpen(struct buff input, char * resultName){
    float mask[3][3] = {
        {0, -1, 0},
        {-1, 5, -1},
        {0, -1, -0}
    };

    struct buff temp = input;
    temp.isLibgd = 1;
    gdImagePtr src = input.imrgb;
    strcpy(temp.name, resultName);

    char name[50];
    strcpy(name, "sharpened-");
    strcat(name, temp.imageName);
    strcpy(temp.imageName, name);

    gdImageConvolution(src, mask, 1.0, 0.0);
    temp.imrgb = src;
    return temp;
}