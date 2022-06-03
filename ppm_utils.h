/*
 * Le Nguyen
 *CPSC 1020 Summer 21
 *PA1
 *UserName: ltn
 *Instructor:  Dr. Yvon Feaster
*/
#ifndef PPM_UTILS
#define PPM_UTILS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <ctype.h>
#define MEDIAN 9
#define AVERAGE 10
/*
 struct header use to store magic number, width, height, and max color of the header
 */
typedef struct header {
  char MAGIC_NUMBER[3];
  unsigned int HEIGHT, WIDTH, MAX_COLOR;
} header_t;

// Represents an RGB pixel with integer values between 0-255
typedef struct pixel {
  unsigned char R, G, B;
} pixel_t;

// PPM Image representation
typedef struct image {
  header_t header;
  pixel_t* pixels;
} image_t;
/*
 parameter: name holding value of argv[].
 return: none
 this function is used to start the programe
 */
void startProgram(char** names);
/*
 parameter: argv, file pointer input[].
 return:none
 this function is used to create name of input files and open these file in read mode
 */
void openInputFiles(char* argv, FILE* inPut[]);
/*
 parameter: pointer img[] of image_t type.
 return: image_t* pic
 this function uses data of img[] passed from main to calculate the average value of each pixel and store it to a variable of image_t* type, and return it to main
 */
image_t* removeNoiseAverage(image_t* img[]);
/*
 parameter: array img of iamge_t* type.
 return: image_t* pic
 this function uses data of img[] passed from main to store value of RGB of each pixel of each image and store them in arrays. then sort values in each array, and assigns the 4th value in that array to pic. and finally return pic
 */
image_t* removeNoiseMedian(image_t* image[]);
/*
 parameter: FILE* image_file
 return: header_t data
 this function read header values from image[] passed from main and read header to variable data. then return data.
 */
header_t read_header(FILE* image_file);
/*
 parameter: FILE* image_file,header_t header
 return: image_t* image
 This function is calls read_header and read_p6 function to read header and all pixle from image_file to iamge and then return it.
 */
image_t* read_ppm(FILE* image_file);
/*
 parameter: FILE* image_file, header_t header
 return: image_t* data
 this function is called from read_ppm to read values of pixels to data, then return it.
 */
image_t* read_p6(FILE* image_file, header_t header);
/*
 parameter: FILE* out_file, header_t header
 return: none
 this function writes data from header to out_file which is passed from main.
 */
void write_header(FILE* out_file, header_t header);
/*
 parameter:FILE* out_file, image_t* image
 return:none
 this function writes values of pixels from image to out_file which is passed from main
 */
void write_p6(FILE* out_file, image_t* image);
/*
 parameter:unsigned int* arr, int n
 return: none
 this function is called from removeNoiseMedian() function to sort value of pixels in each array
 */
void sort(unsigned int* arr, int n);
/*
 parameter:unsigned int* a,unsigned int* b
 return: none
 this function is called from sort to swap 2 int pointer value
 */
void swap(unsigned int* a,unsigned int* b);
/*
 parameter: FILE *infileptr
 return: none
 this function is used to remove comments in the header.
 */
void ckws_comments (FILE *infileptr);

#endif
