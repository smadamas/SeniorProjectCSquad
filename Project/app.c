#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "read.c"
#include "write.c"


void printMenu();


struct buff{
	char* imageName;
	char* name;
	unsigned char* buff;
};

//void addBuffer(char* buffName, unsigned char* buffer, char* imageName, struct pair* buffers, int* buffCount);
void printBuffer(struct buff buffer);


int main() {
	printf("Welcome to the UNIX Image Manipulation tool.\n");
	printf("Type \"menu\" to view the list of commands or \"list\" to view your buffers.\n\n");


	struct buff buffer;

	char p[100];
	gets(p);

	while(1){
		char *command;
		char *imageName;
		char *buffName;

		command = strtok(p," ");


		if(strcmp(command,"menu")==0){
                        printMenu();
                }
		else if(strcmp(command, "read")==0){
			imageName = strtok(NULL," ");
			strtok(NULL," ");
			buffName = strtok(NULL," ");
			buffer.buff = readToBuff(imageName, buffName);
			buffer.name = buffName;
			buffer.imageName = imageName;
		}
		else if(strcmp(command, "write")==0){
			buffName = strtok(NULL," ");
                        strtok(NULL," ");
                        imageName = strtok(NULL," ");
			writeToImage(buffName, imageName);
		}
		else if(strcmp(command, "list")==0){
			printBuffer(buffer);
		}
		else if(strcmp(command, "quit")==0){
			break;
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


void printBuffer(struct buff buffer){
	printf("\n----- Buffers -----\n");
	printf("%s contains %s\n", buffer.name, buffer.imageName);
}

/*void addBuffer(char* buffName, unsigned char* buffer, char* imageName, struct pair* buffers, int* buffCount){
	int k = -1;
        for (int i = 0; i < *buffCount; i++){
        	if(strcmp(buffers[i].buffName, buffName)==0){
                        k = i;
                	break;
        	}
        }
	if(k == -1){
                buffers[*buffCount].buff = buffer;
                buffers[*buffCount].imageName = imageName;
                buffers[*buffCount].buffName = buffName;
		(*buffCount)++;
		printf("new\n");
        }
        else{
                buffers[k].buff = buffer;
                buffers[k].imageName = imageName;
                buffers[k].buffName = buffName;
		printf("old\n");
	}
}*/
