#include <stdio.h>
#include <stdint.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

struct buff readToBuff(char* imageName, char* const buffName ){
	printf("\nReading %s into %s...\n", imageName, buffName);
	int width, height, ch;
	unsigned char* buff = stbi_load(imageName, &width, &height, &ch, 0);
	if(buffName == NULL){
		printf("Error reading file\n");
		exit(1);
	}
	
	struct buff buffer;
	buffer.img = buff;
	strcpy(buffer.name, buffName);
	strcpy(buffer.imageName, imageName);
	buffer.width = width;
	buffer.height = height;
	buffer.channels = ch;
	printf("Done reading!\n\n");
	return buffer;
}