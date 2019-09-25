/*
 * CS4481B Assignment 2
 * Name: Jameel Kaba
 * UWO/GAUL ID: jkaba
 * student #: 250796017
 */

// Include header files
#include "libpnm.h"
#include "read_huffman_encoded_data.h"
#include "huffman_decode_image.h"

// pgm_huffman_decode, this program decodes a compressed image and saves the result
int main(int argc, char *argv[])
{
    
    // If there are too many or not enough images, return an error
    if(argc != 3){
        
        // Message to let the user know what arguments are needed
        printf("Error: This program requires two arguments\n");
        printf("1: File name of compressed file to decode\n");
        printf("2: Output PGM file name\n");
        
        // Stop the program as there was an error
        return 0;
    }
    
    // Initialize variables
    int image_width;
    int image_height;
    int max_gray_value;
    int number_of_nodes;
    struct node *huffman_node;
    long int length_of_encoded_image;
    
    // Read the encoded data
    unsigned char *encoded_image = read_huffman_encoded_data(argv[1], &image_width, &image_height, &max_gray_value, &number_of_nodes, &huffman_node, &length_of_encoded_image);
    
    // Decode the image using a huffman tree
    struct PGM_Image *pic1 = huffman_decode_image(image_width, image_height, max_gray_value, number_of_nodes, huffman_node, length_of_encoded_image,encoded_image);
    
    // Save the decoded image
    save_PGM_Image(pic1, argv[2], true);
    
    // Return 0 to signify the end of program
    return 0;
    
}
