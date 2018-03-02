
#include "asn2.h"

int main(int argc, char *argv[]){
	char* image1 = argv[1];
	char* image2 = argv[2];

	float mae = mean_absolute_error(image1,image2);
	printf("The Mean Absolute Error is: %f\n",mae);

	return 0;
}

float mean_absolute_error(char *file_name_1_ptr, char *file_name_2_ptr){
	struct PGM_Image pic1;
	struct PGM_Image pic2;
	load_PGM_Image(&pic1, file_name_1_ptr);
	load_PGM_Image(&pic2, file_name_2_ptr);

	if(pic1.width != pic2.width || pic1.height != pic2.height){
		printf("Images not the same size\n");
		return -1;
	}
	float mae = 0;
	for(int row = 0; row < pic1.height; row++){
		for(int col = 0; col < pic1.width; col++){
			mae += (pic1.image[row][col] - pic2.image[row][col]);
		}
	}

	mae = mae * (1/(pic1.width*pic1.height));
	return mae;
}  
