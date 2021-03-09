#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <setjmp.h>
#include "libgd/src/gd.h"

struct buff
{
	char imageName[32];
	char name[30];
	char status[30];
	unsigned char *img;
	int width, height, channels;
	gdImagePtr imrgb;
	int isLibgd;
};

#include "read.c"
#include "write.c"
#include "arithmetics.c"
#include "brighten.c"
#include "edge.c"
#include "display.c"
#include "histoEQ.c"
#include "rotation.c"
#include "blurr.c"
#include "sharpen.c"
#define KGRN "\x1B[32m"
#define KYEL "\x1B[33m"
#define KBLU "\x1B[34m"
#define KRED "\x1B[31m"
#define KMAG "\x1B[35m"
#define RESET "\x1B[0m"

void addBuffer(struct buff buffer, struct buff *buffers, int *buffCount);
struct buff buffSearch(char *buffName, struct buff *buffers, int buffCount);
void printBuffer(struct buff *buffer, int buffCount);
void printMenu();
char *get_filename_ext(const char *filename);
int check_types(char *ext, char *file_types[]);

int main(int argc, char **argv)
{
	printf(KGRN "Welcome to the UNIX Image Manipulation tool.\n");
	printf("Type \"" KYEL "menu" KGRN "\"  to view the list of commands or \"" KYEL "list" KGRN "\" to view your buffers.\n\n" RESET);

	struct buff buffers[10];
	int buffCount = 0;

	char p[100];
	gets(p);

	while (1)
	{
		char *command;
		char *imageName;
		char *buffName;
		char *amount;

		command = strtok(p, " ");

		if (strcmp(command, "menu") == 0)
		{
			printMenu();
		}
		else if (strcmp(command, "read") == 0)
		{
			imageName = strtok(NULL, " ");
			if (strlen(imageName) > 14)
			{
				printf(KRED "Error: " RESET "Image name too long. Image + extension must be shorter than 14 characters.\n");
			}
			else
			{
				char *ext = get_filename_ext(imageName);
				char *file_types[5] = {"jpeg", "jpg", "gif", "tiff", "png"}; //ALLOW NEW FILE TYPES HERE
				int approved = check_types(ext, file_types);
				if (approved != 1)
				{
					printf(KRED "Error: " RESET "Image file type is not approved.\n");
					exit(1);
				}
				strtok(NULL, " ");
				buffName = strtok(NULL, " ");
				struct buff temp = readToBuff(imageName, buffName);
				addBuffer(temp, buffers, &buffCount);
			}
		}
		else if (strcmp(command, "write") == 0)
		{
			buffName = strtok(NULL, " ");
			strtok(NULL, " ");
			imageName = strtok(NULL, " ");
			if (strlen(imageName) > 14)
			{
				printf(KRED "Error: " RESET "Image name too long. Image + extension must be shorter than 14 characters.\n");
			}
			else
			{
				printf(KYEL "\nWriting %s into %s...\n" RESET, buffName, imageName);
				writeToImage(buffSearch(buffName, buffers, buffCount), imageName);
				printf(KYEL "Done writing!\n\n" RESET);
			}
		}
		else if (strcmp(command, "list") == 0)
		{
			printBuffer(buffers, buffCount);
		}
		else if (strcmp(command, "brighten") == 0)
		{
			buffName = strtok(NULL, " ");
			strtok(NULL, " ");
			imageName = strtok(NULL, " ");
			if (strlen(imageName) > 14)
			{
				printf(KRED "Error: " RESET "Image name too long. Image + extension must be shorter than 14 characters.\n\n");
			}
			else
			{
				strtok(NULL, " ");
				amount = strtok(NULL, " ");
				if (amount != NULL){
					addBuffer(brighten(buffSearch(buffName, buffers, buffCount), imageName, true, atoi(amount)), buffers, &buffCount);
				}
				else {
					printf(KRED "Error: " RESET "Brightening routine not written in correct format.\n\n");
				}
			}
		}
		else if (strcmp(command, "darken") == 0)
		{
			buffName = strtok(NULL, " ");
			strtok(NULL, " ");
			imageName = strtok(NULL, " ");
			if (strlen(imageName) > 14)
			{
				printf(KRED "Error: " RESET "Image name too long. Image + extension must be shorter than 14 characters.\n");
			}
			else
			{
				strtok(NULL, " ");
				amount = strtok(NULL, " ");
				if (amount != NULL){
					addBuffer(brighten(buffSearch(buffName, buffers, buffCount), imageName, false, atoi(amount)), buffers, &buffCount);
				}
				else {
					printf(KRED "Error: " RESET "Darkening routine not written in correct format.\n");
				}
			}
		}
		else if (strcmp(command, "display") == 0)
		{
			buffName = strtok(NULL, " ");
			char tem[10] = "temp.png";

			struct buff temp = buffSearch(buffName, buffers, buffCount);
			if (strcmp(temp.status, "false") != 0)
			{
				writeToImage(temp, tem);
				displayImage(tem, argc, argv);
			}

			remove(tem);
		}
		else if (strcmp(command, "quit") == 0)
		{
			break;
		}
		else if (strcmp(command, "horizontal") == 0 || strcmp(command, "vertical") == 0)
		{
			char *type = strtok(NULL, " ");
			imageName = strtok(NULL, " ");
			if (strlen(imageName) > 14)
			{
				printf(KRED "Error: " RESET "Image name too long. Image + extension must be shorter than 14 characters.\n");
			}
			else
			{
				detectEdge(command, type, imageName);
				char name[50];
				strcpy(name, type);
				strcat(name, "-");
				strcat(name, command);
				strcat(name, "-");
				strcat(name, imageName);

				struct buff temp1;
				if (strcmp(type, "sobel") == 0)
				{
					temp1 = readToBuff(name, strcat(command, "Sob"));
				}
				else if (strcmp(type, "prewitt") == 0)
				{
					temp1 = readToBuff(name, strcat(command, "Pre"));
				}
				else if (strcmp(type, "kirsch") == 0)
				{
					temp1 = readToBuff(name, strcat(command, "Kir"));
				}

				addBuffer(temp1, buffers, &buffCount);
			}
		}
		else if (strcmp(command, "combined") == 0)
		{

			char *type = strtok(NULL, " ");
			imageName = strtok(NULL, " ");
			if (strcmp(type, "sobel") == 0)
			{
				detectEdge("vertical", type, imageName);
				detectEdge("horizontal", type, imageName);
				char vertname[50];
				char horizname[50];
				strcpy(vertname, "sobel-vertical-");
				strcat(vertname, imageName);
				strcpy(horizname, "sobel-horizontal-");
				strcat(horizname, imageName);
				struct buff temp1 = readToBuff(vertname, "sobelvert");
				struct buff temp2 = readToBuff(horizname, "sobelhoriz");
				remove(vertname);
				remove(horizname);
				addBuffer(temp1, buffers, &buffCount);
				addBuffer(temp2, buffers, &buffCount);
				addBuffer(combine(buffSearch("sobelvert", buffers, buffCount), buffSearch("sobelhoriz", buffers, buffCount), "SobelCombined"),
						  buffers, &buffCount);
			}
			else if (strcmp(type, "prewitt") == 0)
			{
				detectEdge("vertical", type, imageName);
				detectEdge("horizontal", type, imageName);
				char vertname[50];
				char horizname[50];
				strcpy(vertname, "prewitt-vertical-");
				strcat(vertname, imageName);
				strcpy(horizname, "prewitt-horizontal-");
				strcat(horizname, imageName);
				struct buff temp1 = readToBuff(vertname, "prewittvert");
				struct buff temp2 = readToBuff(horizname, "prewitthoriz");
				remove(vertname);
				remove(horizname);
				addBuffer(temp1, buffers, &buffCount);
				addBuffer(temp2, buffers, &buffCount);
				addBuffer(combine(buffSearch("prewittvert", buffers, buffCount), buffSearch("prewitthoriz", buffers, buffCount), "PrewittCombined"),
						  buffers, &buffCount);
			}
			else if (strcmp(type, "kirsch") == 0)
			{
				detectEdge("vertical", type, imageName);
				detectEdge("horizontal", type, imageName);
				char vertname[50];
				char horizname[50];
				strcpy(vertname, "kirsch-vertical-");
				strcat(vertname, imageName);
				strcpy(horizname, "kirsch-horizontal-");
				strcat(horizname, imageName);
				struct buff temp1 = readToBuff(vertname, "kirschvert");
				struct buff temp2 = readToBuff(horizname, "kirschhoriz");
				remove(vertname);
				remove(horizname);
				addBuffer(temp1, buffers, &buffCount);
				addBuffer(temp2, buffers, &buffCount);
				addBuffer(combine(buffSearch("kirschvert", buffers, buffCount), buffSearch("kirschhoriz", buffers, buffCount), "KirschCombined"),
						  buffers, &buffCount);
			}
			else {
				printf(KRED "\nError: " RESET "Phrase following combined must be edge detection type.\n\n");
			}
		}
		else if (strcmp(command, "addition") == 0 || strcmp(command, "subtraction") == 0 || strcmp(command, "division") == 0 || strcmp(command, "multiplication") == 0)
		{
			strtok(NULL, " ");
			buffName = strtok(NULL, " ");
			strtok(NULL, " ");
			char *buff1 = strtok(NULL, " ");
			char *cmd = strtok(NULL, " ");
			char *buff2 = strtok(NULL, " ");
			if (strcmp(cmd, "+") == 0)
			{
				addBuffer(add(buffSearch(buff1, buffers, buffCount), buffSearch(buff2, buffers, buffCount), buffName),
						  buffers, &buffCount);
			}
			else if (strcmp(cmd, "-") == 0)
			{
				addBuffer(subtract(buffSearch(buff1, buffers, buffCount), buffSearch(buff2, buffers, buffCount), buffName),
						  buffers, &buffCount);
			}
			else if (strcmp(cmd, "*") == 0)
			{
				addBuffer(multiply(buffSearch(buff1, buffers, buffCount), buffSearch(buff2, buffers, buffCount), buffName),
						  buffers, &buffCount);
			}
			else if (strcmp(cmd, "/") == 0)
			{
				addBuffer(divide(buffSearch(buff1, buffers, buffCount), buffSearch(buff2, buffers, buffCount), buffName),
						  buffers, &buffCount);
			}
			else
			{
				printf(KRED "Error:" RESET " Arithmetic syntax incorrect\n");
			}
		}
		else if ((strcmp(command, "histeq") == 0))
		{
			char *buff1 = strtok(NULL, " ");
			struct buff temp = buffSearch(buff1, buffers, buffCount);
			temp = histogramEqualization(temp, command);
			addBuffer(temp, buffers, &buffCount);
		}
		else if ((strcmp(command, "flip") == 0))
		{
			char *rot = strtok(NULL, " ");
			if ((strcmp(rot, "vertical") == 0))
			{
				buffName = strtok(NULL, " ");
				struct buff temp = buffSearch(buffName, buffers, buffCount);
				temp = verticalFlip(temp);
				addBuffer(temp, buffers, &buffCount);
			}
			else if (strcmp(rot, "horizontal") == 0)
			{
				buffName = strtok(NULL, " ");
				struct buff temp = buffSearch(buffName, buffers, buffCount);
				temp = horizontalFlip(temp);
				addBuffer(temp, buffers, &buffCount);
			}
			else
			{
				printf(KRED "Error: " RESET "Invalid mirroring!\n");
			}
		}
		else if ((strcmp(command, "rotate") == 0))
		{
			char *rot = strtok(NULL, " ");
			if ((strcmp(rot, "left") == 0))
			{
				buffName = strtok(NULL, " ");
				struct buff temp = buffSearch(buffName, buffers, buffCount);
				temp = leftRotate(temp);
				addBuffer(temp, buffers, &buffCount);
			}
			else if ((strcmp(rot, "right") == 0))
			{
				buffName = strtok(NULL, " ");
				struct buff temp = buffSearch(buffName, buffers, buffCount);
				temp = rightRotate(temp);
				addBuffer(temp, buffers, &buffCount);
			}
			else
			{
				printf(KRED "Error: " RESET " Invalid Rotation!\n");
			}
		}
		else if((strcmp(command, "blurr") == 0))
		{
			buffName = strtok(NULL, " ");
			char* radius = strtok(NULL, " ");
			char* sigma = strtok(NULL, " ");
			struct buff temp = blurr(buffSearch(buffName, buffers, buffCount), atoi(radius), atof(sigma));
			addBuffer(temp, buffers, &buffCount);
		}
		else if((strcmp(command, "sharpen") == 0))
		{
			buffName = strtok(NULL, " ");
			strtok(NULL, " ");
			char* percent = strtok(NULL, " ");
			struct buff temp = sharpen(buffSearch(buffName, buffers, buffCount), atof(percent));
			addBuffer(temp, buffers, &buffCount);
		}
		else
		{
			printf(KRED "Error: " RESET "Command not found or not supported, please type menu for list of commands.\n");
		}

		gets(p);
	}
}

