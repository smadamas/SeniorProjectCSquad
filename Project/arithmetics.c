#include <stdio.h>
#include <stdint.h>
#include <string.h>

// a - b
struct buff subtract(struct buff a, struct buff b) {
	if((a.width != b.width) || (a.height != b.height) || (a.channels != b.channels)) // Check for correct dimensions
		return NULL;
		
	struct buff result;
	char *ext;
	ext = strstr(a.imagename, ".png");
	if(ext == NULL)
		ext = strstr(a.imagename, ".jpg");
	if(ext == NULL)
		ext = strstr(a.imagename, ".tiff");	
	if(ext == NULL)
		ext = strstr(a.imagename, ".gif");	// Use extension of a for extension of result
	
	result.imagename = "subtraction"; // Fill in info for buffer
	strcat(result.imagename, ext);
	result.name = "subtraction";
	result.width = a.width;
	result.height = a.height;
	result.channels = a.channels;
	
	int size = result.width * result.height * result.channels; // Allocate memory for result
	unsigned char *result_img = malloc(size);
	if(result_img == NULL) {
		printf("Unable to allocate memory for the image.\n");
		exit(1);
	}
	result.img = result_img
	
	// Loop through images and subtract pixels
	for(unsigned char *ptra = a.img, *ptrb = b.img, *ptrres = result.img; 
						ptra != a.img + size;
						ptra += result.channels, ptrb += result.channels, ptrres += result.channels) {
	
		for(int i = 0; i < 3; i++) {
			if((*(ptra + i) - *(ptrb + i)) < 0)
				*(ptrres + i) = (uint8_t)0;
			else
				*(ptrres + i) = (uint8_t)(*(ptra + i) - *(ptrb + i));
		}
				
		if(channels == 4)
			*(ptrres + 3) = *(p + 3);
	}
}

// a / b
struct buff divide(struct buff a, struct buff b) {
	if((a.width != b.width) || (a.height != b.height) || (a.channels != b.channels)) // Check for correct dimensions
		return NULL;
		
	struct buff result;
	char *ext;
	ext = strstr(a.imagename, ".png");
	if(ext == NULL)
		ext = strstr(a.imagename, ".jpg");
	if(ext == NULL)
		ext = strstr(a.imagename, ".tiff");	
	if(ext == NULL)
		ext = strstr(a.imagename, ".gif");	// Use extension of a for extension of result
	
	result.imagename = "division"; // Fill in info for buffer
	strcat(result.imagename, ext);
	result.name = "division";
	result.width = a.width;
	result.height = a.height;
	result.channels = a.channels;
	
	int size = result.width * result.height * result.channels; // Allocate memory for result
	unsigned char *result_img = malloc(size);
	if(result_img == NULL) {
		printf("Unable to allocate memory for the image.\n");
		exit(1);
	}
	result.img = result_img
	
	// Loop through images and subtract pixels
	for(unsigned char *ptra = a.img, *ptrb = b.img, *ptrres = result.img; 
						ptra != a.img + size;
						ptra += result.channels, ptrb += result.channels, ptrres += result.channels) {
		
		for(int i = 0; i < 3; i++) {
			if(*(ptrb + i) == 0)
				*(ptrres + i) = (uint8_t)*(ptra + i);
			else
				*(ptrres + i) = (uint8_t)(*(ptra + i) / *(ptrb + i));
		}

		if(channels == 4)
			*(ptrres + 3) = *(p + 3);
	}
}

/*			LIBGD
//#include "stb/gd.h"
// result = a - b
gdImagePtr subtract(gdImagePtr a, gdImagePtr b) {
	if((gdImageSX(a) != gdImageSX(b)) || ((gdImageSY(a) != gdImageSY(b)) // Checks for correct dimensions
		return NULL;
	
	//gdImagePtr result = gdImageCreate(gdImageSX(a), gdImageSY(a)); // 256 colors
	gdImagePtr result = gdImageCreateTrueColor(gdImageSX(a), gdImageSY(a)); // "unlimited" colors
	
	for(int x = 0; i < gdImageSX(a); x++) {
		for(int y = 0; j < gdImageSY(a); y++) {
			int pixel_a = gdImageGetPixel(a, x, y); // Get current pixel of a
			int pixel_b = gdImageGetPixel(b, x, y); // Get current pixel of b
			
			int a_red = gdTrueColorGetRed(pixel_a);		// Red channel of pixel a
			int a_geen = gdTrueColorGetGreen(pixel_a);	// Green channel of pixel a
			int a_blue = gdTrueColorGetBlue(pixel_a);	// Blue channel of pixel a
			
			int b_red = gdTrueColorGetRed(pixel_b);		// Red channel of pixel b
			int b_green = gdTrueColorGetGreen(pixel_b);	// Green channel of pixel b
			int b_blue = gdTrueColorGetBlue(pixel_b);	// Blue channel of pixel b
			
			if((a_red - b_red) < 0)	// If subtraction negative, set to 0
				int result_red = 0;
			else
				int result_red = a_red - b_red;
			
			if((a_green - b_green) < 0)
				int result_green = 0;
			else
				int result_green = a_green - b_green;
				
			if((a_blue - b_blue) < 0)
				int result_blue = 0;
			else
				int result_blue = a_blue - b_blue;
			
			int pixel_result = gdTrueColorAlpha(result_red, result_green, result_blue, 0); // rgb values, alpha = 0 (fully opaque)
			gdImageSetPixel(result, x, y, pixel_result);
		}
	}
	
	return result;
}

// result = a / b
gdImagePtr divide(gdImagePtr a, gdImagePtr b) {
	if((gdImageSX(a) != gdImageSX(b)) || ((gdImageSY(a) != gdImageSY(b)) // Checks for correct dimensions
		return NULL;
	
	//gdImagePtr result = gdImageCreate(gdImageSX(a), gdImageSY(a)); // 256 colors
	gdImagePtr result = gdImageCreateTrueColor(gdImageSX(a), gdImageSY(a)); // "unlimited" colors
	
	for(int x = 0; i < gdImageSX(a); x++) {
		for(int y = 0; j < gdImageSY(a); y++) {
			
			int pixel_a = gdImageGetPixel(a, x, y); // Get current pixel of a
			int pixel_b = gdImageGetPixel(b, x, y); // Get current pixel of b
			
			int a_red = gdTrueColorGetRed(pixel_a);		// Red channel of pixel a
			int a_geen = gdTrueColorGetGreen(pixel_a);	// Green channel of pixel a
			int a_blue = gdTrueColorGetBlue(pixel_a);	// Blue channel of pixel a
			
			int b_red = gdTrueColorGetRed(pixel_b);		// Red channel of pixel b
			int b_green = gdTrueColorGetGreen(pixel_b);	// Green channel of pixel b
			int b_blue = gdTrueColorGetBlue(pixel_b);	// Blue channel of pixel b
			
			if(b_red == 0)	// Check if denominator 0
				int result_red = a_red;
			else
				int result_red = a_red / b_red;
			
			if(b_green == 0)
				int result_green = a_green;
			else
				int result_green = a_green / b_green;
				
			if(b_blue == 0)
				int result_blue = a_blue;
			else
				int result_blue = a_blue / b_blue;
			
			int pixel_result = gdTrueColorAlpha(result_red, result_green, result_blue, 0); // rgb values, alpha = 0 (fully opaque)
			gdImageSetPixel(result, x, y, pixel_result);
		}
	}
	
	return result;
}

*/