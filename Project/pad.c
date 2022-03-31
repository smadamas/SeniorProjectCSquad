#include "gd.h"
#include <math.h>
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KRED  "\x1B[31m"
#define KMAG  "\x1B[35m"
#define RESET "\x1B[0m"

struct buff pad(struct buff input, char * buffName)
{
    
  // struct buff
  // {
  //   char imageName[32];
  //   char name[30];
  //   char status[30];
  //   unsigned char *img;
  //   int width, height, channels;
  //   gdImagePtr imrgb;
  //   int isLibgd;
  // };

	struct buff result;
	int w = input.width;
	int h = input.height;
	int c = input.channels;

	struct buff img = input;

	char* ext;
	ext = strstr(img.imageName, ".png");
	if (ext == NULL)
		ext = strstr(img.imageName, ".jpg");
	if (ext == NULL)
		ext = strstr(img.imageName, ".tiff");
	if (ext == NULL)
		ext = strstr(img.imageName, ".gif");	// Use extension of a for extension of result

	strcpy(result.imageName, "pad");
	strcat(result.imageName, ext);
	strcpy(result.name, buffName);
	strcpy(result.status, "true");
	result.isLibgd = 0;

	// Get the size of the square image: dim = 2^n // gets highest value of n
	int n = (int)ceil(log2(fmax(w, h)));
	int dim = 1 << n;

	result.height = dim;
	result.width = dim;
	//printf("dim = %d\n", dim);
	result.channels = c;

	int size = c * dim * dim; // number of pixels * number of channels
	result.img = malloc(size);

	// Copy img into result with 0s for padding
	for (int k = 0; k < c; k++) {
		for (int i = 0; i < dim; i++) {
			for (int j = 0; j < dim*c; j+=c) {
				if (i >= h || j >= w * c) {
					*(result.img + j + (i * dim * c) + k) = 0;
				}
				else {
					*(result.img + j + (i * dim * c) + k) = *(img.img + j + (i * w * c) + k);
				}
			}
		}
	}

	return result;
}