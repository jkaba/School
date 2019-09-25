/*
 * CS4481B Assignment 2
 * Name: Jameel Kaba
 * UWO/GAUL ID: jkaba
 * student #: 250796017
 */

// Include header file
#include "generate_pixel_frequency.h"

// generate_pixel_frequency calculates the number of non-zero values
// in the frequency array and also returns the frequency array
long int *generate_pixel_frequency(struct PGM_Image *input_pgm_image, int *number_of_non_zero_values_in_the_frequency_array){
    
    // Initialize variables
    int size = input_pgm_image->maxGrayValue + 1;
    int row = 0;
    int col = 0;
    int height = input_pgm_image->height;
    int width = input_pgm_image->width;
    
    // Create memory for pixel frequency array
    long int *pixel_frequency = malloc(size * sizeof(long int));
    
    // Initialize pixel-frequency array to be all zero's
    for (int i = 0; i < size; i++){
        pixel_frequency[i] = 0;
    }
    
    // Loop through the image
    for (row = 0; row < height; row++){
        for (col = 0; col < width; col++){
            
            // If the frequency is zero, increase the number of non zero values
            if (pixel_frequency[input_pgm_image->image[row][col]] == 0){
                *number_of_non_zero_values_in_the_frequency_array += 1;
            }
            
            // Increment the value at this position
            pixel_frequency[input_pgm_image->image[row][col]]++;
            
        }
    }
    
    // Return the pixel frequency
    return pixel_frequency;
}
