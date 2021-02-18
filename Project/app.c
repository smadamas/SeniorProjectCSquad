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
};

#include "read.c"
#include "write.c"
#include "arithmetics.c"
#include "brighten.c"
#include "edge.c"
#include "display.c"
#include "histoEQ.c"

void addBuffer(struct buff buffer, struct buff *buffers, int *buffCount);
struct buff buffSearch(char *buffName, struct buff *buffers, int buffCount);
void printBuffer(struct buff *buffer, int buffCount);
void printMenu();
char *get_filename_ext(const char *filename);
int check_types(char *ext, char *file_types[]);

int main(int argc, char **argv)
{
	printf("Welcome to the UNIX Image Manipulation tool.\n");
	printf("Type \"menu\" to view the list of commands or \"list\" to view your buffers.\n\n");

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
				printf("Image name too long. Image + extension must be shorter than 14 characters.\n");
			}
			else
			{
				char *ext = get_filename_ext(imageName);
				char *file_types[5] = {"jpeg", "jpg", "gif", "tiff", "png"}; //ALLOW NEW FILE TYPES HERE
				int approved = check_types(ext, file_types);
				if (approved != 1)
				{
					printf("Error: Image file type is not approved.\n");
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
				printf("Image name too long. Image + extension must be shorter than 14 characters.\n");
			}
			else
			{
				printf("\nWriting %s into %s...\n", buffName, imageName);
				writeToImage(buffSearch(buffName, buffers, buffCount), imageName);
				printf("Done writing!\n\n");
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
				printf("Image name too long. Image + extension must be shorter than 14 characters.\n");
			}
			else
			{
				strtok(NULL, " ");
				amount = strtok(NULL, " ");
				addBuffer(brighten(buffSearch(buffName, buffers, buffCount), imageName, true, atoi(amount)), buffers, &buffCount);
			}
		}
		else if (strcmp(command, "darken") == 0)
		{
			buffName = strtok(NULL, " ");
			strtok(NULL, " ");
			imageName = strtok(NULL, " ");
			if (strlen(imageName) > 14)
			{
				printf("Image name too long. Image + extension must be shorter than 14 characters.\n");
			}
			else
			{
				strtok(NULL, " ");
				amount = strtok(NULL, " ");
				addBuffer(brighten(buffSearch(buffName, buffers, buffCount), imageName, false, atoi(amount)), buffers, &buffCount);
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
				printf("Image name too long. Image + extension must be shorter than 14 characters.\n");
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
				else
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
				addBuffer(temp1, buffers, &buffCount);
				addBuffer(temp2, buffers, &buffCount);
				addBuffer(combine(buffSearch("sobelvert", buffers, buffCount), buffSearch("sobelhoriz", buffers, buffCount), "combined"),
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
				addBuffer(temp1, buffers, &buffCount);
				addBuffer(temp2, buffers, &buffCount);
				addBuffer(combine(buffSearch("prewittvert", buffers, buffCount), buffSearch("prewitthoriz", buffers, buffCount), "combined"),
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
				addBuffer(temp1, buffers, &buffCount);
				addBuffer(temp2, buffers, &buffCount);
				addBuffer(combine(buffSearch("kirschvert", buffers, buffCount), buffSearch("kirschhoriz", buffers, buffCount), "combined"),
						  buffers, &buffCount);
			}

			/*
			char *type = strtok(NULL, " ");
			imageName = strtok(NULL, " ");
			if (strlen(imageName) > 14){
				printf("Image name too long. Image + extension must be shorter than 14 characters.\n");
			}
			else {
				detectEdge("vertical", type, imageName);
				detectEdge("horizontal", type, imageName);
				char vertname[50];
				char horizname[50];
				strcpy(vertname, type);
				strcat(vertname, "-");
				strcat(vertname, command);
				strcat(vertname, "-");
				strcat(vertname, imageName);
				strcpy(horizname, type);
				strcat(horizname, "-horiz-");
				strcat(horizname, imageName);

				char vertBuffLabel[50];
				char horizBuffLabel[50];
				if (strcmp(type, "sobel") == 0){
					strcpy(vertBuffLabel, "vertSob");
					strcpy(horizBuffLabel, "horizSob");
				}
				else if (strcmp(type, "prewitt") == 0){
					strcpy(vertBuffLabel, "vertPre");
					strcpy(horizBuffLabel, "horizPre");
				}
				else {
					strcpy(vertBuffLabel, "vertKir");
					strcpy(horizBuffLabel, "horizKir");
				}

				
				struct buff temp1;
				temp1 = readToBuff(vertname, vertBuffLabel);
				struct buff temp2 = readToBuff(horizname, horizBuffLabel);
				addBuffer(temp1, buffers, &buffCount);
				addBuffer(temp2, buffers, &buffCount);
				struct buff temp3 = combine(buffSearch("label1", buffers, buffCount), buffSearch("label2", buffers, buffCount), type);
				addBuffer(temp3, buffers, &buffCount); 
				
			}
			*/
		}
		else if (strcmp(command, "addition") == 0 || strcmp(command, "subtraction") == 0 || strcmp(command, "division") == 0 || strcmp(command, "multiplication") == 0)
		{
			strtok(NULL, " ");
			char *buff1 = strtok(NULL, " ");
			char *cmd = strtok(NULL, " ");
			char *buff2 = strtok(NULL, " ");
			if (strcmp(cmd, "+") == 0)
			{
				addBuffer(add(buffSearch(buff1, buffers, buffCount), buffSearch(buff2, buffers, buffCount), command),
						  buffers, &buffCount);
			}
			else if (strcmp(cmd, "-") == 0)
			{
				addBuffer(subtract(buffSearch(buff1, buffers, buffCount), buffSearch(buff2, buffers, buffCount), command),
						  buffers, &buffCount);
			}
			else if (strcmp(cmd, "*") == 0)
			{
				addBuffer(multiply(buffSearch(buff1, buffers, buffCount), buffSearch(buff2, buffers, buffCount), command),
						  buffers, &buffCount);
			}
			else if (strcmp(cmd, "/") == 0)
			{
				addBuffer(divide(buffSearch(buff1, buffers, buffCount), buffSearch(buff2, buffers, buffCount), command),
						  buffers, &buffCount);
			}
			else
			{
				printf("\nError: Arithmetic syntax incorrect\n");
			}
		}
		else if ((strcmp(command, "histeq") == 0))
		{
			char *buff1 = strtok(NULL, " ");
			struct buff temp = buffSearch(buff1, buffers, buffCount);
			histogramEqualization(temp, command);
		}
		else
		{
			printf("\nCommand not found or not supported, please type menu for list of commands.\n\n");
		}

		gets(p);
	}
}

void printMenu()
{
	printf("\n----- Commands -----\n");
	printf("\"quit\"\n");
	printf("\"list\"\n");
	printf("\"display <buffer-name>\"\n");
	printf("\"read <image-name> into <buffer-name>\"\n");
	printf("\"write <buffer-name> into <image-name>\"\n");
	printf("\"addition : <buffer2> + <buffer3>\"\n");
	printf("\"subtraction : <buffer2> + <buffer3>\"\n");
	printf("\"multiplication : <buffer2> + <buffer3>\"\n");
	printf("\"division : <buffer2> + <buffer3>\"\n");
	printf("\"brighten <buffer1> into <buffer2>\"\n");
	printf("\"darken <buffer1> into <buffer2>\"\n");
	printf("\"<horizontal/vertical/combined> <kirsch/prewitt/sobel> <image-name>\"\n\n");
	printf("histEQ: \"histeq <buffer>\"\n\n");
}

void printBuffer(struct buff *buffers, int buffCount)
{
	printf("\n----- Buffers -----\n");
	for (int i = 0; i < buffCount; i++)
	{
		printf("%s contains %s\n", buffers[i].name, buffers[i].imageName);
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
	}

	printf("New buffer added\n\n");
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
	printf("Error: buffer not found.\n");
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
