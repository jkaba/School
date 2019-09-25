#include "libpnm.h"

/*-------------------------------------------------*/
/* A SIMPLE TEST/EXAMPLE OF HOW TO USE THE LIBRARY */
/*-------------------------------------------------*/
int main() { 
        int row, col, pixel;

	struct PGM_Image pic1, pic2, pic3,       pic5, pic6, pic7, pic8, pic9;
	struct PPM_Image pic_ppm;
	struct PPM_Image pic_ppm_1;
	struct PPM_Image pic_ppm_2;
	struct PPM_Image pic_ppm_3;
	struct PPM_Image pic_ppm_4;
	struct PPM_Image pic_ppm_5;
	struct PPM_Image pic_ppm_6;
	struct PPM_Image pic_ppm_7;
	struct PPM_Image pic_ppm_8;
	struct PPM_Image pic_ppm_9;
	struct PPM_Image pic_ppm_10;
	struct PPM_Image pic_ppm_11;

	load_PPM_Image(&pic_ppm, "peppers.ppm");

	copy_PPM_to_PGM(&pic_ppm, &pic1, RED);
	copy_PPM_to_PGM(&pic_ppm, &pic2, GREEN);
	copy_PPM_to_PGM(&pic_ppm, &pic3, BLUE);
	convert_PPM_to_PGM(&pic_ppm, &pic6); 
	convert_PPM_to_PGM(&pic_ppm, &pic7); 
	convert_PPM_to_PGM(&pic_ppm, &pic8); 
	convert_PPM_to_PGM(&pic_ppm, &pic9); 

fprintf(stderr, "After copying and converting\n");

        for(row = 0; row<pic6.height; row++)
           for(col = 0; col<pic6.width; col++)
              pic6.image[row][col] = 0;

fprintf(stderr, "After calculating pic6\n");

        for(row = 0; row<pic_ppm.height; row++)
           for(col = 0; col<pic_ppm.width; col++)
           {
             pixel = 0.299 * pic1.image[row][col]
                   + 0.587 * pic2.image[row][col]
                   + 0.114 * pic3.image[row][col];
             pic7.image[row][col] = ((pixel < 0)? 0 
                                                :((pixel > 255)?255: pixel));

             pixel = -0.1687 * pic1.image[row][col]
                    - 0.3313 * pic2.image[row][col]
                    + 0.5    * pic3.image[row][col]
                    + 128;
             pic8.image[row][col] = ((pixel < 0)? 0 
                                                :((pixel > 255)?255: pixel));

             pixel = 0.5    * pic1.image[row][col]
                    -0.4187 * pic2.image[row][col]
                    -0.0813 * pic3.image[row][col]
                    + 128;
             pic9.image[row][col] = ((pixel < 0)? 0 
                                                :((pixel > 255)?255: pixel));

           }

fprintf(stderr, "After calculating pic9\n");

        convert_PPM_to_PGM_using_average(&pic_ppm, &pic5);

        copy_3_PGM_to_PPM(&pic1, &pic2, &pic3, &pic_ppm_1); 
        copy_3_PGM_to_PPM(&pic1, &pic3, &pic2, &pic_ppm_2); 
        copy_3_PGM_to_PPM(&pic2, &pic1, &pic3, &pic_ppm_3); 
        copy_3_PGM_to_PPM(&pic3, &pic1, &pic2, &pic_ppm_4); 
        copy_3_PGM_to_PPM(&pic2, &pic3, &pic1, &pic_ppm_5); 
        copy_3_PGM_to_PPM(&pic3, &pic2, &pic1, &pic_ppm_6); 

        copy_3_PGM_to_PPM(&pic1, &pic6, &pic6, &pic_ppm_7); 
        copy_3_PGM_to_PPM(&pic6, &pic2, &pic6, &pic_ppm_8); 
        copy_3_PGM_to_PPM(&pic6, &pic6, &pic3, &pic_ppm_9); 

        copy_3_PGM_to_PPM(&pic6, &pic6, &pic8, &pic_ppm_10); 
        copy_3_PGM_to_PPM(&pic9, &pic6, &pic6, &pic_ppm_11); 

fprintf(stderr, "After all copy_3_PGM_to_PPM\n");

	save_PGM_Image(&pic1, "peppers.R.pgm", true);
	save_PGM_Image(&pic2, "peppers.G.pgm", true);
	save_PGM_Image(&pic3, "peppers.B.pgm", true);
	save_PGM_Image(&pic7, "peppers.Y.pgm", true); 
	save_PGM_Image(&pic8, "peppers.Cb.pgm", true); 
	save_PGM_Image(&pic9, "peppers.Cr.pgm", true); 

	save_PGM_Image(&pic5, "peppers.AVERAGE.pgm", true); 

fprintf(stderr, "After Saving PGM\n");

	save_PPM_Image(&pic_ppm_1, "peppers.RGB.ppm", true); 
	save_PPM_Image(&pic_ppm_2, "peppers.RBG.ppm", true); 
	save_PPM_Image(&pic_ppm_3, "peppers.GRB.ppm", true); 
	save_PPM_Image(&pic_ppm_4, "peppers.BRG.ppm", true); 
	save_PPM_Image(&pic_ppm_5, "peppers.GBR.ppm", true); 
	save_PPM_Image(&pic_ppm_6, "peppers.BGR.ppm", true); 

	save_PPM_Image(&pic_ppm_7, "peppers.R.ppm", true); 
	save_PPM_Image(&pic_ppm_8, "peppers.G.ppm", true); 
	save_PPM_Image(&pic_ppm_9, "peppers.B.ppm", true); 

	save_PPM_Image(&pic_ppm_10, "peppers.Cb.ppm", true); 
	save_PPM_Image(&pic_ppm_11, "peppers.Cr.ppm", true); 

fprintf(stderr, "After Saving PPM\n");

	free_PGM_Image(&pic1);
	free_PGM_Image(&pic2);
	free_PGM_Image(&pic3);
	free_PGM_Image(&pic5);
	free_PGM_Image(&pic6);
	free_PGM_Image(&pic7);
	free_PGM_Image(&pic8);
	free_PGM_Image(&pic9);
	free_PPM_Image(&pic_ppm);
	free_PPM_Image(&pic_ppm_1);
	free_PPM_Image(&pic_ppm_2);
	free_PPM_Image(&pic_ppm_3);
	free_PPM_Image(&pic_ppm_4);
	free_PPM_Image(&pic_ppm_5);
	free_PPM_Image(&pic_ppm_6);
	free_PPM_Image(&pic_ppm_7);
	free_PPM_Image(&pic_ppm_8);
	free_PPM_Image(&pic_ppm_9);
	free_PPM_Image(&pic_ppm_10);
	free_PPM_Image(&pic_ppm_11);
      
        return 0;}
