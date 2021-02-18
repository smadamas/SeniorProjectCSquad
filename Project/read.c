#include <stdio.h>
#include <stdint.h>
#include "gd.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

struct buff readToBuff(char* imageName, char* const buffName ){
	printf("\nReading %s into %s...\n", imageName, buffName);
	int width, height, ch;
	unsigned char* buff = stbi_load(imageName, &width, &height, &ch, 3);
	//note: ch is the number of channels that WOULD have been in the buffer. The last argument to stbi_load controls the number of channels
	printf("w: %d, h: %d, ch: %d\n", width, height, ch);

	gdImagePtr im;
	im = gdImageCreateTrueColor(width, height);

	if(buffName == NULL){
		printf("Error reading file\n");
		stbi_failure_reason();
		exit(1);
	}

	struct buff buffer;
	buffer.img = buff;
	buffer.imrgb = im;
	strcpy(buffer.name, buffName);
	strcpy(buffer.imageName, imageName);
	buffer.width = width;
	buffer.height = height;
	buffer.channels = ch;
	printf("Done reading!\n\n");
	return buffer;
}