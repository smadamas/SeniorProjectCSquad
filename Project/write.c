/// \file write.c
#include <stdio.h>
#include <stdlib.h>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#define KYEL "\x1B[33m" ///< Yellow terminal text color
#define KRED "\x1B[31m" ///< Red terminal text color
#define RESET "\x1B[0m" ///< Reset terminal text color to default

void write_to_wht(struct buff buffer, char* imageName);

/**
 * Writes a buffer to disk with specified filename (with extension)
 * \param buffer Source image buffer to be written to disk
 * \param imageName Desired filename of image
 * \param wht Specification of whether or not the buffer is a wht buffer
 */
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

/**
 * Write Walsh-Hadamard transformed buffer to disk with specified filename
 * \param buffer Source wht image buffer
 * \param imageName Desired filename of image
 *
 */
void write_to_wht(struct buff buffer, char* imageName) {
	int size = buffer.height * buffer.width * buffer.channels;
	char name[30];
	strcpy(name, imageName);
	strcat(name, ".wht");
	FILE* fp = fopen(name, "w");
	fwrite(&buffer.height, sizeof(int), 1, fp);
	fwrite(&buffer.width, sizeof(int), 1, fp);
	fwrite(&buffer.channels, sizeof(int), 1, fp);
	fwrite(&buffer.has_wht, sizeof(int), 1, fp);
	fwrite(buffer.wht, sizeof(double), size, fp);
	fclose(fp);

}
