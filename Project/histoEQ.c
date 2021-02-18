// C program to perform histogram equalisation to adjust contrast levels

#include <fcntl.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libgd/src/gd.h"


struct buff histogramEqualization(struct buff a, char *buffName){
    // gdImageGrayScale(a.imrgb);
    //calculate frequencies & get max grey level value
    int max = 0;
    int freq[256];
    for(int i = 0; i<256; i++){
        freq[i]=0;
    }

    for(int r=0; r < a.width; r++){
        for(int c=0; c < a.height; c++){
            int pos = gdImageGetPixel(a.imrgb, r, c);
            int grey = (gdTrueColorGetRed(pos) + gdTrueColorGetGreen(pos) + gdTrueColorGetBlue(pos))/3;
            //printf("%d ", grey);
            freq[grey]++;
            if(grey>max)
                max=grey;
        }
        //printf("\n");
    }

    printf("frequency list \n");
    for(int i=0; i<256; i++){
        printf("%d: %d\n", i, freq[i]);
    }

    //frequency divided by total num of pixels
    printf("pdf list \n");
    int total = a.height*a.width;
    float pdf[256];
    int check = 0;
    for(int i=0; i<256; i++){
        pdf[i]=(float)freq[i]/(float)total;
        printf("%d: %f\n", i, pdf[i]);
        check += freq[i];
    }

    printf("check: %d \ntotal: %d\n\n", check, total);

    printf("cdf\n");

    //cummulative distribution function
    float cdf[256];
    cdf[0]=pdf[0];
    for(int i=1; i < 256; i++){
        cdf[i]=cdf[i-1]+pdf[i];
        printf("%f\n", cdf[i]);
    }


    
    printf("map\n");

    // cdf * max grey level
    int histmap[256];
    for(int i =0; i < 256; i++){
        histmap[i]=max*cdf[i];
        printf("%d\n", histmap[i]);
    }

    //map orginial

    //gdImagePtr out = gdImageCreate(a.width, a.height);
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
            gdImageSetPixel(a.imrgb, r, c, gdImageColorAllocate(a.imrgb, newRed, newGreen, newBlue));
            //printf("%d ", (newRed+newBlue+newGreen)/3);
            
        }
        //printf("\n");
    }

    //gdImag

    FILE* output = fopen("temp.png", "wb");
	gdImagePngEx(a.imrgb, output, 9);


    
    struct buff temp;
    return temp;
}



// Function to perform histogram equalisation on an image
// Function takes total rows, columns, input file

// struct buff histogramEqualisation(struct buff a, char *buffName)
// {
//     // FILE* out = fopen("temp.png", "wb");
// 	// gdImagePngEx(a.imrgb, out, 9);


//     // creating image pointer
//     unsigned char* image;

//     //Instantiating Rows and Cols
//     int cols = a.width;
//     int rows = a.height;
//     //printf("\n\n%d", a.channels);

//     size_t s = cols * rows * a.channels;
//     unsigned char * grey;
//     grey = calloc(rows*cols,sizeof(unsigned char));
    

//     // Declaring 2 arrays for storing histogram values (frequencies) and
//     // new gray level values (newly mapped pixel values as per algorithm)
//     int hist[256];
//     int new_gray_level[256];

//     for (int i = 0; i < 256; i++){
//         hist[i] = 0;
//         new_gray_level[i] = 0;
//     }

//     // Declaring other important variables
//     int col, row, total, i;
//     unsigned long curr, cdf_min;
//     total = cols * rows * a.channels;
//     const unsigned char* limit = a.img + total;
//     curr = 0;

 
//     //Convert to greyscale
    

//     for(int r=0; r < a.width; r++){
//         for(int c=0; c < a.height; c++){
//             int pos = gdImageGetPixel(a.imrgb, r, c);
//             *grey = (unsigned char)((0.3*gdTrueColorGetRed(pos)) + (0.59*gdTrueColorGetGreen(pos)) + (0.11*gdTrueColorGetBlue(pos)));
//             grey++;
//         }
//     }

//     // Calculating frequency of occurrence for all pixel values
//     // New way 

//     unsigned char* img;
//     unsigned char* greyLimit = grey + (rows*cols);

//     for(img = grey; img < greyLimit; img++){
//         hist[*img]++;
//     }

//     // calculating CDF
//     float cdf[256];
//     for (i = 0; i < 256; i++){
//         // cumulative frequency
//         curr += hist[i];
//         cdf[i] = curr;
//     }

//     cdf_min = 255;
//     for(i = 0; i < 256; i++){
//         if(cdf[i] < cdf_min){
//             cdf_min = cdf[i];
//         }
//     }

//     //Allocate for output
//     struct buff newBuff;
//     size_t size = cols * rows; // Allocate memory for result
//                                                                      // unsigned char *result_img = malloc(size * sizeof(unsigned char));
//     unsigned long* result;
//     result = (unsigned long *)calloc(size, sizeof(unsigned long));

//     if (result == NULL)
//     {
//         printf("Unable to allocate memory for the histogram.\n");
//         exit(1);
//     }

//     unsigned char* result_img;
//     result_img = (unsigned char *)calloc(size, sizeof(unsigned char));

//     if (result_img == NULL)
//     {
//         printf("Unable to allocate memory for the image.\n");
//         exit(1);
//     }

//     const double k = 255.0 / ((cols*rows) - cdf_min);

//     //old grey level "i" maps to new grey level "result[i]"
//     for (i = 0; i < 256; i++)
//     {
//         result[i] = (unsigned long)(k*(cdf[i] - cdf_min));
//     }

//     int index = 0;
//     for (img = grey; img < greyLimit; img++){
//         result_img[index] = (unsigned char)result[(int)(*img)];
//         result_img++; //Increment output pointer
//         index++;
//     }


//     // Fill in info for buffer
//     strcpy(newBuff.imageName, a.imageName);
//     strcpy(newBuff.name, a.name);
//     newBuff.width = a.width;
//     newBuff.height = a.height;
//     newBuff.channels = 1;

//     char *ext;
//     ext = strstr(a.imageName, ".png");
//     if (ext == NULL)
//         ext = strstr(a.imageName, ".jpg");
//     if (ext == NULL)
//         ext = strstr(a.imageName, ".tiff");
//     if (ext == NULL)
//         ext = strstr(a.imageName, ".gif"); // Use extension of a for extension of result


//     newBuff.img = result_img;

//     // freeing dynamically allocated memory
//     // free(result_img);
//     printf("Done Equalizing");

//     return newBuff;
// }
