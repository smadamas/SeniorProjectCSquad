#include <stdio.h>

unsigned char* readToBuff(char* imageName, char* buffName){
	printf("\nReading %s into %s...\n", imageName, buffName);
<<<<<<< Updated upstream
	return NULL;
=======
	int width, height, ch;
	unsigned char* buff = stbi_load(imageName, &width, &height, &ch, 0);
	if(buffName == NULL){
		printf("Error reading file\n");
		exit(1);
	}
	printf("Done reading!\n\n");
	return buff;
>>>>>>> Stashed changes
}
