#include "libgd/src/gd.h"

void detectKirsh(char* orientation, char* imageName);
void detectPrewitt();
void detectSobel();

void detectEdge(char* orientation, char* type, char* imageName){
          
     if(strcmp(type, "kirsch")==0){             
         detectKirsh(orientation, imageName);
     }
    else if(strcmp(type, "prewitt")==0){
        detectPrewitt();
    }
    else if(strcmp(type, "sobel")==0){
        detectSobel();
    }
    else{
        printf("Error: edge detection method not supported.\n\n");
    }


}

void detectKirsh(char* orientation, char* imageName){
    
    char* temp = strtok(imageName, ".");
	char* ext = strtok(NULL," ");
    
    FILE *in;
    gdImagePtr result, src;
    
    float kirsch_mask_horiz[3][3] = {
    { 5, 5, 5},
    {-3, 0, -3},
    {-3, -3, -3} };

    float kirsch_mask_vert[3][3] = {
    { 5, -3, -3},
    {5, 0, -3},
    {5, -3, -3} };
   
    
    if(strcmp(ext, "png")==0){ 
	 	in = fopen(strcat(temp, ".png"), "rb");
        src = gdImageCreateFromPng(in);
        gdImageGrayScale(src);
        
        if(strcmp(orientation, "vertical")==0){
            gdImageConvolution(src, kirsch_mask_vert, 1.0,0.0);
        }
        else{
            gdImageConvolution(src, kirsch_mask_horiz, 1.0,0.0);
        }
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
	}
	else if(strcmp(ext, "jpg")==0){
		in = fopen(strcat(temp, ".jpg"), "rb");
        src = gdImageCreateFromJpeg(in);
        gdImageGrayScale(src);
        if(strcmp(orientation, "vertical")==0){
            gdImageConvolution(src, kirsch_mask_vert, 1.0,0.0);
        }
        else{
            gdImageConvolution(src, kirsch_mask_horiz, 1.0,0.0);
        }
        FILE *out;
        temp = strtok(imageName, ".");
        char name[50];
        strcpy(name, "kirsch-");
        strcat(name, orientation);
        strcat(name, "-");
        strcat(name, temp);
        strcat(name, ".png");
        out = fopen(name, "wb");
        gdImagePngEx(src, out, 9);                  
        fclose(out);                               
        gdImageDestroy(src);
	}
	else if(strcmp(ext, "tiff")==0){
        in = fopen(strcat(temp, ".tiff"), "rb");
        src = gdImageCreateFromTiff(in);
        gdImageGrayScale(src);
        if(strcmp(orientation, "vertical")==0){
            gdImageConvolution(src, kirsch_mask_vert, 1.0,0.0);
        }
        else{
            gdImageConvolution(src, kirsch_mask_horiz, 1.0,0.0);
        }
        FILE *out;
        char* temp = strtok(imageName, ".");
        char name[50];
        strcpy(name, "kirsch-");
        strcat(name, orientation);
        strcat(name, "-");
        strcat(name, temp);
        strcat(name, ".png");
        out = fopen(name, "wb");
        gdImagePngEx(src, out, 9);                  
        fclose(out);                               
        gdImageDestroy(src);
    }
	else if(strcmp(ext, "gif")==0){
        in = fopen(strcat(temp, ".gif"), "rb");
        src = gdImageCreateFromGif(in);
        gdImageGrayScale(src);
        if(strcmp(orientation, "vertical")==0){
            gdImageConvolution(src, kirsch_mask_vert, 1.0,0.0);
        }
        else{
            gdImageConvolution(src, kirsch_mask_horiz, 1.0,0.0);
        }
        FILE *out;
        char* temp = strtok(imageName, ".");
        char name[50];
        strcpy(name, "kirsch-");
        strcat(name, orientation);
        strcat(name, "-");
        strcat(name, temp);
        strcat(name, ".png");
        out = fopen(name, "wb");
        gdImagePngEx(src, out, 9);                  
        fclose(out);                               
        gdImageDestroy(src);
    }
    else{
        printf("Error: image type not supported.\n\n");
    }
}

void detectPrewitt(){}
void detectSobel(){}