void printMenu()
{
	printf(KGRN "\n----- Commands -----\n");
	printf(KBLU "Exit Program: " RESET "\"quit\"\n");
	printf(KBLU "List Buffers: " RESET "\"list\"\n");
	printf(KBLU "Show Image in Buffer: " RESET "\"display <buffer-name>\"\n");
	printf(KBLU "Input Image: " RESET "\"read <image-name> into <buffer-name>\"\n");
	printf(KBLU "Output Image: " RESET "\"write <buffer-name> into <image-name>\"\n");

	printf(KBLU "Addition: " RESET "\"addition : <buffer-name> = <buffer2> + <buffer3>\"\n");
	printf(KBLU "Subtraction: " RESET "\"subtraction : <buffer-name> = <buffer2> - <buffer3>\"\n");
	printf(KBLU "Multiplication " RESET "\"multiplication : <buffer-name> = <buffer2> * <buffer3>\"\n");
	printf(KBLU "Division: " RESET "\"division : <buffer-name> = <buffer2> / <buffer3>\"\n");
	printf(KBLU "Brighten: " RESET "\"brighten <buffer1> into <buffer2> by <value between 0 and 255>\"\n");
	printf(KBLU "Darken: " RESET "\"darken <buffer1> into <buffer2> by <value between 0 and 255>\"\n");

	printf(KBLU "Edge Detection: " RESET "\"<horizontal/vertical/combined> <kirsch/prewitt/sobel> <image-name>\"\n");
	printf(KBLU "Histogram Equalization: " RESET "\"histeq <buffer>\"\n");
	printf(KBLU "Flip: " RESET "\"flip <vertical/horizontal> <buffer>\"\n");
	printf(KBLU "Rotation: " RESET "\"rotate <left/right> <buffer>\"\n");
	printf(KBLU "Blurring: " RESET "\"blurr <buffer> <radius> <sigma>\"\n");
	printf(KBLU "Blurring: " RESET "\"sharpen <buffer> by <desired percentage>\"\n\n");
}

