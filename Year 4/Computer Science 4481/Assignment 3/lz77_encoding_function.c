/*
 * CS4481B Assignment 3
 * Name: Jameel Kaba
 * UWO/GAUL ID: jkaba
 * student #: 250796017
 */

// Include header file
#include "lz77_encoding_function.h"

// Encoding function to encode an image passed in as parameter
void Encode_Using_LZ77(char *in_PGM_filename_Ptr, unsigned int searching_buffer_size, float *avg_offset_Ptr, float *std_offset_Ptr, float *avg_length_Ptr, float *std_length_Ptr){
    
    // Get the image to be encoded
    struct PGM_Image pgmPic;
    load_PGM_Image(&pgmPic, in_PGM_filename_Ptr);
    
    // Determine how long of an array will be needed
    long int imageLength = pgmPic.width*pgmPic.height;
    
    // Copy the image to an array to handle easier
    
    // Allocate memory for the array
    unsigned char *image = malloc(sizeof(unsigned char)*imageLength);
    
    // Counter used for positioning in the array
    long int counter = 0;
    
    // Copy image pixels to the image array
    for(int i = 0; i < pgmPic.height; i++){
        for(int j = 0; j < pgmPic.width; j++){
            image[counter++] = pgmPic.image[i][j];
        }
    }
    
    // Reset counter to 0
    counter = 0;
    
    // Assign the image array to a pointer
    unsigned char *imagePointer = &image[0];
    
    // Initializing more variables to be used
    int current_length = 0;
    long int arrayLength = 0;
    
    // Array's used to represent the 3 parts of a token
    int offset_array[imageLength];
    int length_array[imageLength];
    unsigned char next_symbol_array[imageLength];
    
    // int values to be used to for saving values into the array
    int offset_val = 0;
    int length_val = 0;
    unsigned char next_symbol_val = 0;
    
    // int token, used for calling a method
    int token = 0;
    
    // While loop used for encoding the image
    while(counter < imageLength){
        
        // Generate token info, to be saved
        token = Tokenizer(&current_length, searching_buffer_size, imagePointer+counter, imageLength, counter, &offset_val, &length_val, &next_symbol_val);
        
        // Save the offset, match length, and next mismatched symbol
        offset_array[arrayLength] = offset_val;
        length_array[arrayLength] = length_val;
        next_symbol_array[arrayLength] = next_symbol_val;
        
        // Update the counter
        counter += length_array[arrayLength]+1;
        
        // Increment the array length
        arrayLength++;
    }
    
    // Initialize the filenames for compressed image and .csv files
    FILE * f;
    FILE * f1;
    FILE * f2;
    
    // Initialize the filenames to null
    char compressed_filename_Ptr[1024] = "\0";
    char offset_csv[1024] = "\0";
    char length_csv[1024] = "\0";
    
    // Concatenate the input image filename to the 3 filenames
    strcat(compressed_filename_Ptr, in_PGM_filename_Ptr);
    strcat(offset_csv, in_PGM_filename_Ptr);
    strcat(length_csv, in_PGM_filename_Ptr);
    
    // Based on the buffer size, append the according ending to the filename
    
    // Buffer size of 5120
    if(searching_buffer_size == 5120){
        strcat(compressed_filename_Ptr, ".5120.lz");
        strcat(offset_csv, ".5120.offsets.csv");
        strcat(length_csv, ".5120.lengths.csv");
    }
    
    // Buffer size of 1024
    else if(searching_buffer_size == 1024){
        strcat(compressed_filename_Ptr, ".1024.lz");
        strcat(offset_csv, ".1024.offsets.csv");
        strcat(length_csv, ".1024.lengths.csv");
    }
    
    // Buffer size of 256
    else if(searching_buffer_size == 256){
        strcat(compressed_filename_Ptr, ".256.lz");
        strcat(offset_csv, ".256.offsets.csv");
        strcat(length_csv, ".256.lengths.csv");
    }
    
    // Buffer size of something else, append generic endings
    else{
        strcat(compressed_filename_Ptr, ".lz");
        strcat(offset_csv, ".offsets.csv");
        strcat(length_csv, ".lengths.csv");
    }
    
    // Check that the files can be opened, if not then there is an error
    if (!(f = fopen(compressed_filename_Ptr, "w"))){
        
        // Print an error message and exit
        printf("Error: The compressed file could not be opened\n");
        exit(0);
    }
    if (!(f1 = fopen(offset_csv, "w"))){
        
        // Print an error message and exit
        printf("Error: The offset.csv file could not be opened\n");
        exit(0);
    }
    if (!(f2 = fopen(length_csv, "w"))){
        
        // Print an error message and exit
        printf("Error: The length.csv file could not be opened\n");
        exit(0);
    }
    
    // Save the header information into the compressed image
    fprintf(f, "%d\n", pgmPic.height);
    fprintf(f, "%d\n", pgmPic.width);
    fprintf(f, "%d\n", pgmPic.maxGrayValue);
    fprintf(f, "%ld\n", arrayLength);
    
    // Save the offset values
    for (int i = 0; i < arrayLength; i++){
        fprintf(f, "%d ", offset_array[i]);
    }
    
    // Save a new line
    fprintf(f, "\n");
    
    // Save the match length values
    for (int i = 0; i < arrayLength; i++){
        fprintf(f, "%d ", length_array[i]);
    }
    
    // Save a new line
    fprintf(f, "\n");
    
    // Save the next mismatched symbol
    for (int i = 0; i < arrayLength; i++){
        fprintf(f, "%d ", next_symbol_array[i]);
    }
    
    // Close the compressed file
    fclose(f);
    
    // Calculating average and standard deviation
    
    // Initialize variables
    float avg = 0;
    float std = 0;
    
    // Calculate offset average
    for (int i = 0; i < arrayLength; i++){
        avg += offset_array[i];
    }
    avg /= arrayLength;
    
    // Calculate offset standard deviation
    for(int i = 0; i < arrayLength; i++){
        std += pow(offset_array[i] - avg, 2);
    }
    *avg_offset_Ptr = avg;
    *std_offset_Ptr = sqrt(std/arrayLength);
    
    // Reset variables to calculate for match length
    avg = 0;
    std = 0;
    
    // Calculate average match length
    for (int i = 0; i < arrayLength; i++){
        avg += length_array[i];
    }
    avg /= arrayLength;
    
    // Calculate match length standard deviation
    for(int i = 0; i < arrayLength; i++){
        std += pow(length_array[i] - avg, 2);
    }
    *avg_length_Ptr = avg;
    *std_length_Ptr = sqrt(std/arrayLength);
    
    // Initialize variables for sorting the arrays
    int temp;
    int temp2;
    int count = 0;
    
    // THE REMAINDER OF THIS PROGRAM IS WHAT SLOWS IT DOWN
    
    // Sort the offset and match length arrays
    for (int i = 0; i < arrayLength; i++) {
        for(int j = 0; j < arrayLength; j++){
            
            // Check if the later value is larger
            if(offset_array[j] > offset_array[i]){
                
                // If so then swap them
                temp = offset_array[i];
                offset_array[i] = offset_array[j];
                offset_array[j] = temp;
            }
            
            // Check if later value is larger
            if(length_array[j] > length_array[i]){
                
                // If so swap them
                temp = length_array[i];
                length_array[i] = length_array[j];
                length_array[j] = temp;
            }
        }
    }
    
    // Reset variables for saving into .csv
    temp = offset_array[0];
    temp2 = length_array[0];
    count = 0;
    int count2 = 0;
    
    // Write the data names into the .csv files
    fprintf(f1, "Offset Value, Frequency\n");
    fprintf(f2, "Length Value, Frequency\n");
    
    // Loop to write data into .csv files
    for(int j = 0; j < arrayLength; j++){
        
        // If temp is same as the value in array then increase frequency
        if(temp == offset_array[j]){
            count++;
        }
        
        // Otherwise, there is a new value
        else{
            
            // Save the previous value and it's frequency into the .csv
            fprintf(f1, "%d, %d\n", offset_array[j-1], count);
            
            // Set temp to be current value and frequency of 1
            temp = offset_array[j];
            count = 1;
        }
        
        // If temp2 is same as the value in array then increase frequency
        if(temp2 == length_array[j]){
            count2++;
        }
        
        // Otherwise, there is a new value
        else{
            
            // Save the previous value and it's frequency
            fprintf(f2, "%d, %d\n", length_array[j-1], count2);
            
            // Set temp2 to be current value and frequency to 1
            temp2 = length_array[j];
            count2 = 1;
        }
    }
    
    // Close the .csv values and finish
    fclose(f1);
    fclose(f2);
    
}

