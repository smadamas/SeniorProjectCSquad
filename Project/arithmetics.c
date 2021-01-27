#include "gd.h"

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