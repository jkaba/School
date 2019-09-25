/*
 * CS4481B Assignment 2
 * Name: Jameel Kaba
 * UWO/GAUL ID: jkaba
 * student #: 250796017
 */

#include "libpnm.h"
#include "generate_huffman_nodes.h"

// Tree node structure, the node has a stored color value and two children
struct treeNode
{
    int color;
    int left;
    int right;
};

// Bitstream structure to help with data writing
struct bitstream
{
    unsigned char *data;
    
    // Size of data array
    long int data_size;
    
    // Last bit in the stream
    long int last_bit;
    
    // Position in data, that we are currently reading/writing
    long int current_data;
    
    // Which bit is being read/write
    int current_bit;
};

// Main method
struct PGM_Image *huffman_decode_image( int image_width, int image_height, int max_gray_value, int number_of_nodes, struct node *huffman_node, long int length_of_encoded_image, unsigned char *encoded_image);

// helper functions
int findNode(struct treeNode *tree,int symbol,int treeSize);
int getEmptyNode(struct treeNode *tree,int treeSize);
struct treeNode *generate_huffman_tree(struct node *huffman_node,int lengthOfNodeArray);
int readData(struct bitstream *stream, struct treeNode *tree);
