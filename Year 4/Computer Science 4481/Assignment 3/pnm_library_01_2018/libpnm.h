# include <stdio.h>
# include <stdlib.h>

#ifndef _PNM_LIB_H_
#define _PNM_LIB_H_

// booleans
# define false 0
# define true  1
typedef int bool;

// black and white
# define BLACK 1
# define WHITE 0

// colors
enum Color {RED = 0, GREEN, BLUE};

// the maximum value a pixel can have
# define MAX_GRAY_VALUE 255

// the three pnm formats
enum Format {PBM = 1, PGM, PPM};

/*-------------*/
/* A PBM IMAGE */
/*-------------*/
struct PBM_Image
{ // the image dimensions
  int width, height;

  // the 2D image
  unsigned char * * image;
};

/*-------------*/
/* A PGM IMAGE */
/*-------------*/
struct PGM_Image
{ // the image dimensions
  int width, height;

  // the max gray value of the image
  int maxGrayValue; 

  // the 2D image
  unsigned char * * image;
};

/*-------------*/
/* A PPM IMAGE */
/*-------------*/
struct PPM_Image
{ // the image dimensions
  int width, height; 

  // the max gray value of the image
  int maxGrayValue;

  // the 2D image
  unsigned char * * * image;
};

/*--------------*/
/* OPENS A FILE */
/*--------------*/

enum FileAction {READ, WRITE};

FILE * fileOpener(enum FileAction fileAction, char * fileName);

/*-------------------------------------------------------------*/
/* GETS AN INTEGER FROM FILE SKIPPING WHITE SPACE AND COMMENTS */
/*-------------------------------------------------------------*/
int geti(FILE * filePointer);

/*------------------------------------------------------*/
/* THE PBM 'CONSTRUCTOR' WHICH LOADS AN IMAGE FROM FILE */
/*------------------------------------------------------*/
int load_PBM_Image(struct PBM_Image * pbmImage, char * fileName);

/*-------------------------------------------------*/
/* THE PBM 'CONSTRUCTOR' WHICH CREATES A NEW IMAGE */
/*-------------------------------------------------*/
int create_PBM_Image(struct PBM_Image * pbmImage, int width, int height);

/*--------------------------------------*/
/* FREES MEMORY CONSUMED BY A PBM IMAGE */
/*--------------------------------------*/
void free_PBM_Image(struct PBM_Image * pbmImage);

/*-----------------------------*/
/* SAVES THE PBM IMAGE TO FILE */
/*-----------------------------*/
int save_PBM_Image(struct PBM_Image * pbmImage, char * fileName, bool raw);

/*------------------------------------------------------*/
/* THE PGM 'CONSTRUCTOR' WHICH LOADS AN IMAGE FROM FILE */
/*------------------------------------------------------*/
int load_PGM_Image(struct PGM_Image * pgmImage, char * fileName);

/*-------------------------------------------------*/
/* THE PGM 'CONSTRUCTOR' WHICH CREATES A NEW IMAGE */
/*-------------------------------------------------*/
int create_PGM_Image(struct PGM_Image * pgmImage,
                     int width, int height, int maxGrayValue);

/*--------------------------------------*/
/* FREES MEMORY CONSUMED BY A PGM IMAGE */
/*--------------------------------------*/
void free_PGM_Image(struct PGM_Image * pgmImage);

/*-----------------------------*/
/* SAVES THE PGM IMAGE TO FILE */
/*-----------------------------*/
int save_PGM_Image(struct PGM_Image * pgmImage, char * fileName, bool raw);

/*------------------------------------------------------*/
/* THE PPM 'CONSTRUCTOR' WHICH LOADS AN IMAGE FROM FILE */
/*------------------------------------------------------*/
int load_PPM_Image(struct PPM_Image * ppmImage, char * fileName);

/*-------------------------------------------------*/
/* THE PPM 'CONSTRUCTOR' WHICH CREATES A NEW IMAGE */
/*-------------------------------------------------*/
int create_PPM_Image(struct PPM_Image * ppmImage, 
                     int width, int height, int maxGrayValue);

/*--------------------------------------*/
/* FREES MEMORY CONSUMED BY A PPM IMAGE */
/*--------------------------------------*/
void free_PPM_Image(struct PPM_Image * ppmImage);

/*-----------------------------*/
/* SAVES THE PPM IMAGE TO FILE */
/*-----------------------------*/
int save_PPM_Image(struct PPM_Image * ppmImage, char * fileName, bool raw);

/*-----------------------------------*/
/* COPIES A PBM IMAGE TO A PGM IMAGE */
/*-----------------------------------*/
int copy_PBM_to_PGM(struct PBM_Image * pbmImage, struct PGM_Image * pgmImage);

/*-----------------------------------*/
/* COPIES A PBM IMAGE TO A PPM IMAGE */
/*-----------------------------------*/
int copy_PBM_to_PPM(struct PBM_Image * pbmImage, struct PPM_Image * ppmImage);

/*-----------------------------------*/
/* COPIES A PGM IMAGE TO A PBM IMAGE */
/*-----------------------------------*/
int copy_PGM_to_PBM(struct PGM_Image * pgmImage, struct PBM_Image * pbmImage);

/*-----------------------------------*/
/* COPIES 3 PGM IMAGES TO A PPM IMAGE */
/*-----------------------------------*/
int copy_3_PGM_to_PPM(struct PGM_Image * pgmImage_R,
                      struct PGM_Image * pgmImage_G,
                      struct PGM_Image * pgmImage_B,
                      struct PPM_Image * ppmImage);

/*-----------------------------------*/
/* COPIES A PGM IMAGE TO A PPM IMAGE */
/*-----------------------------------*/
int copy_PGM_to_PPM(struct PGM_Image * pgmImage, struct PPM_Image * ppmImage);

/*-----------------------------------*/
/* COPIES A PPM IMAGE TO A PBM IMAGE */
/*-----------------------------------*/
int copy_PPM_to_PBM(struct PPM_Image * ppmImage, 
                    struct PBM_Image * pbmImage, enum Color color);

/*-----------------------------------*/
/* COPIES A PPM IMAGE TO A PGM IMAGE */
/*-----------------------------------*/
int copy_PPM_to_PGM(struct PPM_Image * ppmImage, 
                    struct PGM_Image * pgmImage, enum Color color);

/*-----------------------------------------------------------*/
/* CONVERTS A PPM IMAGE TO A PGM IMAGE USING THE Y COMPONENT */
/*-----------------------------------------------------------*/
int convert_PPM_to_PGM(struct PPM_Image * ppmImage, 
                       struct PGM_Image * pgmImage);

/*-----------------------------------------------------------*/
/* CONVERTS A PPM IMAGE TO A PGM IMAGE USING AVERAGE         */
/*-----------------------------------------------------------*/
int convert_PPM_to_PGM_using_average(struct PPM_Image * ppmImage, 
                       struct PGM_Image * pgmImage);

/*--------------------*/
/* COPIES A PBM IMAGE */
/*--------------------*/
int copy_PBM(struct PBM_Image * pbmImage, struct PBM_Image * copy);

/*--------------------*/
/* COPIES A PGM IMAGE */
/*--------------------*/
int copy_PGM(struct PGM_Image * pgmImage, struct PGM_Image * copy);

/*--------------------*/
/* COPIES A PPM IMAGE */
/*--------------------*/
int copy_PPM(struct PPM_Image * ppmImage, struct PPM_Image * copy);
#endif /*_PNM_LIB_H_*/
