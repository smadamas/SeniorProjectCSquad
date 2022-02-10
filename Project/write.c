#include <stdio.h>
#include <stdlib.h>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#define KYEL "\x1B[33m"
#define KRED "\x1B[31m"
#define RESET "\x1B[0m"

void write_to_wht(struct buff buffer, char* imageName);

void writeToImage(struct buff buffer, char *imageName, int wht)
{
	char *temp = strtok(imageName, ".");
	char *ext = strtok(NULL, " ");

	if (wht == 1) {
		if (buffer.name == NULL)
		{
			printf(KRED "Error: " RESET "buffer is empty.\n");
		}
		else if (strcmp(ext, "png") == 0)
		{
			stbi_write_png(strcat(temp, ".png"), buffer.width, buffer.height, buffer.channels, buffer.whtimg, buffer.width * buffer.channels);
		}
		else if (strcmp(ext, "jpg") == 0 || strcmp(ext, "jpeg") == 0)
		{
			stbi_write_jpg(strcat(temp, ".jpg"), buffer.width, buffer.height, buffer.channels, buffer.whtimg, buffer.width * buffer.channels);
		}
		else if (strcmp(ext, "tiff") == 0)
		{
			stbi_write_jpg(strcat(temp, ".tiff"), buffer.width, buffer.height, buffer.channels, buffer.whtimg, buffer.width * buffer.channels);
		}
		else if (strcmp(ext, "gif") == 0)
		{
			stbi_write_jpg(strcat(temp, ".gif"), buffer.width, buffer.height, buffer.channels, buffer.whtimg, buffer.width * buffer.channels);
		}
		else if (strcmp(ext, "wht") == 0)
		{
			printf(KRED "Error: " RESET "Use \"write <buffer name> to <file name>.wht\" to save the wht data.\n\n");
		}
		else
		{
			printf(KRED "Error: " RESET "File type not supported yet.\n\n");
		}
	}
	else if (buffer.isLibgd > 0)
	{
		if (buffer.name == NULL)
		{
			printf(KRED "Error:" RESET " buffer is empty.\n");
		}
		else if (strcmp(ext, "png") == 0)
		{
			FILE *output = fopen(strcat(temp, ".png"), "wb");
			gdImagePngEx(buffer.imrgb, output, 9);
			fclose(output);
		}
		else if (strcmp(ext, "jpg") == 0 || strcmp(ext, "jpeg") == 0)
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
			printf(KRED "Error: " RESET "File type not supported yet.\n\n");
		}
	}
	else
	{

		if (buffer.name == NULL)
		{
			printf(KRED "Error: " RESET "buffer is empty.\n");
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
		else if (strcmp(ext, "wht") == 0) 
		{
			write_to_wht(buffer, imageName);
		}
		else
		{
			printf(KRED "Error: " RESET "File type not supported yet.\n\n");
		}
	}
}

void write_to_wht(struct buff buffer, char* imageName) {
	int size = buffer.height * buffer.width * buffer.channels;
	char name[30];
	strcpy(name, imageName);
	strcat(name, ".wht");
	FILE* fp = fopen(name, "w");
	fwrite(&buffer.height, sizeof(int), 1, fp);
	fwrite(&buffer.width, sizeof(int), 1, fp);
	fwrite(&buffer.channels, sizeof(int), 1, fp);
	fwrite(buffer.wht, sizeof(double), size, fp);
	fclose(fp);

}