void printBuffer(struct buff *buffers, int buffCount)
{
	printf(KGRN "\n----- Buffers -----\n" RESET);
	for (int i = 0; i < buffCount; i++)
	{
		printf("%s " KBLU "contains" RESET " %s\n", buffers[i].name, buffers[i].imageName);
	}
	printf("\n");
}

void addBuffer(struct buff buffer, struct buff *buffers, int *buffCount)
{
	int k = -1;
	for (int i = 0; i < *buffCount; i++)
	{
		if (strcmp(buffers[i].name, buffer.name) == 0)
		{
			k = i;
			break;
		}
	}
	if (k == -1)
	{
		buffers[*buffCount].img = buffer.img;
		strcpy(buffers[*buffCount].imageName, buffer.imageName);
		strcpy(buffers[*buffCount].name, buffer.name);
		buffers[*buffCount].width = buffer.width;
		buffers[*buffCount].height = buffer.height;
		buffers[*buffCount].channels = buffer.channels;
		buffers[*buffCount].imrgb = buffer.imrgb;
		buffers[*buffCount].isLibgd = buffer.isLibgd;
		(*buffCount)++;
	}
	else
	{
		buffers[k].img = buffer.img;
		strcpy(buffers[k].imageName, buffer.imageName);
		strcpy(buffers[k].name, buffer.name);
		buffers[k].width = buffer.width;
		buffers[k].height = buffer.height;
		buffers[k].channels = buffer.channels;
		buffers[k].imrgb = buffer.imrgb;
		buffers[k].isLibgd = buffer.isLibgd;
	}

	printf(KYEL "New buffer added\n\n" RESET);
}

struct buff buffSearch(char *buffName, struct buff *buffers, int buffCount)
{
	for (int i = 0; i < buffCount; i++)
	{
		if (strcmp(buffers[i].name, buffName) == 0)
		{
			return buffers[i];
		}
	}
	printf(KRED "Error:" RESET " buffer not found.\n");

	struct buff temp;
	strcpy(temp.status, "false");
	return temp;
}

char *get_filename_ext(const char *filename)
{
	char *dot = strrchr(filename, '.');
	if (!dot || dot == filename)
		return "";
	return dot + 1;
}
int check_types(char *ext, char *file_types[])
{
	for (int i = 0; i < 5; i++)
	{
		int temp = strcmp(ext, file_types[i]);
		if (temp == 0)
			return 1;
	}
	return 0;
}