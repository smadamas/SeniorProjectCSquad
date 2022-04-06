/// \file rotation.c
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include "gd.h"
#define KYEL "\x1B[33m" ///< Yellow terminal text color
#define KBLU "\x1B[34m" ///< Blue terminal text color
#define KRED "\x1B[31m" ///< Red terminal text color
#define KMAG "\x1B[35m" ///< Magenta terminal text color
#define RESET "\x1B[0m" ///< Reset termina text color


/**
 * Rotate `buff a` by specified number of `float degrees`.
 * \param a Source image buffer
 * \param degrees Amount to rotated image by, in degrees
 *
 * \return rotated `buff`
 */
struct buff rotate(struct buff a, float degrees)
{
    char input[100];
    printf("Enter name of buffer: \n");
    gets(input);
    struct buff temp = a;
    temp.isLibgd = 1;
    temp.height = a.width;
    temp.width = a.height;
    strcpy(temp.name, input);
    gdImagePtr out = gdImageRotateInterpolated(a.imrgb, (-1.0)*degrees, 0);
    temp.imrgb = out;

    printf(KYEL"Done rotating!\n"RESET);

    return temp;
}

/**
 * Flips image horizontally using `libgd`
 * \param a Source image buffer
 *
 * \return flipped `buff`
 */
struct buff horizontalFlip(struct buff a)
{
    char input[100];
    printf("Enter name of buffer: \n");
    gets(input);
    struct buff temp = a;
    gdImageFlipHorizontal(temp.imrgb);
    temp.isLibgd = 1;
    strcpy(temp.name, input);
    strcpy(temp.imageName, "flipH.jpg");
    return temp;
}

/**
 * Flips `buff a` vertically using `libgd`
 * \param a Source image buffer
 *
 * \return flipped `buff`
 */
struct buff verticalFlip(struct buff a)
{
    char input[100];
    printf("Enter name of buffer: \n");
    gets(input);
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
    strcpy(temp.name, input);
    strcpy(temp.imageName, "flipV.jpg");
    return temp;
}
