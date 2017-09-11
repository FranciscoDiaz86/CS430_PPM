#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//This is a struct to hold pixel information
typedef struct Pixel{
  unsigned char r, g, b;
}Pixel;

//This is a struct to hold image information
typedef struct PPMImage{
  int width, height;
  Pixel *pix_info;
}PPMImage;

//Convert from P3 to P6
void P3_converstion(FILE *input, FILE *output){
 
}

//Convert from P6 to P3
void P6_converstion(FILE *input, FILE *output){
  
}

int main (int argc, char *argv[]){
  //Error handling for the right amout of arguments
  if(argc != 4){
    printf("Usage: The program needs: PPM file number, input file, output file.\n");
    return 1;
  }

  //Checking to see if the files are .ppm files
  char *inputfile_extension, *outputfile_extension;
  
  inputfile_extension = strstr(argv[2], ".ppm");
  outputfile_extension = strstr(argv[3], ".ppm");

  if(inputfile_extension == NULL && outputfile_extension == NULL){
    printf("The file needs to be a .ppm file.\n");
  }

  FILE *input_file = fopen(argv[2], "r");
  FILE *output_file = fopen(argv[3], "w");

  //Calls the correct file converstion function
  if(strcmp(argv[1], "3") != 0){
    printf("Convert to P6");
    P3_converstion(input_file, output_file);
  }

  if(strcmp(argv[1], "6") != 0){
    printf ("Convert to P3");
    P6_converstion(input_file, output_file);
  }

  //Closing the files
  fclose(input_file);
  fclose(output_file);

  return 0;
}
