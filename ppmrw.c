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
}PPM_Image;

//Convert from P3 to P6
int P3_converstion(FILE *input, FILE *output){

  PPM_Image image;
  char temp_data[255];
  int c;
  
  //Getting the PPM number to see if it is the correct PPM file to convert
  fgets(temp_data, 255, input);

  if(strcmp(temp_data, "P6\n") == 0){
    printf("You need to put in a P3 file for this converstion\n");
    return 1;
  }

  //Writing P6 to the output file
  fprintf(output, "%s\n", "P6");
 
  //Copying all the comments into the output file
  c = fgetc(input);
  while(c == '#'){
    fgets(temp_data, 255, input);
    fprintf(output,"%c" "%s",'#', temp_data);
    c = fgetc(input);
  }
  //Put the pointer one back to get the width and height
  fseek(input, -1, SEEK_CUR);

  //Getting the width and the height
  char width_temp[255], height_temp[255];
    
  fscanf(input, "%s" "%s", width_temp, height_temp);
  fprintf(output, "%s " "%s" , width_temp, height_temp);

  //Getting the space that fscanf does not get
  c = fgetc(input);
  fprintf(output, "%c", c);

  //Adding the width and height to PPM_Image
  image.width = atoi(width_temp);
  image.height = atoi(height_temp);

  //Getting max color value
  fgets(temp_data, 255, input);
  fprintf(output, "%s", temp_data);
  
  //Allocating memory for the image data
  image.pix_info = (Pixel *)malloc(sizeof(Pixel) * image.width * image.height);
  
  //Getting image data
  for(int i = 0; i < image.width * image.height; i++){
    int image_data;
    fscanf(input, "%d", &image_data);
    image.pix_info[i].r = image_data;
    fscanf(input, "%d", &image_data);
    image.pix_info[i].g = image_data;
    fscanf(input, "%d", &image_data);
    image.pix_info[i].b = image_data;
  }

  //Write the data to the out file
  fwrite(image.pix_info, 3 * image.width, image.height, output);
  
  return 0;
}

//Convert from P6 to P3
int P6_converstion(FILE *input, FILE *output){
  PPM_Image image;
  char temp_data[255];
  int c;
  
  //Getting the PPM number to see if it is the correct PPM file to convert
  fgets(temp_data, 255, input);

  if(strcmp(temp_data, "P3\n") == 0){
    printf("You need to put in a P6 file for this converstion\n");
    return 1;
  }

  //Writing P3 to the output file
  fprintf(output, "%s\n", "P3");
 
  //Copying all the comments into the output file
  c = fgetc(input);
  while(c == '#'){
    fgets(temp_data, 255, input);
    fprintf(output,"%c" "%s",'#', temp_data);
    c = fgetc(input);
  }
  //Put the pointer one back to get the width and height
  fseek(input, -1, SEEK_CUR);

  //Getting the width and the height
  char width_temp[255], height_temp[255];
    
  fscanf(input, "%s" "%s", width_temp, height_temp);
  fprintf(output, "%s " "%s" , width_temp, height_temp);

  //Getting the space that fscanf does not get
  c = fgetc(input);
  fprintf(output, "%c", c);

  //Adding the width and height to PPM_Image
  image.width = atoi(width_temp);
  image.height = atoi(height_temp);

  //Getting max color value
  fgets(temp_data, 255, input);
  fprintf(output, "%s", temp_data);

  //Allocating memory for the image data
  image.pix_info = (Pixel *)malloc(sizeof(Pixel) * image.width * image.height);

  //fread reads in the byte stream and put it into image.pix_info
  fread(image.pix_info, sizeof(Pixel), image.width * image.height, input);

  //Writing the image data to output using fprintf to write it as ascii
  for(int i = 0; i < image.width * image.height; i++){
    fprintf(output, " %d %d %d ", image.pix_info[i].r, image.pix_info[i].g, image.pix_info[i].b);
  }
  
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

  //Checking to see if the files opened without a problem
  if(input_file == NULL){
    printf("Error opening the input file\n");
  }

  //Calls the correct file converstion function
  if(strcmp(argv[1], "3") == 0){
    printf("Converting to P6\n");
    P3_converstion(input_file, output_file);
  }

  if(strcmp(argv[1], "6") == 0){
    printf ("Converting to P3\n");
    P6_converstion(input_file, output_file);
  }

  //Closing the files
  fclose(input_file);
  fclose(output_file);

  return 0;
}
