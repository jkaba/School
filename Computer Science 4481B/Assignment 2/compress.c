

#include "asn2.h"

int main(int argc, char *argv[]) {
	char* inputUncompressedFileName = argv[1];
	char* outputCompressedFileName = argv[2];
	int number_of_non_zero_values_in_the_frequency_array = 0;
	struct PGM_Image pic;

	//load the uncompressed image into a PGM struct
	if(load_PGM_Image(&pic, inputUncompressedFileName) == -1){
		printf("Error opening image\n");
		exit(EXIT_FAILURE);
	}

	long int* pixel_frequency = generate_pixel_frequency(&pic,&number_of_non_zero_values_in_the_frequency_array);
	
	struct node* huffman_nodes = generate_Huffman_nodes(pixel_frequency,pic.maxGrayValue,number_of_non_zero_values_in_the_frequency_array);
	free(pixel_frequency);

	unsigned long int length_of_encoded_array;
	unsigned char* encoded_image = Huffman_encode(&pic,huffman_nodes,number_of_non_zero_values_in_the_frequency_array-1,&length_of_encoded_array);

	store_Huffman_encoded_data(outputCompressedFileName,pic.width,pic.height,pic.maxGrayValue,number_of_non_zero_values_in_the_frequency_array-1,huffman_nodes,length_of_encoded_array,encoded_image);
	
	free(huffman_nodes);
	free(encoded_image);
	free_PGM_Image(&pic);

	printf("Image Compressed\n");
	return 0;
}

//using a PGM image calculate the frequency of each pixel and return an array of those frequencies
long int* generate_pixel_frequency(struct PGM_Image *input_pgm_image, int *number_of_non_zero_values_in_the_frequency_array){
	int width = input_pgm_image->width;
	int height = input_pgm_image->height;
	int maxGrayValue = input_pgm_image->maxGrayValue;
	long int* pixel_frequency;
	long int value;

	//initialize the pixel frequencies to 0
	pixel_frequency = malloc(sizeof(long int)*(maxGrayValue+1));
	for(int i = 0; i< maxGrayValue+1; i++){
		pixel_frequency[i] = 0;
	}

	//add up the pixel frequencies
	for(int row = 0; row < height; row++){
		for(int col = 0; col < width; col++){
			if(input_pgm_image->image[row][col] >= 0){
				value = input_pgm_image->image[row][col];
				pixel_frequency[value] ++;
			}

		}
	}

	for(int i = 0; i <maxGrayValue+1; i++){
		if(pixel_frequency[i] != 0){
			(*number_of_non_zero_values_in_the_frequency_array)++;
		}
	}
	return pixel_frequency;
}

//using the pixel frequencies generate the huffman nodes
struct node *generate_Huffman_nodes(long int *pixel_frequency, int max_gray_value, int number_of_non_zero_values_in_the_frequency_array){
	struct node* huffman_nodes = (struct node*)malloc(sizeof(struct node)*(number_of_non_zero_values_in_the_frequency_array-1));
	
	int position1,position2;

	for(int nodePos = 0; nodePos < number_of_non_zero_values_in_the_frequency_array-1; nodePos++){
		long int firstFreq = -1;
		long int secondFreq = -1;

		//search the frequencies for first smallest frequency
		for(int i=0; i< max_gray_value+1; i++){
			if(pixel_frequency[i] != 0 && (firstFreq == -1 || pixel_frequency[i] < firstFreq)){
				firstFreq = pixel_frequency[i];
				position1 = i;
			}
		}

		//search the frequencies for second smallest frequency
		for(int i=0; i< max_gray_value+1; i++){
			if(position1 == i)
				continue;
			if(pixel_frequency[i] != 0 && (secondFreq == -1 || pixel_frequency[i] < secondFreq)){
				secondFreq = pixel_frequency[i];
				position2 = i;
			}
		}

		//set the position of first frequency to the updated value
		pixel_frequency[position1] = firstFreq + secondFreq;
		//set the second frequency in the array to zero
		pixel_frequency[position2] = 0;

		//store the values in the nodes.
		//store the least frequent in the last position
		huffman_nodes[number_of_non_zero_values_in_the_frequency_array-2 - nodePos].first_value = position2; 
		huffman_nodes[number_of_non_zero_values_in_the_frequency_array-2 - nodePos].second_value = position1;
	}


