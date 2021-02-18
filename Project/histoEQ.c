// C program to perform histogram equalisation to adjust contrast levels

#include <fcntl.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libgd/src/gd.h"


void histogramEqualization(struct buff a, char *buffName){
    // gdImageGrayScale(a.imrgb);
    /*calculate frequencies & get max grey level value*/
    int max = 0;
    int freq[256];
    for(int i = 0; i<256; i++){
        freq[i]=0;
    }

    for(int r=0; r < a.width; r++){
        for(int c=0; c < a.height; c++){
            int pos = gdImageGetPixel(a.imrgb, r, c);
            int grey = (gdTrueColorGetRed(pos) + gdTrueColorGetGreen(pos) + gdTrueColorGetBlue(pos))/3;
            freq[grey]++;
            if(grey>max)
                max=grey;
        }
    }

    // printf("frequency list \n");
    // for(int i=0; i<256; i++){
    //     printf("%d: %d\n", i, freq[i]);
    // }

    /*frequency divided by total num of pixels*/
    //printf("pdf list \n");
    int total = a.height*a.width;
    float pdf[256];
    int check = 0;
    for(int i=0; i<256; i++){
        pdf[i]=(float)freq[i]/(float)total;
        // printf("%d: %f\n", i, pdf[i]);
        check += freq[i];
    }

    // printf("check: %d \ntotal: %d\n\n", check, total);

    // printf("cdf\n");

    /*cummulative distribution function*/
    float cdf[256];
    for(int i=0; i < 256; i++){
        if(i!=0)
            cdf[i]=cdf[i-1]+pdf[i];
        else
            cdf[i] = pdf[i];
        // printf("%f\n", cdf[i]);
    }


    
    //printf("map\n");

    // cdf * max grey level
    int histmap[256];
    for(int i =0; i < 256; i++){
        histmap[i]=max*cdf[i];
        //printf("%d\n", histmap[i]);
    }

    /*map orginial*/

    gdImagePtr out = gdImageCreateTrueColor(a.width, a.height);
    for(int r=0; r < a.width; r++){
        for(int c=0; c < a.height; c++){
            int pos = gdImageGetPixel(a.imrgb, r, c);
            int red = gdTrueColorGetRed(pos);
            int green = gdTrueColorGetGreen(pos);
            int blue = gdTrueColorGetBlue(pos);
            int grey = (red + green + blue)/3;
            int numerator = histmap[grey];
            float ratio;
            if(grey==0){
                ratio=0;
            }else{
                ratio = (float)numerator/grey;
            }
            int newRed = ratio*red;
            int newBlue = ratio*blue;
            int newGreen = ratio*green;
            gdImageSetPixel(out, r, c, gdImageColorAllocate(a.imrgb, newRed, newGreen, newBlue));
            
        }
    }

    /*gdImageOut*/

    char outName[50];
    strcpy(outName, "histo-eq-");
    char* temp = strtok(a.imageName, ".");
    strcat(outName, temp);

    FILE* output = fopen(strcat(outName,".png"), "wb");
	gdImagePngEx(out, output, 9);

    printf("Done equalizing!\n");
}


