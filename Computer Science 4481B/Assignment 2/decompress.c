

#include "asn2.h"

int main(int argc, char *argv[]) {
	char* inputCompressedFileName = argv[1];
	char* outputUncompressedFileName = argv[2];
	
	int width,height,maxGrayValue,number_of_nodes;
	long int len_of_encoded_image;
	struct node* huffman_node;
	unsigned char * encoded = read_Huffman_encoded_data(inputCompressedFileName,&width,&height,&maxGrayValue,&number_of_nodes,&huffman_node,&len_of_encoded_image);

	struct PGM_Image *pic2 = Huffman_decode_image(width,height,maxGrayValue,number_of_nodes,huffman_node,len_of_encoded_image, encoded);
	
	if(save_PGM_Image(pic2, outputUncompressedFileName, 0) == -1){
		printf("Error saving PGM image\n");
		exit(EXIT_FAILURE);
	}

	free_PGM_Image(pic2);
	free(pic2);
	free(huffman_node);

	printf("Image Decompressed\n");
	return 0;
}

//read the encoded data and save it into the approriate memory locations
unsigned char *read_Huffman_encoded_data(char *compressed_file_name_ptr, int *image_width, int *image_height, int *max_gray_value, int *number_of_nodes, struct node **Huffman_node, long int *length_of_encoded_image){
	FILE *file = fileOpener(READ, compressed_file_name_ptr);
	if(file == NULL)
		exit(EXIT_FAILURE);

	//get the header values
	*image_width = geti(file);
	*image_height = geti(file);
	*max_gray_value = geti(file);
	*number_of_nodes = geti(file);

	//allocate memory for the nodes
	Huffman_node[0] = malloc(sizeof(struct node)*(*number_of_nodes));

	//populate the node memory with the node values
	for(int i = 0; i < *number_of_nodes; i++){
		Huffman_node[0][i].first_value = geti(file);
		Huffman_node[0][i].second_value = geti(file);
	}

	*length_of_encoded_image = geti(file);

	//create and populate an unsigned char array with all of the encoded data
	unsigned char* encoded_image = malloc(*length_of_encoded_image*sizeof(unsigned char));
	for(int i = 0; i < *length_of_encoded_image; i++){
		encoded_image[i] = fgetc(file);
	}

	fclose(file);
	return encoded_image;
}

//decode the encoded image and save it to a PGM_Image function
struct PGM_Image *Huffman_decode_image( int image_width, int image_height, int max_gray_value, int number_of_nodes, struct node *Huffman_node, long int length_of_encoded_image, unsigned char *encoded_image){
	struct PGM_Image *image = malloc(sizeof(struct PGM_Image));
	create_PGM_Image(image, image_width, image_height, max_gray_value);

	//allocate memory for the tree used in decoding
	//set the root and the first two children initially
	struct tree* root = malloc(sizeof(struct tree));
	root->value = 0;
	root->left = malloc(sizeof(struct tree));
	root->right = malloc(sizeof(struct tree));
	root->left->value = Huffman_node[0].first_value;
	root->right->value = Huffman_node[0].second_value;

	//populate the tree with all of the huffman nodes
	for(int i = 1; i < number_of_nodes; i++){
		int first = Huffman_node[i].first_value;
		int second = Huffman_node[i].second_value;
		//printf("f: %d  s: %d\n",Huffman_node[i].first_value,Huffman_node[i].second_value);
		addToTree(root,first,second);
	}

	//code will hold the huffman code as it is being built
	//reset pointer is used to make code point back to the start of the allocated memory
	char c;
	int bitCount = 0;
	int* code = malloc(sizeof(int)*max_gray_value);
	int* resetPointer = code;

	//i holds the position of the char in the encoded image
	int i = 0;
	for(int row = 0; row<image_height; row++){
		for(int col = 0; col < image_width; col++){

			//initialize the code array to value 2 as a placeholder
			for(int j = 0; j <  max_gray_value; j++){
				code[j] = 2;
			}

			//symbol holds the return value from the tree
			//symbol = -1 means the value hasnt been found
			//symbol != -1 means the code was found in the tree
			int symbol = -1;
			for(int j = 0; symbol == -1 ; j++){

				//exit if i is pointing past the end of the encoded image
				if(i > length_of_encoded_image)
				{
					printf("exceeded encoded image\n");
					exit(EXIT_FAILURE);
				}

				//if the bitcound is 0 then we are at the end of the current char
				//reset it to 8 and get the next char from the encoded image
				if(bitCount == 0)
				{
					c = encoded_image[i++];
					bitCount = 8;
				}
				//store the next bit from c into the array
				code[j] = ((c >> --bitCount) & 1);

				//check the node tree for the code
				symbol = checkTree(root,code);

			}

			//reset the code pointer
			code = resetPointer;
			//save the pixel in the image
			image->image[row][col] = symbol;
		}
	}

	free(code);
	freeTree(root);
	free(root);
	free(encoded_image);

	return image;
}

//add a node to the tree with recursion
void addToTree(struct tree* root, int val1, int val2){
	//base case is value is found on the left or right
	if(root->left->value == val2){
		root->left->right = malloc(sizeof(struct tree));
		root->left->right->value = val2;
		root->left->left = malloc(sizeof(struct tree));
		root->left->left->value = val1;
		root->left->value = -1;
	}
	else if(root->right->value == val2){
		root->right->right = malloc(sizeof(struct tree));
		root->right->right->value = val2;
		root->right->left = malloc(sizeof(struct tree));
		root->right->left->value = val1;
		root->right->value = -1;
	}
	//if value is not found search recursively for the value
	else{
		if(root->left->value == -1){
			addToTree(root->left,val1,val2);
		}	
		if(root->right->value == -1){
			addToTree(root->right,val1,val2);
		}
	}
}

//iterate through tree structure to find the code
int checkTree(struct tree* root, int* code){
	
	if(*code == 2){
		//returns -1 if no code and value if code
		return root->value;
	}
	else{
		//if code is 1 then go right
		if(*code == 1){
			return checkTree(root->right, ++code);
		}
		//if code is 0 then go left
		else if (*code == 0){
			return checkTree(root->left, ++code);
		}
		else{
			//ERROR
			printf("ERROR with code: %c\n", *code);
			return -2;
		}
	}
}

//iterate through the tree structure and free the memory
void freeTree(struct tree* root){
	if(root->left->value != -1){
		free(root->left);
	}
	else{
		freeTree(root->left);
		free(root->left);
	}
	if(root->right->value != -1){
		free(root->right);
	}
	else{
		freeTree(root->right);
		free(root->right);
	}
}
