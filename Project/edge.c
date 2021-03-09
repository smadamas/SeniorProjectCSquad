#include "libgd/src/gd.h"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KRED  "\x1B[31m"
#define KMAG  "\x1B[35m"
#define RESET "\x1B[0m"

struct buff detectEdge(char *orientation, char *type, struct buff image)
{
    float kirsch_mask_horiz[3][3] = {
        {5, 5, 5},
        {-3, 0, -3},
        {-3, -3, -3}};
    float kirsch_mask_vert[3][3] = {
        {5, -3, -3},
        {5, 0, -3},
        {5, -3, -3}};
    float prewitt_mask_vert[3][3] = {
        {1, 0, -1},
        {1, 0, -1},
        {1, 0, -1}};
    float prewitt_mask_horiz[3][3] = {
        {1, 1, 1},
        {0, 0, 0},
        {-1, -1, -1}};
    float sobel_mask_horiz[3][3] = {
        {1, 0, -1},
        {2, 0, -2},
        {1, 0, -1}};
    float sobel_mask_vert[3][3] = {
        {1, 2, 1},
        {0, 0, 0},
        {-1, -2, -1}};
    

    gdImagePtr src = image.imrgb, copy;
    gdImageGrayScale(src);
    if (strcmp(type, "kirsch") == 0)
    {
        struct buff temp = image;
        if (strcmp(orientation, "vertical") == 0)
        {
            gdImageConvolution(src, kirsch_mask_vert, 1.0, 0.0);
            temp.imrgb = src;
        }
        else if (strcmp(orientation, "horizontal") == 0)
        {
            gdImageConvolution(src, kirsch_mask_horiz, 1.0, 0.0);
            temp.imrgb = src;
        }
        else if (strcmp(orientation, "combined") == 0)
        {
            struct buff temp1 = detectEdge("vertical", type, image);
			struct buff temp2 = detectEdge("horizontal", type, image);
			temp.imrgb = combine(temp1, temp2).imrgb;
        }
        char name[50];
        strcpy(name, "kirsch-");
        strcat(name, orientation);
        strcat(name, "-");
        strcat(name, temp.imageName);
        strcpy(temp.imageName, name);
        return temp;
    }
    else if (strcmp(type, "prewitt") == 0)
    {
        struct buff temp = image;
        if (strcmp(orientation, "vertical") == 0)
        {
            gdImageConvolution(src, prewitt_mask_vert, 1.0, 0.0);
            temp.imrgb = src;
        }
        else if (strcmp(orientation, "horizontal") == 0)
        {
            gdImageConvolution(src, prewitt_mask_horiz, 1.0, 0.0);
            temp.imrgb = src;
        }
        else if (strcmp(orientation, "combined") == 0)
        {
            struct buff temp1 = detectEdge("vertical", type, image);
			struct buff temp2 = detectEdge("horizontal", type, image);
			temp.imrgb = combine(temp1, temp2).imrgb;
        }
        char name[50];
        strcpy(name, "prewitt-");
        strcat(name, orientation);
        strcat(name, "-");
        strcat(name, temp.imageName);
        strcpy(temp.imageName, name);
        return temp;
    }
    else if (strcmp(type, "sobel") == 0)
    {
        struct buff temp = image;
        if (strcmp(orientation, "vertical") == 0)
        {
            gdImageConvolution(src, sobel_mask_vert, 1.0, 0.0);
            temp.imrgb = src;
        }
        else if (strcmp(orientation, "horizontal") == 0)
        {
            gdImageConvolution(src, sobel_mask_horiz, 1.0, 0.0);
            temp.imrgb = src;
        }
        else if (strcmp(orientation, "combined") == 0)
        {
           struct buff temp1 = detectEdge("vertical", type, image);
			struct buff temp2 = detectEdge("horizontal", type, image);
			temp.imrgb = combine(temp1, temp2).imrgb;
        }
        char name[50];
        strcpy(name, "sobel-");
        strcat(name, orientation);
        strcat(name, "-");
        strcat(name, temp.imageName);
        strcpy(temp.imageName, name);
        return temp;
    }
    else
    {
        printf(KRED "Error:"RESET" edge detection method not supported.\n\n");
        return;
    }
}
