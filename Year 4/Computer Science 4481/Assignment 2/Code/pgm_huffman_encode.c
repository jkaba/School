/*
 * CS4481B Assignment 2
 * Name: Jameel Kaba
 * UWO/GAUL ID: jkaba
 * student #: 250796017
 */

// Include header files
#include "libpnm.h"
#include "generate_huffman_nodes.h"
#include "generate_pixel_frequency.h"
#include "huffman_encode_image.h"
#include "store_huffman_encoded_data.h"

// pgm_huffman_encode, this program compresses a file from input
int main(int argc, char *argv[]) {
    
    // If there are too many or not enough images, return an error
    if(argc != 3){
        
        // Message to let the user know what arguments are needed
        printf("Error: This program requires two arguments\n");
        printf("1: File name of PGM image to encode\n");
        printf("2: Output compressed file name\n");
        
        // Stop the program as there was an error
        return 0;
    }
    
    // Initialize and load up the image from argument 1
    struct PGM_Image pic1;
    load_PGM_Image(&pic1, argv[1]);
    
    // Initialize variables
    int number_of_non_zero_values;
    unsigned long int encodeArrayLength;
    
    // Generate Pixel Frequency and number of non zero values
    long int *pixel_frequency = generate_pixel_frequency(&pic1, &number_of_non_zero_values);
    
    // Generate huffman nodes
    struct node *nodeArray = generate_huffman_nodes(pixel_frequency, pic1.maxGrayValue, number_of_non_zero_values);
    
    // Encode the image using huffman codes
    unsigned char *encodedPicture = huffman_encode_image(&pic1, nodeArray, number_of_non_zero_values - 1, &encodeArrayLength);
    
    // Save the encoded file
    store_huffman_encoded_data(argv[2], pic1.width, pic1.height, pic1.maxGrayValue, number_of_non_zero_values - 1, nodeArray, encodeArrayLength, encodedPicture);
    
    // Return 0 to signify end
    return 0;
}
