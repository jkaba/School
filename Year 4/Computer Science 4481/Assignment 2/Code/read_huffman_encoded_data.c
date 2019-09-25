/*
 * CS4481B Assignment 2
 * Name: Jameel Kaba
 * UWO/GAUL ID: jkaba
 * student #: 250796017
 */

// Include header file
#include "read_huffman_encoded_data.h"

// Program reads the encoded huffman data from a compressed file
unsigned char *read_huffman_encoded_data(char *compressed_file_name_ptr, int *image_width, int *image_height, int *max_gray_value, int *number_of_nodes, struct node **huffman_node, long int *length_of_encoded_image){
    
    // Open the compressed file
    FILE *file;
    
    // If the compressed file is null, then return an error
    if ((file = fopen(compressed_file_name_ptr,"r")) == NULL){
        printf("Error: File %s failed to open", compressed_file_name_ptr);
        exit(1);
    }
    
    // Read the image characteristics from the file
    fscanf(file, "%d", image_width);
    fscanf(file, "%d", image_height);
    fscanf(file, "%d", max_gray_value);
    fscanf(file, "%d", number_of_nodes);
    
    // Create a node array to store node info from file
    struct node *nodeArray = malloc(*number_of_nodes * sizeof(struct node));
    
    // Read the node data from the file
    for(int i = 0; i < *number_of_nodes; i++){
        
        // Get and assign the first and second value for each node from the file
        fscanf(file, "%d", &nodeArray[i].first_value);
        fscanf(file, "%d", &nodeArray[i].second_value);
    }
    
    // Save the node array data in the pointer to the node array from input
    *huffman_node = nodeArray;
    
    // Read the length of the encoded image
    fscanf(file, "%ld", length_of_encoded_image);
    
    // Allocate memory for the encoded image
    unsigned char *encoded_image = malloc(*length_of_encoded_image * sizeof(unsigned char));
    
    // Advance the current byte by one as we are on a \n which separates the image from the rest of data
    fseek(file,1,SEEK_CUR);
    
    // Read the encoded image from the file
    fread(encoded_image, 1,*length_of_encoded_image ,file);
    
    // Close the file
    fclose(file);
    
    // Return the encoded image to end the program
    return encoded_image;
}
