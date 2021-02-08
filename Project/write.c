#include <stdio.h>
#include <stdlib.h>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"


void writeToImage(struct buff buffer, char* imageName){
    printf("\nWriting %s into %s...\n",buffer.name, imageName);
	char* temp = strtok(imageName, ".");
	char* ext = strtok(NULL," ");
	if(buffer.name == NULL){
		printf("Error: buffer is empty.\n");
	}
	else if(strcmp(ext, "png")==0){
		stbi_write_png(strcat(temp,".png"), buffer.width, buffer.height, buffer.channels, buffer.img, buffer.width * buffer.channels);
		printf("Done writing!\n\n");
	}
	else if(strcmp(ext, "jpg")==0){
		stbi_write_jpg(strcat(temp,".jpg"), buffer.width, buffer.height, buffer.channels, buffer.img, buffer.width * buffer.channels);
		printf("Done writing!\n\n");
	}
	else if(strcmp(ext, "tiff")==0){
                stbi_write_jpg(strcat(temp,".tiff"), buffer.width, buffer.height, buffer.channels, buffer.img, buffer.width* buffer.channels);
                printf("Done writing!\n\n");
        }
	else if(strcmp(ext, "gif")==0){
                stbi_write_jpg(strcat(temp,".gif"), buffer.width, buffer.height, buffer.channels, buffer.img, buffer.width * buffer.channels);
                printf("Done writing!\n\n");
        }
	else{
		printf("File type not supported yet.\n\n");
	}
}