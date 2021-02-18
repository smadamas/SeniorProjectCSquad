#include <stdio.h>
#include <stdint.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

struct buff readToBuff(char *imageName, char *const buffName)
{
	printf("\nReading %s into %s...\n", imageName, buffName);
	int width, height, ch;
	unsigned char *buff = stbi_load(imageName, &width, &height, &ch, 0);
	if (buffName == NULL)
	{
		printf("Error reading file\n");
		stbi_failure_reason();
	}

	char *temp = strtok(imageName, ".");
	char *ext = strtok(NULL, " ");
	FILE *in;

	struct buff buffer;

	if (strcmp(ext, "png") == 0)
	{
		in = fopen(strcat(temp, ".png"), "rb");
		buffer.imrgb = gdImageCreateFromPng(in);
	}
	else if (strcmp(ext, "jpg") == 0 || strcmp(ext, "jpeg") == 0)
	{
		in = fopen(strcat(temp, ".jpg"), "rb");
		//printf("%s", strcat(temp, .jpg));
		buffer.imrgb = gdImageCreateFromJpeg(in);
	}
	else if (strcmp(ext, "gif") == 0)
	{
		in = fopen(strcat(temp, ".gif"), "rb");
		buffer.imrgb = gdImageCreateFromGif(in);
	}
	else if (strcmp(ext, "tiff") == 0)
	{
		in = fopen(strcat(temp, ".tiff"), "rb");
		buffer.imrgb = gdImageCreateFromTiff(in);
	}

	buffer.img = buff;
	strcpy(buffer.name, buffName);
	strcpy(buffer.imageName, imageName);
	buffer.width = width;
	buffer.height = height;
	buffer.channels = ch;
	printf("Done reading!\n\n");
	return buffer;
}