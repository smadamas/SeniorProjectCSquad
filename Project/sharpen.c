#include "libgd/src/gd.h"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KRED  "\x1B[31m"
#define KMAG  "\x1B[35m"
#define RESET "\x1B[0m"

struct buff sharpen(struct buff buffer, double percent)
{
    char newBuff[100];
    printf("Enter name of buffer: \n");
    gets(newBuff);

    gdImagePtr copy;
    copy = gdImageClone(buffer.imrgb);

    struct buff result;
    char *temp = strtok(buffer.imageName, ".");
    char *ext = strtok(NULL, " ");
    strcpy(result.imageName, "sharp-");
	strcat(result.imageName, temp);
    strcat(result.imageName, ".");
    strcat(result.imageName, ext);
	strcpy(result.name, newBuff);
	result.width = buffer.width;
	result.height = buffer.height;
	result.channels = buffer.channels;

    //Mean Image Removal Option
    gdImageMeanRemoval(copy);

    //Adding to edges option
    

    result.imrgb = copy;
    result.isLibgd = 1;

    printf(KYEL "Done sharpening!\n"RESET);

    return result;
}
