#include <fcntl.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libgd/src/gd.h"
#define KYEL "\x1B[33m"
#define KBLU "\x1B[34m"
#define KRED "\x1B[31m"
#define KMAG "\x1B[35m"
#define RESET "\x1B[0m"

struct buff histogramEqualization(struct buff a, char *buffName)
{
    // gdImageGrayScale(a.imrgb);
    /*calculate frequencies & get max grey level value*/
    struct buff temp = a;
    int max = 0;
    int freq[256];
    for (int i = 0; i < 256; i++)
    {
        freq[i] = 0;
    }

    for (int r = 0; r < temp.width; r++)
    {
        for (int c = 0; c < temp.height; c++)
        {
            int pos = gdImageGetPixel(temp.imrgb, r, c);
            int grey = (gdTrueColorGetRed(pos) + gdTrueColorGetGreen(pos) + gdTrueColorGetBlue(pos)) / 3;
            freq[grey]++;
            if (grey > max)
                max = grey;
        }
    }

    // printf("frequency list \n");
    // for(int i=0; i<256; i++){
    //     printf("%d: %d\n", i, freq[i]);
    // }

    /*frequency divided by total num of pixels*/
    //printf("pdf list \n");
    int total = temp.height * temp.width;
    float pdf[256];
    int check = 0;
    for (int i = 0; i < 256; i++)
    {
        pdf[i] = (float)freq[i] / (float)total;
        // printf("%d: %f\n", i, pdf[i]);
        check += freq[i];
    }

    // printf("check: %d \ntotal: %d\n\n", check, total);

    // printf("cdf\n");

    /*cummulative distribution function*/
    float cdf[256];
    for (int i = 0; i < 256; i++)
    {
        if (i != 0)
            cdf[i] = cdf[i - 1] + pdf[i];
        else
            cdf[i] = pdf[i];
        // printf("%f\n", cdf[i]);
    }

    //printf("map\n");

    // cdf * max grey level
    int histmap[256];
    for (int i = 0; i < 256; i++)
    {
        histmap[i] = max * cdf[i];
        //printf("%d\n", histmap[i]);
    }

    /*map orginial*/

    gdImagePtr out = gdImageCreateTrueColor(temp.width, temp.height);
    for (int r = 0; r < temp.width; r++)
    {
        for (int c = 0; c < temp.height; c++)
        {
            int pos = gdImageGetPixel(temp.imrgb, r, c);
            int red = gdTrueColorGetRed(pos);
            int green = gdTrueColorGetGreen(pos);
            int blue = gdTrueColorGetBlue(pos);
            int grey = (red + green + blue) / 3;
            int numerator = histmap[grey];
            float ratio;
            if (grey == 0)
            {
                ratio = 0;
            }
            else
            {
                ratio = (float)numerator / grey;
            }
            int newRed = ratio * red;
            int newBlue = ratio * blue;
            int newGreen = ratio * green;
            gdImageSetPixel(out, r, c, gdImageColorAllocate(temp.imrgb, newRed, newGreen, newBlue));
        }
    }
    temp.isLibgd = 1;
    strcpy(temp.name, "histeq");
    strcpy(temp.imageName, "HisteQ.jpg");
    temp.imrgb = out;

    printf(KYEL "Done equalizing!\n\n" RESET);

    return temp;
}