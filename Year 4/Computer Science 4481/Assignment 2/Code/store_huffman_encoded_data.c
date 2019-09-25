/*
 * CS4481B Assignment 2
 * Name: Jameel Kaba
 * UWO/GAUL ID: jkaba
 * student #: 250796017
 */

// Include header files
#include "store_huffman_encoded_data.h"

// store_huffman_encoded_data, this program saves the encoded data
void store_huffman_encoded_data(char *compressed_file_name_ptr, int image_width, int image_height, int max_gray_value, int number_of_nodes, struct node *huffman_node, long int length_of_encoded_image, unsigned char *encoded_image){
    
    // Open the file
    FILE *file;
    
    // If the file is null, it can't be opened and so exit with failure
    if ((file = fopen(compressed_file_name_ptr, "w")) == NULL){
        printf("Error: File %s failed to open\n", compressed_file_name_ptr);
        exit(1);
    }
    
    // Write the characteristics of the image into the file
    fprintf(file, "%d\n", image_width);
    fprintf(file, "%d\n", image_height);
    fprintf(file, "%d\n", max_gray_value);
    fprintf(file, "%d\n", number_of_nodes);
    
    // Save the nodes and the pair values belonging to them
    for (int i = 0; i < number_of_nodes; i++){
        fprintf(file, "%d %d\n", huffman_node[i].first_value, huffman_node[i].second_value);
    }
    
    // Save the length of the encoded image
    fprintf(file, "%ld\n", length_of_encoded_image);
    
    // Save the encoded image
    fwrite(encoded_image, sizeof(unsigned char), length_of_encoded_image, file);
    
    // Close the file to end the program
    fclose(file);
}
