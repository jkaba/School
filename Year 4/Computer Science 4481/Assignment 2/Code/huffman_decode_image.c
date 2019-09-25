/*
 * CS4481B Assignment 2
 * Name: Jameel Kaba
 * UWO/GAUL ID: jkaba
 * student #: 250796017
 */

// Include header files
#include "huffman_decode_image.h"

// huffman_decode_image, this program decodes an encoded image using huffman
struct PGM_Image *huffman_decode_image( int image_width, int image_height, int max_gray_value, int number_of_nodes, struct node *huffman_node, long int length_of_encoded_image, unsigned char *encoded_image){
    
    // Allocate memory and create the image
    struct PGM_Image *pic1 = malloc(sizeof(struct PGM_Image));
    create_PGM_Image(pic1, image_width,image_height,max_gray_value);
    
    // Create a huffman tree from the root
    struct treeNode *root = generate_huffman_tree(huffman_node, number_of_nodes);
    
    // Bitstream needed for determining bits
    struct bitstream stream;
    
    // Set the data stream to be the encoded image
    stream.data = encoded_image;
    
    // data size is based on the length of the encoded image
    stream.data_size = length_of_encoded_image;
    
    // Set the last bit
    stream.last_bit = 0L;
    
    // Set the current data position
    stream.current_data = 0L;
    
    // Set the current bit position
    stream.current_bit = 7;
    
    // Loop through the image
    for (int row = 0; row < pic1->height; row++){
        for (int col = 0; col < pic1->width; col++){
            
            // Read the data at the current position
            pic1->image[row][col] = readData(&stream, root);
        }
    }
    
    // Return the decoded image
    return pic1;
}

// Method used to create the huffman tree
struct treeNode *generate_huffman_tree(struct node *huffman_node, int lengthOfNodeArray){
    
    // Create the tree array
    int treeSize = (lengthOfNodeArray+1)+(lengthOfNodeArray);
    struct treeNode *tree = malloc(treeSize*sizeof(struct treeNode));
    
    // Initialize the tree by setting values to -1
    for(int i = treeSize-1; i >= 0; i--){
        tree[i].color = -1;
        tree[i].left = -1;
        tree[i].right = -1;
    }
    
    // Initialize the root node
    
    // Initialize the left child, will always be position 1
    int leftNodeIndex = 1;
    tree[0].left = leftNodeIndex;
    tree[leftNodeIndex].color = huffman_node[lengthOfNodeArray-1].first_value;
    
    // Initialize the right child, will always be position 2
    int rightNodeIndex = 2;
    tree[0].right = rightNodeIndex;
    tree[rightNodeIndex].color = huffman_node[lengthOfNodeArray-1].second_value;
    
    // Loop through all nodes except for the root
    for(int j = lengthOfNodeArray - 2; j >= 0; j--){
        
        // Search for the first index
        int firstIndex = findNode(tree, huffman_node[j].first_value, treeSize);
        
        // Get the new empty node to the left
        leftNodeIndex = getEmptyNode(tree, treeSize);
        
        // Assign the left child to reference the index
        tree[firstIndex].left = leftNodeIndex;
        
        // Set the left color to be the first value in the huffman node
        tree[leftNodeIndex].color = huffman_node[j].first_value;
        
        // Get the new empty node to the right
        rightNodeIndex = getEmptyNode(tree, treeSize);
        
        // Assign right child to reference the index
        tree[firstIndex].right = rightNodeIndex;
        
        // Set the right color to be the second value in the huffman node
        tree[rightNodeIndex].color = huffman_node[j].second_value;
        
        // Set the color of the first index to -1
        tree[firstIndex].color = -1;
    }
    
    // Return the tree
    return tree;
}

// find node, returns the index of the node with the color, or -1 if it doesn't exist
int findNode(struct treeNode *tree, int color, int treeSize){
    
    // Loop through tree to see if the element with the requested color exists
    for(int i = 0; i < treeSize; i++){
        
        // If the element exists, return the index
        if(tree[i].color == color){
            return i;
        }
    }
    
    // Element does not exist so return -1
    return -1;
}

// get empty node, returns the next avaialable empty node
int getEmptyNode(struct treeNode *tree, int treeSize){
    
    // Search through the tree for an empty/unintialized node
    for(int i = 1; i < treeSize; i++){
        
        // If an empty node is available return the index
        if(tree[i].color == -1 && tree[i].left == -1 && tree[i].right == -1){
            return i;
        }
    }
    
    // Return -1 if there are no more empty nodes
    return -1;
}

// read data, this function reads the data from the encoded image and searches the tree for decoding
int readData(struct bitstream *stream, struct treeNode *tree){
    
    // Set the initial position to 0
    int currentNode = 0;
    
    // Loop through the encoded data
    while(stream->current_data<stream->data_size){
        
        // While the current bit is positive
        while(stream->current_bit >= 0){
            
            // If the current bit is 1, the code bit value is 1
            if (((stream->data[stream->current_data] >> stream->current_bit) & 0x01)){
                
                // Move towards the side with 1
                currentNode = tree[currentNode].right;

                // Reduce the bit
                stream->current_bit--;
                
                // Check to see, if the node is a leaf
                if(tree[currentNode].left == -1 && tree[currentNode].right == -1)
                {
                    // If so, then we have reached the encoding for this color
                    return tree[currentNode].color;
                }
            }
            
            // Code bit value is 0
            else{
                
                // Move along the zero side of the tree
                currentNode = tree[currentNode].left;
                
                // Reduce the bit
                stream->current_bit--;
                
                // Check to see if the node is a leaf
                if(tree[currentNode].left == -1 && tree[currentNode].right == -1){
                    
                    // If so, then we have reached the encoding for this color
                    return tree[currentNode].color;
                }
            }
        }
        
        // Increment the current position
        stream->current_data++;
        
        // Reset the current bit location
        stream->current_bit = 7;
    }
    
    // If this point is reached, there was a problem reading data
    // Return an error
    printf("Error: Trouble reading data");
    return 1;
}
