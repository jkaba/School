/*
 * CS4481B Assignment 2
 * Name: Jameel Kaba
 * UWO/GAUL ID: jkaba
 * student #: 250796017
 */

#include "libpnm.h"
#include "generate_huffman_nodes.h"

// structure for the huffman code
struct huffman_code
{
    // symbol is the numerical value which is stored
    int color;
    
    // Length is the length of the code
    int length;
    
    // Code 
    unsigned int code;
};

// structure for the bit stream used for writing data
struct bitstream
{
    // Data to be used
    unsigned char *data;
    
    // Size of the data
    long int data_size;
    
    // Last bit in the stream
    long int last_bit;
    
    // Position in data, that we are currently reading/writing
    long int current_data;
    
    // Which bit is being read/write
    int current_bit;
};

// Main function prototype
unsigned char *huffman_encode_image(struct PGM_Image *input_pgm_image, struct node *huffman_node, int number_of_nodes, unsigned long int *length_of_encoded_array);

// Helper function prototypes
void generate_huffman_codes(struct huffman_code *huffman_code_array, int arrayLen, int first, int second);
void writeData(struct bitstream *stream, struct huffman_code *codeStruct);