	return huffman_nodes;
}

//takes a PGM image, builds the code using the huffman nodes, encodes the image and returns the encoded image
unsigned char *Huffman_encode(struct PGM_Image *input_pgm_image, struct node *Huffman_node, int number_of_nodes, unsigned long int *length_of_encoded_array){
	unsigned char* encoded = (unsigned char*)malloc((input_pgm_image->width*input_pgm_image->height)*sizeof(unsigned char));

	//allocate memory for the codes
	//store the codes in an array of strings
	//each code is a string
	char** codes = (char**)malloc((input_pgm_image->maxGrayValue +1)*sizeof(char*));
	for(int i = 0; i < input_pgm_image->maxGrayValue +1; i++){
		codes[i] = (char*)malloc((input_pgm_image->maxGrayValue +1)*sizeof(char));
		for(int j = 0; j < input_pgm_image->maxGrayValue +1; j++){
			codes[i][j] = '\0';
		}
	}

	//create the huffman code
	for(int i = 0; i < number_of_nodes; i++){
		int position1 = Huffman_node[i].first_value;
		int position2 = Huffman_node[i].second_value;

		if(strlen(codes[position1]) > strlen(codes[position2]))
			strcpy(codes[position2],codes[position1]);
		else if (strlen(codes[position2]) > strlen(codes[position1]))
			strcpy(codes[position1],codes[position2]);

		codes[position1] = strcat(codes[position1], "0");
		codes[position2] = strcat(codes[position2], "1");
	}

	//PRINTS the codes for debugging purposes
	// for(int i = 0; i < input_pgm_image->maxGrayValue+1; i++){
	// 	if(strcmp(codes[i],"") != 0)
	// 		printf("%d   %s\n",i,codes[i]);
	// }

	//iterate through the image and encode the data using the created huffman code
	int j =0;
	unsigned char c = 0;
	int bitCount = 0;
	for(int row = 0; row < input_pgm_image->height; row++){	
		for(int col = 0; col < input_pgm_image->width; col++){
			int pixelValue = input_pgm_image->image[row][col];
			
			//take the value from the image and build the code into the unsigned char array
			for(int i = 0; codes[pixelValue][i] != '\0'; i++){
				if(codes[pixelValue][i] == '1')
					c+= (1 << (7- bitCount));
				if(++bitCount == 8)
				{
					encoded[j] = c;
					j++;
					c = 0;
					bitCount = 0;
				}
			}
			
		}		
	}
	
	if(bitCount != 0){
		encoded[j] = c;
		j++;
	}
	
	*length_of_encoded_array = j;

	//reallocate the memory to be only the size of the compressed image
	encoded = (unsigned char*)realloc(encoded,*length_of_encoded_array);
	for(int i = 0; i < input_pgm_image->maxGrayValue +1; i++){
		free(codes[i]);
	}
	free(codes);
	
	return encoded;
}

//save all of the header values, nodes, and the encoded image data into a file
void store_Huffman_encoded_data(char *compressed_file_name_ptr, int image_width, int image_height, int max_gray_value, int number_of_nodes, struct node *Huffman_node, long int length_of_encoded_image, unsigned char *encoded_image){
	FILE *file = fileOpener(WRITE, compressed_file_name_ptr);
	if(file == NULL){
		printf("Error opening file\n");
		exit(EXIT_FAILURE);
	}
	
	//save the header data as integers
	fprintf(file, "%d %d %d %d\n", image_width,image_height,max_gray_value,number_of_nodes);
	
	//save the nodes as integers
	for(int i = 0; i < number_of_nodes; i++){
		fprintf(file, "%d %d ", Huffman_node[i].first_value,Huffman_node[i].second_value);
	}

	//save the image as unsigned characters
	fprintf(file, "%ld ", length_of_encoded_image);
	for(int i = 0; i < length_of_encoded_image; i++){
		fputc(encoded_image[i],file);
	}
	fclose(file);
}
