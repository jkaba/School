/*
 * CS4481B Assignment 2
 * Name: Jameel Kaba
 * UWO/GAUL ID: jkaba
 * student #: 250796017
 */

// Include header file
#include "huffman_encode_image.h"

// This program encodes an image using generated huffman codes
unsigned char *huffman_encode_image(struct PGM_Image *input_pgm_image, struct node *huffman_node, int number_of_nodes, unsigned long int *length_of_encoded_array){
    
    // Length of array to store huffman codes
    int huffman_code_array_length = number_of_nodes + 1;
    
    // Allocate memory for an array of huffman codes
    struct huffman_code *huffman_code_array = malloc((huffman_code_array_length) * sizeof(struct huffman_code));
    
    // Initialize the array of huffman codes
    for (int i = number_of_nodes; i >= 0; i--){
        huffman_code_array[i].color = -1;
        huffman_code_array[i].length = 0;
        huffman_code_array[i].code = 0x0;
    }
    
    // Generate huffman codes based on the nodes
    for (int j = number_of_nodes - 1; j >= 0; j--){
        generate_huffman_codes(huffman_code_array, huffman_code_array_length, huffman_node[j].first_value, huffman_node[j].second_value);
    }
    
    // Encode the picture
    struct bitstream stream;
    
    // Create the data stream and allocate memory
    stream.data = malloc((input_pgm_image->height * input_pgm_image->width) * sizeof(unsigned char));
    
    // Size of data to be encoded
    stream.data_size = (input_pgm_image->height * input_pgm_image->width);
    
    // Location of the last bit in the stream
    stream.last_bit = 0L;
    
    // Current position in data
    stream.current_data = 0L;
    
    // The current bit which we read/write
    stream.current_bit = 7;
    
    // Loop through the image
    for (int row = 0; row < input_pgm_image->height; row++){
        for (int col = 0; col < input_pgm_image->width; col++){
            
            // Initialize structure to save code
            struct huffman_code code;
            
            // Find the code for this pixel
            for (int i = 0; i < huffman_code_array_length; i++){
                if (huffman_code_array[i].color == input_pgm_image->image[row][col]){
                    code = huffman_code_array[i];
                }
            }
                        
            // Encode this pixel using the huffman code
            writeData(&stream, &code);
        }
    }
    
    // Set the length of the encoded array
    *length_of_encoded_array = stream.current_data + 1;
    
    // Return the encoded data
    return stream.data;
}

// This function generates huffman codes which are used for encoding
void generate_huffman_codes(struct huffman_code *huffman_code_array, int arrayLen, int first, int second){
    
    // Index values to represent location of code values in array
    int index1 = -1;
    int index2 = -1;
    
    // Find the location of the code for first and second values of huffman node
    for(int i = 0; i < arrayLen; i++){
        if(huffman_code_array[i].color == first){
            index1 = i;
        }
        if(huffman_code_array[i].color == second){
            index2 = i;
        }
    }
    
    // If either index is still -1, search for the location where color is -1
    if(index1 == -1 || index2 == -1){
        for(int j = 0; j < arrayLen; j++){
            
            // If index1 is -1
            if(index1 == -1){
                
                // If the color is -1, then update this color
                if(huffman_code_array[j].color == -1){
                    index1 = j;
                    huffman_code_array[index1].color = first;
                }
            }
            
            // If index2 is -1
            if(index2 == -1){
                
                // If the color is -1, then update this color
                if(huffman_code_array[j].color == -1){
                    index2 = j;
                    huffman_code_array[index2].color = second;
                }
            }
        }
    }
    
    // If the length of code at index1 is shorter, then put larger code in it's location
    if (huffman_code_array[index1].length < huffman_code_array[index2].length){
        huffman_code_array[index1].code = huffman_code_array[index2].code;
        huffman_code_array[index1].length = huffman_code_array[index2].length;
    }
    
    // Else if length of code at index1 is larger, then put larger code in index2
    else if (huffman_code_array[index1].length > huffman_code_array[index2].length){
        huffman_code_array[index2].code = huffman_code_array[index1].code;
        huffman_code_array[index2].length = huffman_code_array[index1].length;
    }
    
    // Logical Shift Left the codes by 1
    huffman_code_array[index1].code = huffman_code_array[index1].code << 1;
    huffman_code_array[index2].code = huffman_code_array[index2].code << 1;

    // Increment the length of the code at index's
    huffman_code_array[index1].length++;
    
    // bitwise OR the code at second index with all 1's
    huffman_code_array[index2].code |= 1;
    huffman_code_array[index2].length++;
}



// This function writes the data to an array in the bit stream so it can be saved later
void writeData(struct bitstream *stream, struct huffman_code *codeStruct){
    
    // Loop through the huffman codes
    for (int i = codeStruct->length - 1; 0 <= i; i--){
        
        // If we are at 8 bits, then shift to the next set
        if (stream->current_bit < 0){
            stream->current_data++;
            stream->data[stream->current_data] = 0x00;
            stream->current_bit = 7;
        }
        
        // If the code is a 1, then write it into a byte
        if (((codeStruct->code >> i) & 0x01)){
            stream->data[stream->current_data] |= 0x01 << stream->current_bit;
            stream->current_bit--;
            stream->last_bit++;
        }
        
        // Otherwise, leave the code as 0
        else{
            stream->current_bit--;
            stream->last_bit++;
        }
    }
}
