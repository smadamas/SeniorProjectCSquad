#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

//Change this into the brightening routine which changes the pixels, add truncate function below
struct buff brighten(struct buff input, char* buffName, bool choice) {

	// printf(input.imageName);
	// printf("\n");
	// printf(input.name);
	// printf("\n");
	// printf(buffName);
	// printf("\n%d", choice);

	struct buff result;
	char* ext;
	ext = strstr(input.imageName, ".png");
	if (ext == NULL)
		ext = strstr(input.imageName, ".jpg");
	if (ext == NULL)
		ext = strstr(input.imageName, ".tiff");
	if (ext == NULL)
		ext = strstr(input.imageName, ".gif");	// Use extension

	// Fill in info for buffer
	if (choice){
		strcpy(result.imageName, "brightened");
	}
	else {
		strcpy(result.imageName, "darkened");
	}
	strcat(result.imageName, ext);
	strcpy(result.name, buffName);
	result.width = input.width;
	result.height = input.height;
	result.channels = input.channels;

	size_t size = result.width * result.height * result.channels; // Allocate memory for result
	unsigned char* result_img = malloc(size);
	if (result_img == NULL) {
		printf("Unable to allocate memory for the image.\n");
		exit(1);
	}

	result.img = result_img;
	unsigned char *oldPtr = input.img, *newPtr = result.img;

	// Loop through image pixels and brighten or darken
	for (unsigned char *oldPtr = input.img, *newPtr = result.img; oldPtr != input.img + size; oldPtr += result.channels, newPtr += result.channels) {
		//printf("%u", oldPtr);
		if (choice){
			for (int i = 0; i < 3; i++) {
				if ((*(oldPtr + i) + 128) > 255)
					*(newPtr + i) = (uint8_t)255;
				else
					*(newPtr + i) = (uint8_t)(*(oldPtr + i) + 128);
			}
		}
		else {
			for (int i = 0; i < 3; i++) {
				if ((*(oldPtr + i) - 128) < 0)
					*(newPtr + i) = (uint8_t)0;
				else
					*(newPtr + i) = (uint8_t)(*(oldPtr + i) - 128);
			}
		}
		
		if (result.channels == 4)
			*(newPtr + 3) = *(oldPtr + 3);

		oldPtr += result.channels;
		newPtr += result.channels;

	}

	return result;
}
