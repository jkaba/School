/* CS4481B Assignment 1
 Name: Jameel Kaba
 UWO/GAUL ID: jkaba
 Student #: 250796017
 */

// Include header files
#include <stdlib.h>
#include <string.h>
#include "libpnm.h"

// Structures for each image type
struct PBM_Image pbmImage;	
struct PGM_Image pgmImage;
struct PPM_Image ppmImage;

// Constants, lots of constants

// image dimensions
int width;
int height;

// Is the image raw or ascii, used for saving
bool raw = false;

char filename[1024];
int x;
int y;
int color;

// colorType, used for representing color
char *colorType[] = {"R","G", "B"};

// max color value
float c = 255.0;

// calculated slope value
float slope;

// shade/intensity of color (used for changing color)
float shade;

/* PROGRAM 1: PBM IMAGE */
int CreatePBM(){
    
    // Nested loops to set the whole image to black
    for(x = 0; x < width; x++){
        for(y = 0; y < height; y++){
            pbmImage.image[y][x] = 1;
        }
    }
    
    // Second set of nested loops to create a white square in the middle
    for(x = width/4; x < (width*3/4); x++){
        for(y = height/4; y < (height*3/4); y++){
            pbmImage.image[y][x] = 0;
        }
    }
    
    // Calculate the slope
    slope = (float)((height*(3/4)) - (height/4)) / (float)((width*(3/4)) - (width/4));
    
    // If the slope is larger than 1, then we loop over the x values (width)
    if(slope <= 1.0){
        for(x = width/4; x <= (width*3/4); x++){
            
            // Calculate y
            y = slope * x;
            
            // -1 is included in the calculations/pixel placement to fix rounding error so that pixels go to the end rather than stop 1 short
            
            // Black line which goes from Bottom Right to Top Left
            pbmImage.image[height-y-1][width-x-1] = 1;

            // Black line which goes from Bottom Left to Top Right
            pbmImage.image[height-y-1][x] = 1;
        }
    }
    
    // Slope is smaller than 1, so we need to loop over y values (height)
    else{
        for(y = height/4; y <= (height*3/4); y++){
            
            // Calculate x
            x = y / slope;
            
            // -1 is included in the calculations/pixel placement to fix rounding error so that pixels go to the end rather than stop 1 short

            // Black line which goes from Bottom Right to Top Left
            pbmImage.image[height-y-1][width-x-1] = 1;
            
            // Black line which goes from Bottom Left to Top Right
            pbmImage.image[height-y-1][x] = 1;
        }
    }
    
    // Return 0, go back to caller
    return 0;
}

/* PROGRAM 2: PGM IMAGE */
int CreatePGM(){
    
    // loop counter
    int i;
    
    // Nested loops to set the whole image to black
    for(x = 0; x < width; x++){
        for(y = 0; y < height; y++){
            pgmImage.image[y][x] = 0;
        }
    }
    
    // Second set of nested loops to set the middle to white
    for(x = width/4; x < (width*(3/4)); x++){
        for(y = height/4; y < (height*(3/4)); y++){
            pgmImage.image[y][x] = 255;
        }
    }
    
    // Calculate slope
    slope = (float)((height*(3/4)) - (height/4)) / (float)((width*(3/4)) - (width/4));
    
    // If the slope is larger than 1
    if(slope <= 1.0){
        
        // Set the color intensity / next shade
        shade = (255.0 / width) * 4.0;
        
        // Loop from corner to the center
        for(x = width/4; x <= (width/2); x++){
            
            // Calculate y
            y = slope * x;
            
            // Loop over x, to set the values for the top and bottom of the inside
            for(i = x; i < width - x; i++){
                
                //Set the color for the top and bottom to be the same
                pgmImage.image[y][i] = (unsigned char)c;
                
                // -1 is included in the calculation to handle rounding error
                pgmImage.image[height-y-1][i] = (unsigned char)c;
            }
            
            // Loop over y, to set the values for the left and right of the inside
            for(i = y; i < height - y; i++){
                
                // Set the color for the left and right to be the same
                pgmImage.image[i][x] = (unsigned char)c;
                pgmImage.image[i][width-x] = (unsigned char)c;
            }
            
            // Adjust the color so that it gets closer to black
            c -= shade;
        }
    }
    
    // Slope is less than 1
    else{
        
        // Set the color intensity / next shade
        shade = (255.0 / height) * 4.0;
        
        //Loop from the top, to center
        for(y = height/4; y <= (height/2); y++){
            
            // Calculate x
            x = y / slope;
            
            // Loop over x values to set the values for the top and bottom of the inside
            for(i = x; i < width - x; i++){
                pgmImage.image[y][i] = (unsigned char)c;
                pgmImage.image[height-y][i] = (unsigned char)c;
            }
            
            // Loop over y values to set the values for the left and right of the inside
            for(i = y; i < height - y; i++){
                pgmImage.image[i][x] = (unsigned char)c;
                
                // -1 included in calculation to handle the rounding error
                pgmImage.image[i][width-x-1] = (unsigned char)c;
            }
            
            // Adjust the color so that it gets closer to black
            c -= shade;
        }
    }
    
    // Return 0, go back to caller
    return 0;
}

