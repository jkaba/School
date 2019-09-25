/*
 * CS4481B Assignment 2
 * Name: Jameel Kaba
 * UWO/GAUL ID: jkaba
 * student #: 250796017
 */

// Include header file
#include "generate_huffman_nodes.h"

// Program generates huffman nodes which contain pairs of pixel values
// Returns an array of huffman nodes
struct node *generate_huffman_nodes(long int *pixel_frequency, int max_gray_value, int number_of_non_zero_values_in_the_frequency_array){
   
    // Create the array of huffman nodes
    struct node *nodeArray = malloc((number_of_non_zero_values_in_the_frequency_array - 1) * sizeof(struct node));
    
    // Initialize variable
    int arraySize = max_gray_value+1;
    
    // We need a loop which goes until we've got every non zero value from the frequency array
    for (int i = 0; i < number_of_non_zero_values_in_the_frequency_array - 1; i++){
        
        // Initialize index values to -1
        int index1 = -1;
        int index2 = -1;
        
        // Check the indexes to ensure that they are the smallest values
        for (int j = 0; j < arraySize; j++){
            
            // If the frequency at j is not 0, and is different from both indexes
            if (pixel_frequency[j] != 0 && j != index1 && j != index2){
                
                // Check if the frequency is the smallest value
                if (pixel_frequency[j] < pixel_frequency[index1] || index1 == -1){
                    
                    // If so, then fix the index values
                    index2 = index1;
                    index1 = j;
                }
                
                // If the frequency at j is the second smallest, update
                else if (pixel_frequency[j] < pixel_frequency[index2] || index2 == -1){
                    index2 = j;
                }
            }
        }
        
        // If index 1 is smaller
        if (index1 < index2){
            
            // Node pair is index1, index2
            nodeArray[i].first_value = index1;
            nodeArray[i].second_value = index2;
            
            // Update pixel frequencies
            pixel_frequency[index1] = pixel_frequency[index1] + pixel_frequency[index2];
            pixel_frequency[index2] = 0;
        }
        
        // If index 2 is smaller
        else{
            
            // Node pair is index2, index1
            nodeArray[i].first_value = index2;
            nodeArray[i].second_value = index1;
            
            // Update pixel frequencies
            pixel_frequency[index2] = pixel_frequency[index1] + pixel_frequency[index2];
            pixel_frequency[index1] = 0;
        }
    }
    
    // Return the array of nodes
    return nodeArray;
}
