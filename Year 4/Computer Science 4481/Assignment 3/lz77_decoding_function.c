/*
 * CS4481B Assignment 3
 * Name: Jameel Kaba
 * UWO/GAUL ID: jkaba
 * student #: 250796017
 */

// Include header file
#include "lz77_decoding_function.h"

// Decoding function, which decompresses a compressed image passed as input
void Decode_Using_LZ77(char *in_compressed_filename_Ptr){
    
    // Initialize variables for header info
    int width = 0;
    int height = 0;
    int maxGrayValue = 0;
    long int arrayLength;
    
    // Try opening the compressed file
    FILE* file;
    if (!(file = fopen(in_compressed_filename_Ptr, "r"))){
        
        // Error with a file, print error and exit
        printf("Error: There was an error trying to open the file\n");
        exit(0);
    }
    
    // Read the header info from the compressed file
    fscanf(file, "%d", &height);
    fscanf(file, "%d", &width);
    fscanf(file, "%d", &maxGrayValue);
    fscanf(file, "%ld", &arrayLength);
    
    // Initialize a pgm image to be used for making the decompressed image
    struct PGM_Image pgmPic;
    create_PGM_Image(&pgmPic, width, height,maxGrayValue);
    
    // Create the 3 array representing the 3 parts of a token
    int offset_array[arrayLength];
    int length_array[arrayLength];
    unsigned char next_val_array[arrayLength];
    
    // Get all of the offset values
    for (int i = 0; i < arrayLength; i++){
        fscanf(file, "%d", &offset_array[i]);
    }
    
    // Get all of the match length values
    for (int i = 0; i < arrayLength; i++){
        fscanf(file, "%d", &length_array[i]);
    }
    
    // Get all of the next mismatched symbols
    for (int i = 0; i < arrayLength; i++){
        fscanf(file, "%hhu", &next_val_array[i]);
    }
    
    // Obtained all info from the compressed file, so close it
    fclose(file);
    
    // Get the length of the image
    long int imageLength = pgmPic.width*pgmPic.height;
    
    // Allocate memory to convert image into an array
    unsigned char *image = malloc(sizeof(unsigned char)*imageLength);
    
    // DECODING PROCESS
    
    // Initialize pointer's for decoding
    long int readPointer = 0;
    long int writePointer = 0;
    long int startPointer = 0;
    
    for(int i = 0; i < arrayLength; i++){
        
        // Update the pointer to what we're reading
        readPointer = writePointer - offset_array[i];
        
        // Update the starting pointer
        startPointer = writePointer;
        
        for(int j =0;j<length_array[i];j++){
            
            // If the Starting and Read pointers match
            if(startPointer == readPointer){
                // Update read pointer
                readPointer = startPointer - offset_array[i];
            }
            
            // Update the image pointer
            *(image + writePointer) = *(image + readPointer);
            
            // Increment read and write pointers
            writePointer++;
            readPointer++;
        }
        
        // Save the next mismatched value
        *(image+writePointer) = next_val_array[i];
        
        // Increment write pointer
        writePointer++;
    }
    
    // Counter to be used for copying the image pointer to the picture
    long int counter = 0;
    
    for(int i = 0; i < pgmPic.height; i++){
        for(int j = 0; j < pgmPic.width; j++){
            
            // Save the image pointer data to the picture
            pgmPic.image[i][j] = image[counter++];
        }
    }
    
    // Create decompressed picture filename
    char out_PGM_filename_Ptr[1024] = "\0";
    strcat(out_PGM_filename_Ptr, in_compressed_filename_Ptr);
    strcat(out_PGM_filename_Ptr, ".pgm");
    
    // Save the decompressed PGM image
    save_PGM_Image(&pgmPic, out_PGM_filename_Ptr, 1);
}