/* PROGRAM 3: PPM IMAGE */
int CreatePPM(){
    
    // Nested loops to set the image to white
    for(x = 0; x < width; x++){
        for(y = 0; y < height; y++){
            for(color = RED; color <= BLUE; color++){
                ppmImage.image[y][x][color] = 255;
            }
        }
    }
    
    // Set the intensity / next shade
    shade = 255.0 / (height / 2);
    
    // Set color value to 0
    c = 0.0;
    
    // Going from the top to the center
    for(y = 0; y < height/2; y++){
        
        // Inside loops, setting RGB values so that they eventually are equal (white)
        
        // Red loop / first third (red goes from red to white)
        for(x = 0; x < width/3; x++){
            
            // Set Green and Blue value to current color value
            ppmImage.image[y][x][GREEN] = (unsigned char)c;
            ppmImage.image[y][x][BLUE] = (unsigned char)c;
        }
        
        // Green loop / second third (green goes from white to green)
        for(x = width/3; x < width/3 * 2; x++){
            
            // Set Red and Blue to be 255 - current color value since reverse fade
            ppmImage.image[y][x][RED] = (unsigned char)(255 - c);
            ppmImage.image[y][x][BLUE] = (unsigned char)(255 - c);
        }
        
        // Blue loop / last third (blue goes from blue to white)
        for(x = width/3 * 2; x < width; x++){
            
            // Set Red and Green to be current color value
            ppmImage.image[y][x][RED] = (unsigned char)c;
            ppmImage.image[y][x][GREEN] = (unsigned char)c;
        }
        
        // Increase the color so it becomes closer to white
        c += shade;
    }
    
    // Reset color to black
    c = 0.0;
    
    // Going from the center, down to the bottom
    for(y = height/2; y < height; y++){
        
        // Black loop / first half (black to white)
        for(x = 0; x < width/2; x++){
            
            // Set Red, Green, and Blue to all be current color
            ppmImage.image[y][x][RED] = (unsigned char)c;
            ppmImage.image[y][x][GREEN] = (unsigned char)c;
            ppmImage.image[y][x][BLUE] = (unsigned char)c;
        }
        
        // White loop / second half (white to black)
        for(x = width/2; x < width; x++){
            
            // Reverse color (-255) applied to Red, Green, and Blue
            ppmImage.image[y][x][RED] = (unsigned char)(255 - c);
            ppmImage.image[y][x][GREEN] = (unsigned char)(255 - c);
            ppmImage.image[y][x][BLUE] = (unsigned char)(255 - c);
        }
        
        // Increase the color so it becomes closer to white
        c += shade;
    }
    
    // Return 0, go back to caller
    return 0;
}

/* MAIN METHOD
 
    This method performs the initial setup before going to the functions
    This method also converts PPM Images to PGM Images
 */
