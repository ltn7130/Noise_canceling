/*
 * Le Nguyen
 *CPSC 1020 Summer 21
 *PA1
 *UserName: ltn
 *Instructor:  Dr. Yvon Feaster
*/
#include "ppm_utils.h"
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <ctype.h>

#define MEDIAN 9
#define AVERAGE 10


void startProgram(char** names)
{
    FILE* noisyInPut[AVERAGE];
    FILE* peskyInPut[MEDIAN];
    //These variables are the images used hold the input image data
    image_t* noisyImages[AVERAGE];
    image_t* peskyImages[MEDIAN];
    int i = 0;
    
    if(strcmp(names[1], "average") == 0)
    {
        FILE* noisyOutPut = fopen(names[2], "w");
        openInputFiles(names[1], noisyInPut);

        for(i = 0; i < AVERAGE; i++)
        {
          noisyImages[i] = read_ppm(noisyInPut[i]);
        }
        //Call remove noise pass in the array of noisyImages and the output file for
        //the output file pointer
        image_t* nOut = removeNoiseAverage(noisyImages);
        write_p6(noisyOutPut, nOut);
        //close file
        fclose(noisyOutPut);
        //free allocated memory
        for(int k = 0; k < AVERAGE; ++k)
        {
            free(noisyImages[k]);
        }
    }
    
    else
    {
        FILE* peskyOutPut = fopen(names[2], "w");
        openInputFiles(names[1], peskyInPut);
        for(i = 0; i < MEDIAN; i++)
        {
          peskyImages[i] = read_ppm(peskyInPut[i]);
        }
        //Call remove noise pass in the array of noisyImages and the output file for
        //the output file pointer
        image_t* nOut = removeNoiseMedian(peskyImages);
        write_p6(peskyOutPut, nOut);
        //close file
        fclose(peskyOutPut);
        //free allocated memory
        for(int j = 0; j < MEDIAN; ++j)
        {
            free(peskyImages[j]);
        }
    }
}

image_t* removeNoiseMedian(image_t* image[])
{
    int row = image[1]->header.HEIGHT;
    int col = image[1]->header.WIDTH;
    //used this variable to store new calculated data and return to main
    image_t* pic = (image_t*)malloc(row*sizeof(image_t));
    //callocate memory for pic
    for (int h = 0; h < row  ; ++h)
    {
        pic[h].pixels = (pixel_t*)malloc(col*sizeof(pixel_t));
    }
    //assign data from header to pic
    pic->header.HEIGHT =image[1]->header.HEIGHT;
    pic->header.WIDTH=image[1]->header.WIDTH;
    pic->header.MAX_COLOR =image[1]->header.MAX_COLOR;
    strcpy(pic->header.MAGIC_NUMBER, image[1]->header.MAGIC_NUMBER);
    //used these arrays to store red green and blue values of each pixel
    unsigned int red[9];
    unsigned int green[9];
    unsigned  int blue[9];
    // use loop to store red green blue values of each pixel of 9 images to the arrays. then sort these value and assign the 4th value to pic.
    for (int j = 0; j < row; ++j)
    {
        for (int k = 0; k < col; ++k)
        {
            for (int i =0; i < MEDIAN; ++i)
            {
                // store RGB value in each pixel to arrays
                red[i] = image[i][j].pixels[k].R;
                green[i] = image[i][j].pixels[k].G;
                blue[i] = image[i][j].pixels[k].B;
            }
            //sort values in each array
            sort(red, MEDIAN);
            sort(green, MEDIAN);
            sort(blue, MEDIAN);
            //assign 4th value to pic
            pic[j].pixels[k].R = red[3];
            pic[j].pixels[k].G = green[3];
            pic[j].pixels[k].B = blue[3];
        }
    }
    return pic;
}
void sort(unsigned int* arr, int n)
{
   int i, j;
   for(i = 0; i < n-1; i++)
   {
     // Last i elements are already in place
      for(j = 0; j < n-i-1; j++)
      {
        if (arr[j] > arr[j+1])
        {
            //swap 2 values
          swap(&arr[j], &arr[j+1]);
        }
      }
    }
}

void swap(unsigned int* a,unsigned int* b)
{
   unsigned int temp;
    // temp tempolarilly holds value of a
    temp = *a;
    // set value of b to a
    *a = *b;
    // set value of b to temp which is holding initial value of a
    *b = temp;
}

