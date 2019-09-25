/*
 * CS4481B Assignment 3
 * Name: Jameel Kaba
 * UWO/GAUL ID: jkaba
 * student #: 250796017
 */

// Include header file
#include "lz77_encoding_function.h"

// Main function which calls the encoding function
int main(int argc, char *argv[]){
    
    // Check to ensure there are 3 arguments
    if(argc != 3){
        
        // If there are not 3 arguments, print error message and exit
        printf("Error: Program accepts 2 arguments\n");
        printf("1: input pgm image name\n");
        printf("2: searching buffer size\n");
        return 0;
    }
    
    // Initialize variables to be passed into encoding function
    unsigned int searching_buffer_size = atoi(argv[2]);
    float avg_offset_Ptr = 0;
    float std_offset_Ptr = 0;
    float avg_length_Ptr = 0;
    float std_length_Ptr = 0;
    
    // Get the time before running the program
    clock_t start = clock();
    
    // Encoding function to encode/compress the image
    Encode_Using_LZ77(argv[1], searching_buffer_size, &avg_offset_Ptr, &std_offset_Ptr, &avg_length_Ptr, &std_length_Ptr);
    
    // Get the time when program ended
    clock_t end = clock();
    
    // Get the difference in time, and convert it to seconds
    double diff = (double) (end - start) / CLOCKS_PER_SEC;
    
    // Print out average and standard deviation for offset and length
    printf("Average Offset: %f \n", avg_offset_Ptr);
    printf("Standard Deviation of Offset: %f \n", std_offset_Ptr);
    printf("Average Match Length: %f \n", avg_length_Ptr);
    printf("Standard Deviation of Match Length: %f \n", std_length_Ptr);
    
    // Print out the compression time
    printf("Compression Time: %f seconds\n", diff);

    // End program by returning 0
    return 0;
}