int main(int argc, char** argv){
    
    // Boolean values used to determine which image to make
    bool pbm = false;
    bool pgm = false;
    bool ppm = false;
    char extension[1024];
    
    // If there are not enough arguments then return an error message
    if(argc != 6){
        
        // Message to let the user know what arguments are needed
        printf("Error: This program requires five arguments\n");
        printf("1: Image type (1 for pbm, 2 for pgm, 3 for ppm)\n");
        printf("2: Width of image. (pbm and pgm must be a multiple of 4, ppm a multiple of 6)\n");
        printf("3: Height of image. (must be a multiple of 4)\n");
        printf("4: Output image name\n");
        printf("5: Image format code (0 for ASCII, 1 for Raw)\n");
        
        // Stop the program as there was an error
        return 0;
    }
    
    // Switch case to determine what image to make
    switch (argv[1][0]) {
            
        // If it is 1, we are making a PBM
        case '1':
            pbm = true;
            break;
            
        // If it is 2, we are making a PGM
        case '2':
            pgm = true;
            break;
            
        // If it is 3, we are making a PPM
        case '3':
            ppm = true;
            break;
            
        // If the number is something else, return an error message and stop the program
        default:
            printf("Error: Image type should be either 1(pbm), 2(pgm), or 3(ppm)\n");
            return 0;
    }
    
    // The width is given as the second argument
    width = atoi(argv[2]);
    
    // The height is given as the third argument
    height = atoi(argv[3]);
    
    // The filename is given as the fourth argument
    strcpy(filename, argv[4]);
    
    // Switch case for fifth argument to determine whether the image is ascii or raw
    switch (argv[5][0]) {
            
        // If it is 0, then the image will be saved as an ascii image
        case '0':
            raw = false;
            break;
            
        // If it is 1, then the image will be saved as a raw image
        case '1':
            raw = true;
            break;
            
        // If it is something else, then return an error message and stop the program
        default:
            printf("Error: Image format code should be either 0 (ASCII) or 1(raw)\n");
            return 0;
    }
    
    // If pbm is true, we are making a pbm image
    if(pbm == true){
        
        // Print statement to let user know what image is being made
        printf("PBM image\n");
        
        // Width check to ensure that width is proper
        if(width < 4 || width % 4 != 0){
            
            // If the check fails, then return an error message and stop the program
            printf("Error: Width for pbm must be a multiple of 4\n");
            return 0;
        }
        
        // Height check to ensure that height is proper
        if(height < 4 || height % 4 != 0){
            
            // If the check fails, then return an error message and stop the program
            printf("Error: Height for pbm must be a multiple of 4\n");
            return 0;
        }
        
        // Try to create enough memory for the image
        if(create_PBM_Image(&pbmImage, width, height) != 0){
            
            // If memory couldn't be allocated return an error message and stop the program
            printf("Error: Memory problem creating the PBM Image\n");
            return 0;
        }
        
        // Print statement to let user know image dimensions
        printf("Creating PBM image %d W x %d H\n", width, height);
        
        // Create PBM Image function (Refer to program 1)
        CreatePBM();
        
        // Add .pbm file extension to the filename
        strcat(filename, ".pbm");
        
        // Try to save the image
        if(save_PBM_Image(&pbmImage, filename, raw) != 0){
            
            // If the image couldn't be saved return an error message and stop the program
            printf("An Error occured while trying to save the PBM image to the requested filename\n");
            return 0;
        }
        
        // If the user wanted to save the image as raw
        if(raw == true){
            
            // Print message letting the user know what the raw image is saved as
            printf("PBM Raw image saved as: %s\n", filename);
        }
        else{
            // Print message letting the user know what the ascii image is saved as
            printf("PBM ASCII image saved as: %s\n", filename);
        }
        
        // Free memory
        free_PBM_Image(&pbmImage);
    }
    
    // If pgm is true, we are making a PGM image
    else if(pgm == true){
        
        // Print statement to let the user know what image is being made
        printf("PGM Image\n");
        
        // Width check, to ensure that the width is proper
        if(width < 4 || width % 4 != 0){
            
            // If the width check failed, return an error message and stop the program
            printf("Error: Width for pgm image must be a multiple of 4\n");
            return 0;
        }
        
        // Height check, to ensure that the height is proper
        if(height < 4 || height % 4 != 0){
            
            // If the height check failed, return an error message and stop the program
            printf("Error: Height for pgm image must be a multiple of 4\n");
            return 0;
        }
        
        // Try to create enough memory for the image
        if(create_PGM_Image(&pgmImage, width, height, 255) != 0){
            
            // If memory could not be allocated, return an error message and stop the program
            printf("Error: Memory problem creating the PGM Image\n");
            return 0;
        }
        
        // Print out the dimensions of the image
        printf("Creating PGM image %d W x %d H\n", width, height);
        
        // Create PGM Function (Refer to program 2)
        CreatePGM();
        
        // Add .pgm file extension to the file name
        strcat(filename, ".pgm");
        
        // Try to save the PGM Image
        if(save_PGM_Image(&pgmImage, filename, raw) != 0){
            
            // If the image could not be saved, return an error message and stop the program
            printf("An Error occured while trying to save the PGM image to the requested filename\n");
            return 0;
        }
        
        // If the user wanted to save the image as raw
        if(raw == true){
            
            // Print message letting the user know what the raw image is saved as
            printf("PGM Raw image saved as: %s\n", filename);
        }
        else{
            // Print message letting the user know what the ascii image is saved as
            printf("PGM ASCII image saved as: %s\n", filename);
        }
        // Free memory
        free_PGM_Image(&pgmImage);
    }
    
    // If ppm is true, we are making a PPM Image
    else if(ppm == true){
        
        // Print statement to let the user know what image is being made
        printf("PPM Image\n");
        
        // Width check to ensure width is proper (note: ppm needs a multiple of 6)
        if(width < 6 || width % 6 != 0){
            
            // If width check fails, return an error message and stop the program
            printf("Error: Width for ppm image must be a multiple of 6\n");
            return 0;
        }
        
        // Height check to ensure height is proper
        if(height < 4 || height % 4 != 0){
            
            // If height check fails, return an error message and stop the program
            printf("Error: Height for ppm image must be a multiple of 4\n");
            return 0;
        }
        
        // Try to allocate memory for PPM Image
        if(create_PPM_Image(&ppmImage, width, height, 255) != 0){
            
            // If memory could not be allocated, return an error message and stop the program
            printf("Error: Memory problem creating the PPM Image\n");
            return 0;
        }
        
        // Print out dimensions for the image
        printf("Creating PPM image %d W x %d H\n", width, height);
        
        // Create PPM Function (Refer to program 3)
        CreatePPM();
        
        // Add .ppm file extension to the file name
        strcat(filename, ".ppm");
        
        // Try to save the PPM Image
        if(save_PPM_Image(&ppmImage, filename, raw) != 0){
            
            // If the image could not be saved, then return an error message and stop the program
            printf("An Error occured while trying to save the PPM image to the requested filename\n");
            return 0;
        }
        
        // If the user wanted to save the image as raw
        if(raw == true){
            
            // Print message letting the user know what the raw image is saved as
            printf("PPM Raw image saved as: %s\n", filename);
        }
        else{
            // Print message letting the user know what the ascii image is saved as
            printf("PPM ASCII image saved as: %s\n", filename);
        }
        
        // convert and store PPM into 3 PGM through copy_PPM_to_PGM
        printf("Copying PPM Image to PGM Format\n");
        
        // Allocate memory for the pgm conversion of the ppm image
        if(create_PGM_Image(&pgmImage, width, height, 255) != 0){
            
            // If memory could not be allocated, then return an error message and stop the program
            printf("Error: Memory problem creating the PGM Image Copy\n");
            return 0;
        }
        
        // Print out PGM copy dimensions
        printf("Creating PGM image copy %d W x %d H\n", width, height);
        
        // Converting ppm into 3 pgm, converting one color at a time
        for(color = RED; color <= BLUE; color++){
            
            // Copy PPM to PGM with current color from the loop
            if(copy_PPM_to_PGM(&ppmImage, &pgmImage, color) != 0){
                
                // If there was an error converting, return an error message and stop the program
                printf("Error: converting from PPM to PGM\n");
                return 0;
            }
            
            // Filename setup for the copies
            strcpy(filename, argv[4]);
            strcat(filename, ".ppm.");
            strcat(filename, colorType[color]);
            strcat(filename, ".copy2PGM");
            strcat(filename, ".pgm");
            
            // Try to save the converted pgm image
            if(save_PGM_Image(&pgmImage, filename, raw) != 0){
                
                // If the PGM cannot be saved, return an error message and stop the program
                printf("An Error occured while trying to save the converted PGM image to the requested filename\n");
                return 0;
            }
            
            // If the user wanted to save the image as raw
            if(raw == true){
                
                // Print message letting the user know what the raw image is saved as
                printf("PGM Raw image saved as: %s\n", filename);
            }
            else{
                // Print message letting the user know what the ascii image is saved as
                printf("PGM ASCII image saved as: %s\n", filename);
            }
        }
        // Free memory used for the converted image
        free_PGM_Image(&pgmImage);
        
        // Free memory used for the PPM image
        free_PPM_Image(&ppmImage);
    }
    
    // Program reached end successfully, return 0
    return 0;
}