void openInputFiles(char* argv, FILE* inPut[])
{
    char* name;
    int numFile;
    // set number of files according to the user input average or median
    if ( strcmp(argv, "average") == 0)
    {
        numFile = AVERAGE;
    }
    else
    {
        numFile = MEDIAN;
    }
    // allocate memory for name
    name = (char*)malloc(numFile*sizeof(char));
    //create names file input files and of pen these files in read mode
    for (int i = 0; i < numFile; ++i)
    {
        sprintf(name,"%s_%03d.ppm",argv, i + 1);
        inPut[i] = fopen(name, "r");
        // check if files open successfuly
        if (inPut[i] == NULL)
        {
            printf("file did not open successfully\n");
            exit(-1);
        }
    }
}

image_t* removeNoiseAverage(image_t* img[])
{
    // set value to row and collumn of image.
    int row = img[1]->header.HEIGHT;
    int col = img[1]->header.WIDTH;
    // use this variable to store data of the final image.
    image_t* pic = (image_t*)malloc(row*sizeof(image_t));
    for (int h = 0; h < row  ; ++h)
    {
        pic[h].pixels = (pixel_t*)malloc(col*sizeof(pixel_t));
    }
    // store header to pic
    pic->header.HEIGHT =img[1]->header.HEIGHT;
    pic->header.WIDTH=img[1]->header.WIDTH;
    pic->header.MAX_COLOR =img[1]->header.MAX_COLOR;
    strcpy(pic->header.MAGIC_NUMBER ,img[1]->header.MAGIC_NUMBER);
    //allocate memory for each element of pic
    // caculte average value of RGB in each pixel of 10 images and store to pic
    for( int i = 0; i < AVERAGE; ++i)
    {
        for (int j = 0; j < row  ; ++j)
        {
            for (int k = 0; k < col ; ++k )
            {
                // finals value of each pixel equap sum of 1/10 value of each pixel of each input image
                pic[j].pixels[k].R += img[i][j].pixels[k].R/(10);
                pic[j].pixels[k].G += img[i][j].pixels[k].G/(10);
                pic[j].pixels[k].B += img[i][j].pixels[k].B/(10);
            }
                 
        }
    }
    return pic;
}

image_t* read_ppm(FILE* image_file)
{
    // set value to header
    header_t header = read_header(image_file);
    //use this to store header and pixel and return it
    image_t* image = NULL;
    // call function to store pixels to image
    image = read_p6(image_file, header);

    return image;
}

header_t read_header(FILE* image_file)
{
    header_t data;
    //read magic number to data
    fscanf(image_file, "%s\n",data.MAGIC_NUMBER);
    // read width height and max color to data
    fscanf(image_file, "%u %u %u\n", &data.WIDTH, &data.HEIGHT, &data.MAX_COLOR);
    return data;
}

image_t* read_p6(FILE* image_file, header_t header)
{
    // use this to store pixels
    image_t* data = (image_t*)malloc((header.HEIGHT*header.WIDTH)*sizeof(image_t));
    // allocate memory for data
    for (int row = 0; row < header.HEIGHT; ++ row)
    {
        data[row].pixels = (pixel_t*)malloc(header.WIDTH*sizeof(pixel_t));
    }
    // assign header values to data
    data->header = header;
    // assign pixels values to data
    for (int i = 0; i <header.HEIGHT; ++i)
    {
        for (int j = 0; j < header.WIDTH; ++j)
        {
            fscanf(image_file,"%c%c%c",&data[i].pixels[j].R,&data[i].pixels[j].G,&data[i].pixels[j].B);
        }
    }
    return data;
}


void write_p6(FILE* out_file, image_t* image)
{
    // call fucntion to write header to out_file
    write_header( out_file, image->header);
    // use for loop to write pixel values to out_file
    for (int i = 0; i < image->header.HEIGHT; ++i)
    {
        for(int j = 0 ; j < image->header.WIDTH; ++j )
        {
            fprintf(out_file,"%c%c%c",image[i].pixels[j].R,image[i].pixels[j].G,image[i].pixels[j].B);
        }
    }
}

void write_header(FILE* out_file, header_t header)
{
    //write header values to out_file
    fprintf(out_file,"%s\n", header.MAGIC_NUMBER);
    fprintf(out_file,"%u %u %u\n", header.WIDTH, header.HEIGHT, header.MAX_COLOR);
}

