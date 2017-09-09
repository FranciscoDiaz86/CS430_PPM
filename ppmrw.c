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
void P3_converstion (FILE *input, FILE *output){
 
}

int main (int argc, char *argv[]){
  //Error handling for the right amout of arguments
  if (argc != 4){
    printf("Usage: The program needs: PPM file number, input file, output file.\n");
    return 1;
  }

  //Checking to see if the files are .ppm files
  char *infile_extension, *outfile_extension;
  
  infile_extension = strstr(argv[2], ".ppm");
  outfile_extension = strstr(argv[3], ".ppm");

  if (infile_extension == NULL && outfile_extension == NULL){
    printf ("The file needs to be a .ppm file.\n");
  }

  return 0;
}
