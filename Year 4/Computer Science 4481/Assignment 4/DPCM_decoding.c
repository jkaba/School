/*
 * CS4481B Assignment 4
 * Name: Jameel Kaba
 * UWO/GAUL ID: jkaba
 * student #: 250796017
 */

// Include the header file
#include "DPCM_decoding_function.h"

// Main function which calls the decoding function
int main(int argc, char *argv[]){
    
    // Check to ensure that there is only 1 argument passed
    if(argc != 2){
        
        // More or Less than 1 argument, print an error and exit
        printf("Error: This program takes in 1 argument as input\n");
        printf("1: The compressed image filename\n");
        return 0;
    }
    
    // Clock starts before running the decompression
    clock_t start = clock();
    
    // Decompressing / Decoding the compressed image
    Decode_Using_DPCM(argv[1]);
    
    // End time taken after decompression
    clock_t end = clock();
    
    // Find the difference between times, and convert to seconds
    double diff = (double) (end - start) / CLOCKS_PER_SEC;
    
    // Print out the decompression time
    printf("Decompression Time: %f seconds\n", diff);
    
    // End program by returning 0
    return 0;
}
