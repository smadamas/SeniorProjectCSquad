#include <stdio.h>
#include <stdint.h>
#include <string.h>

// a + b
struct buff add(struct buff a, struct buff b, char* buffName) {
	if ((a.width != b.width) || (a.height != b.height) || (a.channels != b.channels)) { // Check for correct dimensions
		printf("Wrong dimensions.\n");
		exit(1);
	}

	struct buff result;
	char* ext;
	ext = strstr(a.imageName, ".png");
	if (ext == NULL)
		ext = strstr(a.imageName, ".jpg");
	if (ext == NULL)
		ext = strstr(a.imageName, ".tiff");
	if (ext == NULL)
		ext = strstr(a.imageName, ".gif");	// Use extension of a for extension of result

	// Fill in info for buffer
	strcpy(result.imageName, "add");
	strcat(result.imageName, ext);
	strcpy(result.name, buffName);
	result.width = a.width;
	result.height = a.height;
	result.channels = a.channels;

	size_t size = result.width * result.height * result.channels; // Allocate memory for result
	unsigned char* result_img = malloc(size);
	if (result_img == NULL) {
		printf("Unable to allocate memory for the image.\n");
		exit(1);
	}

	result.img = result_img;

	// Loop through images and subtract pixels
	for (unsigned char* ptra = a.img, *ptrb = b.img, *ptrres = result.img;
		ptra != a.img + size;
		ptra += result.channels, ptrb += result.channels, ptrres += result.channels) {

		for (int i = 0; i < 3; i++) {
			if ((*(ptra + i) + *(ptrb + i)) > 255)
				*(ptrres + i) = (uint8_t)255;
			else
				*(ptrres + i) = (uint8_t)(*(ptra + i) + *(ptrb + i));
		}

		if (result.channels == 4)
			*(ptrres + 3) = *(ptra + 3);
	}

	return result;
}

// a - b
struct buff subtract(struct buff a, struct buff b, char* buffName) {
	if ((a.width != b.width) || (a.height != b.height) || (a.channels != b.channels)) { // Check for correct dimensions
		printf("Wrong dimensions.\n");
		exit(1);
	}
		
	struct buff result;
	char *ext;
	ext = strstr(a.imageName, ".png");
	if(ext == NULL)
		ext = strstr(a.imageName, ".jpg");
	if(ext == NULL)
		ext = strstr(a.imageName, ".tiff");	
	if(ext == NULL)
		ext = strstr(a.imageName, ".gif");	// Use extension of a for extension of result
	
	// Fill in info for buffer
	strcpy(result.imageName, "sub");
	strcat(result.imageName, ext);
	strcpy(result.name, buffName);
	result.width = a.width;
	result.height = a.height;
	result.channels = a.channels;
	
	size_t size = result.width * result.height * result.channels; // Allocate memory for result
	unsigned char *result_img = malloc(size);
	if(result_img == NULL) {
		printf("Unable to allocate memory for the image.\n");
		exit(1);
	}

	result.img = result_img;
		
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
				
		if(result.channels == 4)
			*(ptrres + 3) = *(ptra + 3);
	}
	
	return result;
}

// a * b
struct buff multiply(struct buff a, struct buff b, char* buffName) {
	if ((a.width != b.width) || (a.height != b.height) || (a.channels != b.channels)) { // Check for correct dimensions
		printf("Wrong dimensions.\n");
		exit(1);
	}

	struct buff result;
	char* ext;
	ext = strstr(a.imageName, ".png");
	if (ext == NULL)
		ext = strstr(a.imageName, ".jpg");
	if (ext == NULL)
		ext = strstr(a.imageName, ".tiff");
	if (ext == NULL)
		ext = strstr(a.imageName, ".gif");	// Use extension of a for extension of result

	// Fill in info for buffer
	strcpy(result.imageName, "mul");
	strcat(result.imageName, ext);
	strcpy(result.name, buffName);
	result.width = a.width;
	result.height = a.height;
	result.channels = a.channels;

	size_t size = result.width * result.height * result.channels; // Allocate memory for result
	unsigned char* result_img = malloc(size);
	if (result_img == NULL) {
		printf("Unable to allocate memory for the image.\n");
		exit(1);
	}

	result.img = result_img;

	// Loop through images and subtract pixels
	for (unsigned char* ptra = a.img, *ptrb = b.img, *ptrres = result.img;
		ptra != a.img + size;
		ptra += result.channels, ptrb += result.channels, ptrres += result.channels) {

		for (int i = 0; i < 3; i++) {
			if ((*(ptra + i) * *(ptrb + i)) > 255)
				*(ptrres + i) = (uint8_t)255;
			else
				*(ptrres + i) = (uint8_t)(*(ptra + i) * *(ptrb + i));
		}

		if (result.channels == 4)
			*(ptrres + 3) = *(ptra + 3);
	}

	return result;
}

// a / b
struct buff divide(struct buff a, struct buff b, char* buffName) {
	if ((a.width != b.width) || (a.height != b.height) || (a.channels != b.channels)) { // Check for correct dimensions
		printf("Wrong dimensions.\n");
		exit(1);
	}

	struct buff result;
	char* ext;
	ext = strstr(a.imageName, ".png");
	if (ext == NULL)
		ext = strstr(a.imageName, ".jpg");
	if (ext == NULL)
		ext = strstr(a.imageName, ".tiff");
	if (ext == NULL)
		ext = strstr(a.imageName, ".gif");	// Use extension of a for extension of result

	// Fill in info for buffer
	strcpy(result.imageName, "div");
	strcat(result.imageName, ext);
	strcpy(result.name, buffName);
	result.width = a.width;
	result.height = a.height;
	result.channels = a.channels;

	size_t size = result.width * result.height * result.channels; // Allocate memory for result
	unsigned char* result_img = malloc(size);
	if (result_img == NULL) {
		printf("Unable to allocate memory for the image.\n");
		exit(1);
	}

	result.img = result_img;

	// Loop through images and subtract pixels
	for (unsigned char* ptra = a.img, *ptrb = b.img, *ptrres = result.img;
		ptra != a.img + size;
		ptra += result.channels, ptrb += result.channels, ptrres += result.channels) {

		for (int i = 0; i < 3; i++) {
			if (*(ptrb + i) == 0)
				*(ptrres + i) = (uint8_t)*(ptra + i);
			else
				*(ptrres + i) = (uint8_t)(*(ptra + i) / *(ptrb + i));
		}

		if (result.channels == 4)
			*(ptrres + 3) = *(ptra + 3);
	}

	return result;
}