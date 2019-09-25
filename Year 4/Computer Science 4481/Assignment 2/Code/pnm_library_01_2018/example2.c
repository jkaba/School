#include "libpnm.h"

/*-------------------------------------------------*/
/* A SIMPLE TEST/EXAMPLE OF HOW TO USE THE LIBRARY */
/*-------------------------------------------------*/
int main(int arg_count, char * arg_val[]) { 
        int row, col;

	struct PGM_Image pic1, pic2, pic3;

        if(arg_count != 3)
        { printf("Usage: %s input_image_1 input_image_2\n", arg_val[0]);
          return -1;
        }
 	printf("%d\n", load_PGM_Image(&pic1, arg_val[1]));
	printf("%d\n", load_PGM_Image(&pic2, arg_val[2]));
	printf("%d\n", load_PGM_Image(&pic3, arg_val[2]));

fprintf(stderr, "After loading\n");

           printf("%d %d\n", pic1.width,pic1.height);
 
        for(row = 0; row<pic1.height; row++)
           for(col = 0; col<pic1.width; col++)
{ if (pic1.image[row][col] != pic2.image[row][col])
    printf("%d %d   %d   %d\n", row, col, pic1.image[row][col], pic2.image[row][col]);

  pic3.image[row][col] = abs(pic1.image[row][col] -
                                      pic2.image[row][col]);
}

	save_PGM_Image(&pic3, "diff.pgm", true);

	free_PGM_Image(&pic1);
	free_PGM_Image(&pic2);
	free_PGM_Image(&pic3);
      
        return 0;}
