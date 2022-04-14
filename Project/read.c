/// \file read.c
#include <stdio.h>
#include <stdint.h>
#include <errno.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define KYEL  "\x1B[33m" ///< Yellow terminal text color
#define KRED  "\x1B[31m" ///< Red terminal text color
#define RESET "\x1B[0m"  ///< Reset terminal text color


/**
 * Reads any image of supported filetype into an internal buffer of name `buffName`
 * \param imageName Name of the image on the disk to be read
 * \parma buffName Desired name of the loaded buffer
 * 
 * \return loaded `buff`
 */
struct buff readToBuff(char *imageName, char *const buffName)
{
	char path[32 + 7] = "./img/";     // max size of imageName + size of folder name
	char* name = malloc(14);
	strcpy(name, imageName);
	char *temp = strtok(name, ".");
	char *ext = strtok(NULL, " ");
	strcat(path, imageName);
	// printf("%s\n", path);
	
	FILE *in;
	struct buff buffer;
	
	if (strcmp(ext, "wht") == 0)
	{
		printf(KYEL"Reading %s into %s..."RESET"\n", imageName, buffName);
		in = fopen(path, "rb");
		fread(&buffer.width, sizeof(int), 1, in);
		fread(&buffer.height, sizeof(int), 1, in);
		fread(&buffer.channels, sizeof(int), 1, in);
		fread(&buffer.has_wht, sizeof(int), 1, in);
		int size = buffer.width * buffer.height * buffer.channels;
		//printf("size: %d\n", size);
		buffer.wht = malloc(size * sizeof(double));
		fread(buffer.wht, sizeof(double), size, in);
		buffer.img = NULL;
		strcpy(buffer.name, buffName);
		strcpy(buffer.imageName, imageName);
		buffer.isLibgd = false;
		// buffer.has_wht = 1;
		fclose(in);
		//print_matrixf(buffer.wht, buffer.width);
		free(name);
		return buffer;
	}

	printf(KYEL"Reading %s into %s..."RESET"\n" , imageName, buffName);
	int width, height, ch;
	unsigned char *buff = stbi_load(path, &width, &height, &ch, 0);
	// unsigned char *buff = stbi_load(path, &width, &height, &ch, 0);
	if (buffName == NULL || buff == NULL)
	{
		printf(KRED "Error: "RESET " Cannot read file\n");
		stbi_failure_reason();
	}
	//printf("ext:%s\n",ext);
	if (strcmp(ext, "png") == 0)
	{
		in = fopen(path, "rb");
		buffer.imrgb = gdImageCreateFromPng(in);
	}
	else if (strcmp(ext, "jpeg") == 0)
	{
		in = fopen(path, "rb");
		buffer.imrgb = gdImageCreateFromJpeg(in);
	}
	else if (strcmp(ext, "gif") == 0)
	{
		in = fopen(path, "rb");
		buffer.imrgb = gdImageCreateFromGif(in);
	}
	else if (strcmp(ext, "tiff") == 0)
	{
		in = fopen(path, "rb");
		buffer.imrgb = gdImageCreateFromTiff(in);
	}
	

	buffer.img = buff;
	strcpy(buffer.name, buffName);
	strcpy(buffer.imageName, imageName);
	buffer.width = width;
	buffer.height = height;
	buffer.channels = ch;
	buffer.isLibgd = false;
	buffer.has_wht = 0;
	printf(KYEL "Done reading!\n"RESET);
	free(name);
	return buffer;
}
