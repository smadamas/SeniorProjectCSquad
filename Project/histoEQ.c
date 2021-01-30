// C program to perform histogram equalisation to adjust contrast levels 

#include <fcntl.h> 
#include <math.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
  
// Function to perform histogram equalisation on an image 
// Function takes total rows, columns, input file

struct buff histogramEqualisation(struct buff a) 
{ 
    // creating image pointer 
    unsigned char* image; 

    //Instantiating Rows and Cols
    int cols = a.width;
    int rows = a.height;
    
    // Declaring 2 arrays for storing histogram values (frequencies) and 
    // new gray level values (newly mapped pixel values as per algorithm) 
    int hist[256] = { 0 }; 
    int new_gray_level[256] = { 0 }; 
  
    // Declaring other important variables 
    int col, row, total, curr, i; 
  
    // allocating image array the size equivalent to number of columns 
    // of the image to read one row of an image at a time 
    image = (unsigned char*)calloc(cols, sizeof(unsigned char)); 
  
    // opening input file in Read Only Mode 
    int input_file = a.width * a.height; 

    if (input_file < 0) { 
        printf("Error reading input file\n"); 
        exit(1); 
    } 
  
    // creating output file that has write and read access 
    //output_file = creat(output_file_name, 0666); 
    //if (output_file < 0) { 
    //    printf("Error creating output file\n"); 
    //    exit(1); 
    //} 
  
    // Calculating frequency of occurrence for all pixel values 
    for (row = 0; row < rows; row++) { 
        // reading a row of image 
        //read(input_file, &image[0], cols * sizeof(unsigned char)); 
        for(int i=0; i<cols; i++){
            image[i] = a.img[i];
        }
        // logic for calculating histogram 
        for (col = 0; col < cols; col++) 
            hist[(int)a.img[col]]++; 
    } 
  
    // calculating total number of pixels 
    total = cols * rows; 
  
    curr = 0; 
  
    // calculating cumulative frequency and new gray levels 
    for (i = 0; i < 256; i++) { 
        // cumulative frequency 
        curr += hist[i]; 
  
        // calculating new gray level after multiplying by 
        // maximum gray count which is 255 and dividing by 
        // total number of pixels 
        new_gray_level[i] = round((((float)curr) * 255) / total); 
    } 
  
    // closing file 
    //close(input_file); 
  
    // reopening file in Read Only Mode 
    //input_file = open(input_file_name, O_RDONLY); 
  
    // performing histogram equalisation by mapping new gray levels 
    for (row = 0; row < rows; row++) { 
        // reading a row of image 
        //read(input_file, &image[0], cols * sizeof(unsigned char)); 
        for(int i=0; i<cols; i++){
            image[i] = a.img[i];
        }
        // mapping to new gray level values 
        for (col = 0; col < cols; col++) 
            image[col] = (unsigned char)new_gray_level[image[col]]; 
  
        // reading new gray level mapped row of image 
        //write(output_file, &image[0], cols * sizeof(unsigned char)); 
    }

    struct buff newBuff;

    // Fill in info for buffer
    char * nombre = a.imageName;
	strcpy(newBuff.imageName, nombre);

    //Need to pass in extension
	strcat(newBuff.imageName, "extension");
    
    //Change name
    char * B_nombre = a.imageName;
	strcpy(newBuff.name, B_nombre);
	newBuff.width = a.width;
	newBuff.height = a.height;
	newBuff.channels = a.channels;

	size_t size = newBuff.width * newBuff.height * newBuff.channels; // Allocate memory for result
	unsigned char* result_img = malloc(size);
	if (result_img == NULL) {
		printf("Unable to allocate memory for the image.\n");
		exit(1);
	}

	newBuff.img = result_img;

    // freeing dynamically allocated memory 
    free(image); 
  
    // closing input and output files 
    //close(input_file); 

    return newBuff;
} 
