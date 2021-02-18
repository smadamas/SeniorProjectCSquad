#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libgd/src/gd.h"

struct buff
{
	char imageName[15];
	char name[15];
	unsigned char *img;
	int width, height, channels;
	gdImagePtr imrgb;
};

#include "read.c"
#include "write.c"
#include "arithmetics.c"
#include "histoEQ.c"

void addBuffer(struct buff buffer, struct buff *buffers, int *buffCount);
struct buff buffSearch(char *buffName, struct buff *buffers, int buffCount);
void printBuffer(struct buff *buffer, int buffCount);
void printMenu();

struct buff histogramEqualisation(struct buff a, char *buffName);

int main()
{
	printf("Welcome to the UNIX Image Manipulation tool.\n");
	printf("Type \"menu\" to view the list of commands or \"list\" to view your buffers.\n\n");

	struct buff buffers[10];
	int buffCount = 0;

	char p[100];

	//strcpy(p,p2);
	fgets(p, 100, stdin);

	while (1)
	{
		//gets is depreciated

		char *p2 = strtok(p, "\n");
		char *command;
		char *imageName;
		char *buffName;
		char *p3 = p2;

		command = strtok(p3, " ");

		if (strcmp(command, "menu") == 0)
		{
			printMenu();
		}
		else if (strcmp(command, "read") == 0)
		{
			imageName = strtok(NULL, " ");
			strtok(NULL, " ");
			buffName = strtok(NULL, " ");
			struct buff temp = readToBuff(imageName, buffName);
			addBuffer(temp, buffers, &buffCount);
			// FILE* out = fopen("temp.png", "wb");
			// gdImagePngEx(buffers[0].imrgb, out, 9);
		}
		else if (strcmp(command, "write") == 0)
		{
			buffName = strtok(NULL, " ");
			strtok(NULL, " ");
			imageName = strtok(NULL, " ");
			writeToImage(buffSearch(buffName, buffers, buffCount), imageName);
		}
		else if (strcmp(command, "list") == 0)
		{
			printBuffer(buffers, buffCount);
		}
		else if (strcmp(command, "quit") == 0)
		{
			break;
		}
		else
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
			else if ((strcmp(buff1, "histeq") == 0))
			{
				struct buff temp = buffSearch(cmd, buffers, buffCount);
				// FILE* out = fopen("temp.png", "wb");
				// gdImagePngEx(temp.imrgb, out, 9);
				// printf("values are %d %d %d", temp.height, temp.width, temp.channels);
				addBuffer(histogramEqualisation(temp, command), buffers, &buffCount);
			}
			else
			{
				printf("\nError: command not found.\n");
			}
		}

		fgets(p, 100, stdin);
	}

	return 0;
}

void printMenu()
{
	printf("\n----- Commands -----\n");
	printf("\"quit\"\n");
	printf("\"list\"\n");
	printf("\"read <image-name> into <buffer-name>\"\n");
	printf("\"write <buffer-name> into <image-name>\"\n");
	printf("addition: \"<buffer1> = <buffer2> + <buffer3>\"\n");
	printf("subtraction: \"<buffer1> = <buffer2> - <buffer3>\"\n");
	printf("multiplication: \"<buffer1> = <buffer2> * <buffer3>\"\n");
	printf("division: \"<buffer1> = <buffer2> / <buffer3>\"\n");
	printf("histEQ: \"<buffer_dest> := histeq <buffer>\"\n\n");
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
	return temp;
}