// Tokenizer method used to generate the three parts of a token
int Tokenizer (int *current_length, int max_length,unsigned char *imagePointer,long int imageLength,long int counter, int *offset_val, int *length_val, unsigned char *next_symbol_val){
    
    // Initialize variables
    int current_clone = *current_length;
    int location_of_match = 0;
    int length_of_match = 0;
    int current_location_match = 0;
    int current_length_match = 0;
    int flag = 0;
    int forwardOffset = 0;
    
    // While the current length is larger than 0
    while(current_clone>0){
        
        // If we have a match
        if((*(imagePointer + forwardOffset) == *(imagePointer - current_clone)) && !(counter + forwardOffset > imageLength)){
            
            // If this is part of the current match
            if(!flag){
                
                // Set the flag, set current match location to current length
                flag = 1;
                current_location_match = current_clone;
            }
            
            // Increment current match length, and forward offset
            current_length_match++;
            forwardOffset++;
        }
        
        // We did not have a match
        else{
            
            // If we had a match before, then reset
            if(flag){
                // Is the match now the new longest match
                if(current_location_match - current_clone >= length_of_match){
                    
                    // Set the location and length of the match
                    location_of_match = current_location_match;
                    length_of_match = current_length_match;
                }
                
                // Reset variables
                current_location_match = 0;
                current_length_match = 0;
                forwardOffset = 0;
                flag = 0;
            }
        }
        
        // Decrement the current length
        current_clone--;
        
    }
    
    // Save the parts of the token
    *offset_val = location_of_match;
    *length_val = length_of_match;
    *next_symbol_val = *(imagePointer + length_of_match);
    
    // If the current length, is smaller than max length
    if(*current_length < max_length){
        
        // Update the current length
        *current_length += *length_val+1;
    }
    
    // Return to program which called
    return 0;
}
