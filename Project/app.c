#include <stdio.h>
#include <string.h>
#include "read.c"
#include "write.c"

void printMenu();

struct pixel{
	unsigned char red;
	unsigned char green;
	unsigned char blue;
};


int main() {
	printf("Welcome to the UNIX Image Manipulation tool.\n");
	printf("Type \"menu\" to view the list of commands.\n\n");

	char p[100];
	gets(p);

	while(strcmp(p,"quit") != 0){
		char *command;
		char *imageName;
		char *buffName;

		command = strtok(p," ");

		if(strcmp(p,"menu")==0){
                        printMenu();
                }
		else if(strcmp(command, "read")==0){
			imageName = strtok(NULL," ");
			strtok(NULL," ");
			buffName = strtok(NULL," ");
			readToBuff(imageName, buffName);
		}
		else if(strcmp(command, "write")==0){
			buffName = strtok(NULL," ");
                        strtok(NULL," ");
                        imageName = strtok(NULL," ");
			writeToImage(buffName, imageName);
		}
		else{
			printf("\nError: command not found.\n");
		}

		gets(p);
	}

   	return 0;
}

void printMenu(){
	printf("\n----- Commands -----\n");
	printf("\"quit\"\n");
	printf("\"read <image-name> into <buffer-name>\"\n");
	printf("\"write <buffer-name> into <image-name>\"\n\n");
}
