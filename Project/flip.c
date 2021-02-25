#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "libgd/src/gd.h"

struct buff verticalFlip(struct buff a)
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
}

struct buff horizontalFlip(struct buff a)
{
    struct buff temp = a;
    temp.isLibgd = true;
    temp.height = a.width;
    temp.width = a.height;
    strcpy(temp.name, "flipH");
    gdImageFlipHorizontal(a.imrgb);
    temp.imrgb = a.imrgb;

    printf("Done flipping!\n");

    return temp;
}



// //Get mem address of pixel
// unsigned char * get_pixel_address(unsigned char* base, int line_stride, int pixel_stride, int x, int y){
//     return base + (y * line_stride) + (x * pixel_stride);
// }

//Assuming Pixel Stride of 32, bit depth of 24 (RGB)
// struct buff horizontalFlip(struct buff a){
//     const int pixel_stride = a.channels * (int)sizeof(unsigned char);
//     const int line_stride = (a.channels * (int)sizeof(unsigned char)) * a.width;

//     //Starting Pixel
//     unsigned char * src;
//     unsigned char* beginning = a.img + ((a.width - 1) * (pixel_stride));
//     unsigned char * result_img = (unsigned char *)malloc(sizeof(unsigned char)*a.width*a.height*a.channels);
//     unsigned char * dest = result_img;
//     int pxcount = 0;
//     for(int i=0; i < a.height-1; i++){
//         for(int j=0; j < a.width-1; j++){
//             //Negate the pixel stride so the image can be read flipped horizontally
//             src = get_pixel_address(beginning, line_stride, -pixel_stride, i, j);
            
//             //Copy a pixel
//             memcpy(dest, src, pixel_stride);

//             //Increment By a pixel
//             dest += pixel_stride;
//         }
//     }

//     struct buff result = a;
//     result.img = result_img;
//     strcpy(result.name, "flipH");
//     strcpy(result.imageName, "flipH.jpg");
//     return result;
// }