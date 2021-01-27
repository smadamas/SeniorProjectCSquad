#include <stdio.h>
#include <stdint.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

// result = a - b
gdImagePtr subtract(gdImagePtr a, gdImagePtr b) {
	if((gdImageSX(a) != gdImageSX(b)) || ((gdImageSY(a) != gdImageSY(b)) // Checks for correct dimensions
		return NULL;
	
	gdImagePtr result = gdImageCreate(gdImageSX(a), gdImageSY(a)); // 256 colors
	//gdImagePtr result = gdImageCreateTrueColor(gdImageSX(a), gdImageSY(a)); // "unlimited" colors
	
	for(int x = 0; i < gdImageSX(a); x++) {
		for(int y = 0; j < gdImageSY(a); y++) {
			if((gdImageGetPixel(a, x, y) - gdImageGetPixel(b, x, y)) < 0) // If subtraction negative, set to 0
				gdImageSetPixel(result, x, y, 0);
			else
				gdImageSetPixel(result, x, y, (gdImageGetPixel(a, x, y) - gdImageGetPixel(b, x, y));
		}
	}
	
	return result;
}

// result = a / b
gdImagePtr divide(gdImagePtr a, gdImagePtr b) {
	if((gdImageSX(a) != gdImageSX(b)) || ((gdImageSY(a) != gdImageSY(b)) // Checks for correct dimensions
		return NULL;
	
	gdImagePtr result = gdImageCreate(gdImageSX(a), gdImageSY(a)); // 256 colors
	//gdImagePtr result = gdImageCreateTrueColor(gdImageSX(a), gdImageSY(a)); // "unlimited" colors
	
	for(int x = 0; i < gdImageSX(a); x++) {
		for(int y = 0; j < gdImageSY(a); y++) {
			if(gdImageGetPixel(b, x, y) = 0) // Check if denominator 0
				gdImageSetPixel(result, x, y, (gdImageGetPixel(a, x, y));
			else
				gdImageSetPixel(result, x, y, (gdImageGetPixel(a, x, y) / gdImageGetPixel(b, x, y));
		}
	}
	
	return result;
}