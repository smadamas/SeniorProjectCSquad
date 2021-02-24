#include <stdio.h>
#include <stdlib.h>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

void writeToImage(struct buff buffer, char *imageName)
{
	char *temp = strtok(imageName, ".");
	char *ext = strtok(NULL, " ");
	if (buffer.isLibgd)
	{
		if (buffer.name == NULL)
		{
			printf("Error: buffer is empty.\n");
		}
		else if (strcmp(ext, "png") == 0)
		{
			FILE *output = fopen(strcat(temp, ".png"), "wb");
			gdImagePngEx(buffer.imrgb, output, 9);
			fclose(output);
		}
		else if (strcmp(ext, "jpg") == 0|| strcmp(ext, "jpeg") == 0)
		{
			FILE *output = fopen(strcat(temp, ".jpg"), "wb");
			gdImageJpeg(buffer.imrgb, output, 9);
			fclose(output);
		}
		else if (strcmp(ext, "tiff") == 0)
		{
			FILE *output = fopen(strcat(temp, ".tiff"), "wb");
			gdImageTiff(buffer.imrgb, output);
			fclose(output);
		}
		else if (strcmp(ext, "gif") == 0)
		{
			FILE *output = fopen(strcat(temp, ".gif"), "wb");
			gdImageGif(buffer.imrgb, output);
			fclose(output);
		}
		else
		{
			printf("File type not supported yet.\n\n");
		}
		
	}
	else
	{

		if (buffer.name == NULL)
		{
			printf("Error: buffer is empty.\n");
		}
		else if (strcmp(ext, "png") == 0)
		{
			stbi_write_png(strcat(temp, ".png"), buffer.width, buffer.height, buffer.channels, buffer.img, buffer.width * buffer.channels);
		}
		else if (strcmp(ext, "jpg") == 0 || strcmp(ext, "jpeg") == 0)
		{
			stbi_write_jpg(strcat(temp, ".jpg"), buffer.width, buffer.height, buffer.channels, buffer.img, buffer.width * buffer.channels);
		}
		else if (strcmp(ext, "tiff") == 0)
		{
			stbi_write_jpg(strcat(temp, ".tiff"), buffer.width, buffer.height, buffer.channels, buffer.img, buffer.width * buffer.channels);
		}
		else if (strcmp(ext, "gif") == 0)
		{
			stbi_write_jpg(strcat(temp, ".gif"), buffer.width, buffer.height, buffer.channels, buffer.img, buffer.width * buffer.channels);
		}
		else
		{
			printf("File type not supported yet.\n\n");
		}
	}
}