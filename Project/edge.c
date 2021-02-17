#include "libgd/src/gd.h"


void detectEdge(char* orientation, char* type, char* imageName){
    FILE *in;
    //Src holds the input image's data and output data, copy holds a copy of the input in case of a combined command
    gdImagePtr src, copy;
    char* temp = strtok(imageName, ".");
    char* ext = strtok(NULL," ");
    int extType;

    float kirsch_mask_horiz[3][3] = {
    { 5, 5, 5},
    {-3, 0, -3},
    {-3, -3, -3} };
    float kirsch_mask_vert[3][3] = {
    { 5, -3, -3},
    {5, 0, -3},
    {5, -3, -3} };
    float prewitt_mask_vert[3][3] = {
    {1, 0, -1},
    {1, 0, -1},
    {1, 0, -1} };
    float prewitt_mask_horiz[3][3] = {
    { 1,  1,  1},
    { 0,  0,  0},
    {-1, -1, -1} };
    float sobel_mask_horiz[3][3] = {
    {1, 0, -1},
    {2, 0, -2},
    {1, 0, -1} };
    float sobel_mask_vert[3][3] = {
    { 1,  2,  1},
    { 0,  0,  0},
    {-1, -2, -1} };
        
    if (strcmp(ext, "png")==0){
        in = fopen(strcat(temp, ".png"), "rb");
        extType = 1;
    }
    else if (strcmp(ext, "jpg")==0 || strcmp(ext, "jpeg")==0){
        in = fopen(strcat(temp, ".jpeg"), "rb");
        extType = 2;
    }
    else if (strcmp(ext, "gif")==0){
        in = fopen(strcat(temp, ".gif"), "rb");
        extType = 3;
    }
    else {
        printf("This file type is not supported by this function.\n");
        return;
    }

    src = gdImageCreateFromPng(in);
    gdImageGrayScale(src);
    if(strcmp(type, "kirsch")==0){             
        if(strcmp(orientation, "vertical")==0){
            gdImageConvolution(src, kirsch_mask_vert, 1.0,0.0);
 			FILE *out;
			char name[50];
			strcpy(name, "kirsch-");
			strcat(name, orientation);
			strcat(name, "-");
			strcat(name, temp);
			out = fopen(name, "wb");
			gdImagePngEx(src, out, 9);                  
			fclose(out);                               
			gdImageDestroy(src);
			return;
        }
        else if(strcmp(orientation, "horizontal")==0){
            gdImageConvolution(src, kirsch_mask_horiz, 1.0,0.0);
 			FILE *out;
			char name[50];
			strcpy(name, "kirsch-");
			strcat(name, orientation);
			strcat(name, "-");
			strcat(name, temp);
			out = fopen(name, "wb");
			gdImagePngEx(src, out, 9);                  
			fclose(out);                              
			gdImageDestroy(src);
			return;
        }
        else if(strcmp(orientation, "combined")==0){
            gdImageConvolution(src, kirsch_mask_vert, 1.0,0.0);
            copy = gdImageClone(src);
            gdImageConvolution(copy, kirsch_mask_horiz, 1.0,0.0);
        }
    }
    else if(strcmp(type, "prewitt")==0){
        if(strcmp(orientation, "vertical")==0){
            gdImageConvolution(src, prewitt_mask_vert, 1.0,0.0);
 			FILE *out;
			char name[50];
			strcpy(name, "prewitt-");
			strcat(name, orientation);
			strcat(name, "-");
			strcat(name, temp);
			out = fopen(name, "wb");

            //Experiemental trying to get other file types working!
            switch (extType){
                case 1:
                    gdImagePngEx(src, out, 9);
                case 2:
                    gdImageJpeg(src, out, -1);
                case 3:
                    gdImageGif(src, out);
            }

			fclose(out);                               
			gdImageDestroy(src);
			return;
        }
        else if(strcmp(orientation, "horizontal")==0){
            gdImageConvolution(src, prewitt_mask_horiz, 1.0,0.0);
 			FILE *out;
			char name[50];
			strcpy(name, "prewitt-");
			strcat(name, orientation);
			strcat(name, "-");
			strcat(name, temp);
			out = fopen(name, "wb");
			gdImagePngEx(src, out, 9);                  
			fclose(out);                              
			gdImageDestroy(src);
			return;
        }
        else if(strcmp(orientation, "combined")==0){
            gdImageConvolution(src, prewitt_mask_vert, 1.0,0.0);
            copy = gdImageClone(src);
            gdImageConvolution(copy, prewitt_mask_horiz, 1.0,0.0);
        }
    }
    else if(strcmp(type, "sobel")==0){
        if(strcmp(orientation, "vertical")==0){
            gdImageConvolution(src, sobel_mask_vert, 1.0,0.0);
 			FILE *out;
			char name[50];
			strcpy(name, "sobel-");
			strcat(name, orientation);
			strcat(name, "-");
			strcat(name, temp);
			out = fopen(name, "wb");
			gdImagePngEx(src, out, 9);                  
			fclose(out);                               
			gdImageDestroy(src);
			return;
        }
        else if(strcmp(orientation, "horizontal")==0){
            gdImageConvolution(src, sobel_mask_horiz, 1.0,0.0);
 			FILE *out;
			char name[50];
			strcpy(name, "sobel-");
			strcat(name, orientation);
			strcat(name, "-");
			strcat(name, temp);
			out = fopen(name, "wb");
			gdImagePngEx(src, out, 9);                  
			fclose(out);                              
			gdImageDestroy(src);
			return;
        }
        else if(strcmp(orientation, "combined")==0){
            gdImageConvolution(src, sobel_mask_vert, 1.0,0.0);
            copy = gdImageClone(src);
            gdImageConvolution(copy, sobel_mask_horiz, 1.0,0.0);
        }
    }
    else{
        printf("Error: edge detection method not supported.\n\n");
    }
}
