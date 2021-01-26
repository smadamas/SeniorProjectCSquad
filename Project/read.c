#include <stdio.h>
#include <stdint.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

struct pixel** readToBuff(char* imageName, char* buffName){
	printf("\nReading %s into %s...\n", imageName, buffName);
	int width, height, ch;
	buffName = stbi_load(imageName, &width, &height, &ch, 0);
	if(buffName == NULL){
		printf("Error reading file\n");
		exit(1);
	}
	printf("Done reading!");
	stbi_write
	stbi_image_free(buffName);
	return NULL;
}
