#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct buff{
	char imageName[15];
	char name[15];
	unsigned char* img;
	int width, height, channels;
};

#include "read.c"
#include "write.c"
#include "arithmetics.c"
#include "brighten.c"
#include "display.c"

void addBuffer(struct buff buffer, struct buff* buffers, int* buffCount);
struct buff buffSearch(char* buffName, struct buff* buffers, int buffCount);
void printBuffer(struct buff* buffer, int buffCount);
void printMenu();
char *get_filename_ext(const char *filename);
int check_types(char* ext, char* file_types[]);

int main(int   argc, char** argv) {
	printf("Welcome to the UNIX Image Manipulation tool.\n");
	printf("Type \"menu\" to view the list of commands or \"list\" to view your buffers.\n\n");


	struct buff buffers[10];
	int buffCount = 0;

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
			char* ext = get_filename_ext(imageName);
			char* file_types[5] = {"jpeg","jpg","gif","tiff","png"}; //ALLOW NEW FILE TYPES HERE
			int approved = check_types(ext, file_types);
			if(approved != 1 ){
				printf("Error: Image file type is not approved.\n");
                exit(1);
            } 
			strtok(NULL," ");
			buffName = strtok(NULL," ");
			struct buff temp = readToBuff(imageName, buffName);
			addBuffer(temp, buffers, &buffCount);
		}
		else if(strcmp(command, "write")==0){
			buffName = strtok(NULL," ");
                        strtok(NULL," ");
                        imageName = strtok(NULL," ");
			writeToImage(buffSearch(buffName, buffers,buffCount), imageName);
		}
		else if(strcmp(command, "list")==0){
			printBuffer(buffers, buffCount);
		}
		else if(strcmp(command, "brighten")==0){
			buffName = strtok(NULL, " ");
			strtok(NULL, " ");
			imageName = strtok(NULL," ");
			brighten(buffSearch(buffName, buffers, buffCount), imageName, true);
		}
		else if(strcmp(command, "darken")==0){
			buffName = strtok(NULL, " ");
			strtok(NULL, " ");
			imageName = strtok(NULL," ");
			brighten(buffSearch(buffName, buffers, buffCount), imageName, false);
		}
		else if(strcmp(command, "display")==0){
			buffName = strtok(NULL, " ");
			printf("in display");
			displayImage(buffSearch(buffName, buffers, buffCount), argc, argv);
			// displayImage(buffName);
		}
		else if(strcmp(command, "quit")==0){
			break;
		}		else{
			strtok(NULL," ");
			char* buff1 = strtok(NULL," ");
                        char* cmd = strtok(NULL," ");
                        char* buff2 = strtok(NULL," ");
			if(strcmp(cmd,"+")==0){
				addBuffer(add(buffSearch(buff1, buffers,buffCount), buffSearch(buff2, buffers,buffCount), command),
					buffers, &buffCount);
			}
			else if(strcmp(cmd,"-")==0){
                                addBuffer(subtract(buffSearch(buff1, buffers,buffCount), buffSearch(buff2, buffers,buffCount), command),
                                        buffers, &buffCount);
                        }
			else if(strcmp(cmd,"*")==0){
                                addBuffer(multiply(buffSearch(buff1, buffers,buffCount), buffSearch(buff2, buffers,buffCount), command),
                                        buffers, &buffCount);
                        }
			else if(strcmp(cmd,"/")==0){
                                addBuffer(divide(buffSearch(buff1, buffers,buffCount), buffSearch(buff2, buffers,buffCount), command),
                                        buffers, &buffCount);
                        }
			else{
				printf("\nError: command not found.\n");
			}
		}

		gets(p);
	}

   	return 0;
}

void printMenu(){
	printf("\n----- Commands -----\n");
	printf("\"quit\"\n");
	printf("\"list\"\n");
	printf("\"display <buffer-name>\"\n");
	printf("\"read <image-name> into <buffer-name>\"\n");
	printf("\"write <buffer-name> into <image-name>\"\n");
	printf("addition: \"<buffer1> = <buffer2> + <buffer3>\"\n");
	printf("subtraction: \"<buffer1> = <buffer2> - <buffer3>\"\n");
	printf("multiplication: \"<buffer1> = <buffer2> * <buffer3>\"\n");
	printf("division: \"<buffer1> = <buffer2> / <buffer3>\"\n");
	printf("\"brighten <buffer1> into <buffer2>\"\n");
	printf("\"darken <buffer1> into <buffer2>\"\n\n");
}


void printBuffer(struct buff* buffers, int buffCount){
	printf("\n----- Buffers -----\n");
 	for (int i = 0; i < buffCount; i++){
                printf("%s contains %s\n", buffers[i].name, buffers[i].imageName);
        }
	printf("\n");
}

void addBuffer(struct buff buffer, struct buff* buffers, int* buffCount){
	int k = -1;
        for (int i = 0; i < *buffCount; i++){
        	if(strcmp(buffers[i].name, buffer.name)==0){
                        k = i;
                	break;
        	}
        }
	if(k == -1){
                buffers[*buffCount].img = buffer.img;
                strcpy(buffers[*buffCount].imageName, buffer.imageName);
		strcpy(buffers[*buffCount].name, buffer.name);
		buffers[*buffCount].width = buffer.width;
        	buffers[*buffCount].height = buffer.height;
        	buffers[*buffCount].channels = buffer.channels;
		(*buffCount)++;
        }
        else{
                buffers[k].img = buffer.img;
                strcpy(buffers[k].imageName, buffer.imageName);
                strcpy(buffers[k].name, buffer.name);
                buffers[k].width = buffer.width;
                buffers[k].height = buffer.height;
                buffers[k].channels = buffer.channels;
	}
}

struct buff buffSearch(char* buffName, struct buff* buffers, int buffCount){
	for (int i = 0; i < buffCount; i++){
                if(strcmp(buffers[i].name, buffName)==0){
                       	return buffers[i];
                }
        }
	printf("Error: buffer not found.\n");
	struct buff temp;
	return temp;
}

char *get_filename_ext(const char *filename){
    char *dot = strrchr(filename, '.');
    if(!dot || dot == filename) return "";
    return dot + 1;
}
int check_types(char* ext, char* file_types[]){
    for(int i =0; i< 3; i++){
        int temp = strcmp(ext,file_types[i]);
        if(temp == 0) return 1;
    }
    return 0;
}
