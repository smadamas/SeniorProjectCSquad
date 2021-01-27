#include <stdio.h>
#include <stdint.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

unsigned char* readToBuff(char* imageName, char* buffName){
	printf("\nReading %s into %s...\n", imageName, buffName);
	int width, height, ch;
	unsigned char* buff = stbi_load(imageName, &width, &height, &ch, 0);
	if(buffName == NULL){
		printf("Error reading file\n");
		exit(1);
	}
	printf("Done reading!\n\n");
	return buff;
}
