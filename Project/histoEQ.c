// C program to perform histogram equalisation to adjust contrast levels

#include <fcntl.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to perform histogram equalisation on an image
// Function takes total rows, columns, input file

struct buff histogramEqualisation(struct buff a, char *buffName)
{
    // creating image pointer
    unsigned char* image;

    //Instantiating Rows and Cols
    int cols = a.width;
    int rows = a.height;
    printf("\n\n%d", a.channels);

    // Declaring 2 arrays for storing histogram values (frequencies) and
    // new gray level values (newly mapped pixel values as per algorithm)
    int hist[256];
    int new_gray_level[256];

    for (int i = 0; i < 256; i++){
        hist[i] = 0;
        new_gray_level[i] = 0;
    }

    // Declaring other important variables
    int col, row, total, i;
    unsigned long curr, cdf_min;
    total = cols * rows;

    curr = 0;

    // allocating image array the size equivalent to number of columns
    // of the image to read one row of an image at a time
    image = (unsigned char *)calloc(cols, sizeof(unsigned char));

    if (image == NULL)
    {
        printf("Unable to allocate memory for the image.\n");
        exit(1);
    }

    // Calculating frequency of occurrence for all pixel values
    // New way 

    unsigned char* img;
    img = a.img;
    const unsigned char* limit = a.img + total;

    for(img = a.img; img < limit; img++){
        hist[*img]++;
    }

    // calculating CDF (works)
    float cdf[256];
    for (i = 0; i < 256; i++){
        // cumulative frequency
        curr += hist[i];
        cdf[i] = curr;
    }
    for(i = 0; i < 256; i++){
        if(cdf[i] != 0){
            cdf_min = cdf[i];
            break;
        }
    }

    //Allocate for output
    struct buff newBuff;
    size_t size = cols * rows * 1; // Allocate memory for result
                                                                     // unsigned char *result_img = malloc(size * sizeof(unsigned char));
    unsigned long* result;
    result = (unsigned long *)calloc(size, sizeof(unsigned long));

    if (result == NULL)
    {
        printf("Unable to allocate memory for the histogram.\n");
        exit(1);
    }

    unsigned char* result_img;
    result_img = (unsigned char *)calloc(size, sizeof(unsigned char));

    if (result_img == NULL)
    {
        printf("Unable to allocate memory for the image.\n");
        exit(1);
    }

    const double k = 255.0 / (total - cdf_min);

    for (i = 0; i < 256; i++)
    {
        result[i] = (unsigned long)(k*(cdf[i] - cdf_min));
    }
    int index = 0;
    for (img = a.img; img < limit; img++){
        *result_img = (unsigned char)result[(unsigned long)*img];
        result_img++; //Increment output pointer
    }


    // Fill in info for buffer
    strcpy(newBuff.imageName, a.imageName);
    strcpy(newBuff.name, a.name);
    newBuff.width = a.width;
    newBuff.height = a.height;
    newBuff.channels = 1;

    char *ext;
    ext = strstr(a.imageName, ".png");
    if (ext == NULL)
        ext = strstr(a.imageName, ".jpg");
    if (ext == NULL)
        ext = strstr(a.imageName, ".tiff");
    if (ext == NULL)
        ext = strstr(a.imageName, ".gif"); // Use extension of a for extension of result


    newBuff.img = result_img;

    // freeing dynamically allocated memory
    // free(result_img);
    printf("Done Equalizing");

    return newBuff;
}
