#include "libpnm.h"

/*--------------*/
/* OPENS A FILE */
/*--------------*/

FILE * fileOpener(enum FileAction fileAction, char * fileName)
{ 
  FILE * filePointer;
    
  if(fileAction == READ) filePointer = fopen(fileName, "rb");
  if(fileAction == WRITE) filePointer = fopen(fileName, "wb");

  return filePointer; 
}

/*-------------------------------------------------------------*/
/* GETS AN INTEGER FROM FILE SKIPPING WHITE SPACE AND COMMENTS */
/*-------------------------------------------------------------*/
int geti(FILE * filePointer)
{ /*----------------------*/
  /* VARIABLE DECLARATION */
  /*----------------------*/

  // to read in data from file
  char c; int i = 0;

  /*----------------------*/
  /* FIND THE FIRST DIGIT */
  /*----------------------*/
  do
  { // get another character
    c = fgetc(filePointer);

    /*---------------*/
    /* SKIP COMMENTS */
    /*---------------*/
    if(c == '#')
      do 
      { c = getc(filePointer);
        if(c == EOF) return -1;
      }
      while (c != '\n' && c != '\r' );
    
    // if end of file is reached, return an error flag
    if(c == EOF) return -1;
  } while (c == ' ' || c == '\t' || c == '\n' || c == '\r');

  // make sure it is a digit
  if(c < '0' || c > '9') return -1;

  /*----------------------------*/
  /* GET THE REST OF THE DIGITS */
  /*----------------------------*/
  do 
  { // add in the next digit
    i = i * 10 + (c - '0');
    
    // get another character
    c = fgetc(filePointer); 
  
    /*---------------*/
    /* SKIP COMMENTS */
    /*---------------*/
    if(c == '#')
    { do 
      { c = getc(filePointer);
      } while (c != '\n' && c != '\r' && c != EOF);
      return i;
    } 
  } while (c >= '0' && c <= '9' );

  return i; 
}

/*------------------------------------------------------*/
/* THE PBM 'CONSTRUCTOR' WHICH LOADS AN IMAGE FROM FILE */
/*------------------------------------------------------*/
int load_PBM_Image(struct PBM_Image * pbmImage, char * fileName)
{ /*----------------------*/
  /* VARIABLE DECLARATION */
  /*----------------------*/

  // to read from file
  char c; bool raw = true; int bitCount;

  // forl oop variables
  int row, col;

  // open the file forreading
  FILE * imageFilePointer = fileOpener(READ, fileName);
  if(imageFilePointer == NULL) return -1;

  // make sure the first char is P
  if(fgetc(imageFilePointer) != 'P')
  { fclose(imageFilePointer);
    return - 1;
  }

  // make sure the second char is either a 1 or 4
  c = fgetc(imageFilePointer);
  if(c != '1' && c != '4')
  { fclose(imageFilePointer);
    return - 1;
  }

  if(c == '4') raw = true; else raw = false;

  // get the width and height of the image
  pbmImage->width = geti(imageFilePointer); 
  pbmImage->height = geti(imageFilePointer);
  if(pbmImage->width < 0 || pbmImage->height < 0)
  { fclose(imageFilePointer);
    return - 1;
  }

  // allocate memory for a COLUMN
  pbmImage->image = (unsigned char * *) 
                    calloc(pbmImage->height, sizeof(char *));
  if(pbmImage->image == (unsigned char * *)0)
  { fclose(imageFilePointer);
    return - 1;
  }

  // allocate memory for the ROWS
  for(row = 0; row < pbmImage->height; row++) 
  { pbmImage->image[row] = (unsigned char *) 
                         calloc(pbmImage->width, sizeof(char));
    if(pbmImage->image[row] == (unsigned char *)0)
    { fclose(imageFilePointer);
      return - 1;
    }
  }

  /*-------------------*/
  /* READ IN THE IMAGE */
  /*-------------------*/

  bitCount = 0;

  /*--------------*/
  /* ASCII FORMAT */
  /*--------------*/
  if(!raw)
    for(row = 0; row < pbmImage->height; row++)
      for(col = 0; col < pbmImage->width; col++) 
      { c = fgetc(imageFilePointer);
        while ((c == '\n') || (c == ' ') || (c == '\t')) c = fgetc(imageFilePointer);
        pbmImage->image[row][col] = c  - '0'; 
      }

  /*------------*/
  /* RAW FORMAT */
  /*------------*/
  if(raw)
    for(row = 0; row < pbmImage->height; row++)
      for(col = 0; col < pbmImage->width; col++)
      { // every 8 bits, read in another character
        if(bitCount == 0)
        { c = fgetc(imageFilePointer);
          bitCount = 8;
        }

        // get a bit from c
        pbmImage->image[row][col] = (c >> --bitCount) & 1;
      }

  // success

  fclose(imageFilePointer);

  return 0; 
}

/*-------------------------------------------------*/
/* THE PBM 'CONSTRUCTOR' WHICH CREATES A NEW IMAGE */
/*-------------------------------------------------*/
int create_PBM_Image(struct PBM_Image * pbmImage, int width, int height)
{ // for loop variable
  int row;

  // initialize the width and height of the image
  pbmImage->width = width; pbmImage->height = height;
  if(pbmImage->width < 0 || pbmImage->height < 0) return - 1;

  // allocate memory for a COLUMN
  pbmImage->image = (unsigned char * *)
                    calloc(pbmImage->height, sizeof(char *));
  if(pbmImage->image == (unsigned char * *)0) return -1;

  // allocate memory for the ROWS
  for(row = 0; row < pbmImage->height; row++) 
  { pbmImage->image[row] = (unsigned char *)
                         calloc(pbmImage->width, sizeof(char));
    if(pbmImage->image[row] == (unsigned char *)0) return -1;
  }

  // success
  return 0; 
}

/*--------------------------------------*/
/* FREES MEMORY CONSUMED BY A PBM IMAGE */
/*--------------------------------------*/
void free_PBM_Image(struct PBM_Image * pbmImage)
{ // free the ROWS
  int row;
  for(row = 0; row < pbmImage->height; row++) 
    free(pbmImage->image[row]);
 
  // free the COLUMN
  free(pbmImage->image);
}

/*-----------------------------*/
/* SAVES THE PBM IMAGE TO FILE */
/*-----------------------------*/
int save_PBM_Image(struct PBM_Image * pbmImage, char * fileName, bool raw)
{ /*----------------------*/
  /* VARIABLE DECLARATION */
  /*----------------------*/

  // for loop variables
  int row, col;

  // for writing raw bits to file
  unsigned char c; int bitCount;

  // the file to save to
  FILE * imageFilePointer = fileOpener(WRITE, fileName);
  if(imageFilePointer == NULL) return - 1;

  // write the header
  if(!raw) 
    fprintf(imageFilePointer, "P1\n%d %d\n", pbmImage->width, pbmImage->height);
  else 
    fprintf(imageFilePointer, "P4\n%d %d\n", pbmImage->width, pbmImage->height);

  /*-----------------*/
  /* WRITE THE IMAGE */
  /*-----------------*/

  /*--------------*/
  /* ASCII FORMAT */
  /*--------------*/
  if(!raw)
    for(row = 0; row < pbmImage->height; row++)
      for(col = 0; col < pbmImage->width; col++)
        fprintf(imageFilePointer, "%d ", pbmImage->image[row][col]);

  /*------------*/
  /* RAW FORMAT */
  /*------------*/
  if(raw)
    for(row = 0; row < pbmImage->height; row++)
    { // reset the char
      c = 0; bitCount = 0;

      for(col = 0; col < pbmImage->width; col++)
      { if(pbmImage->image[row][col] == 1) c += (1 << (7 - bitCount));
        if(++bitCount == 8) 
        { fputc(c, imageFilePointer); 
          c = 0; bitCount = 0; 
        } 
      }

      // send the last few bits
      if(bitCount != 0 && raw) fputc(c, imageFilePointer); 
     }

  fclose(imageFilePointer);

  return 0; 
}

/*------------------------------------------------------*/
/* THE PGM 'CONSTRUCTOR' WHICH LOADS AN IMAGE FROM FILE */
/*------------------------------------------------------*/
int load_PGM_Image(struct PGM_Image * pgmImage, char * fileName)
{ /*----------------------*/
  /* VARIABLE DECLARATION */
  /*----------------------*/

  // to read from file
  char c; bool raw;

  // for loop variables
  int row, col;

  // open the file forreading
  FILE * imageFilePointer = fileOpener(READ, fileName);
  if(imageFilePointer == NULL) return -1;

  // make sure the first char is P
  if(fgetc(imageFilePointer) != 'P')
  { fclose(imageFilePointer);
    return - 1;
  }

  // make sure the second char is either a 2 or 5
  c = fgetc(imageFilePointer);
  if(c != '2' && c != '5')
  { fclose(imageFilePointer);
    return - 1;
  }

  if(c == '5') raw = true; else raw = false;

  // get the width, height and max gray value of the image
  pgmImage->width = geti(imageFilePointer); 
  pgmImage->height = geti(imageFilePointer);
  pgmImage->maxGrayValue = geti(imageFilePointer);
  
  if(pgmImage->width < 0 || pgmImage->height < 0 || 
      pgmImage->maxGrayValue < 0)
  { fclose(imageFilePointer);
    return - 1;
  }

  if(pgmImage->maxGrayValue > 255) pgmImage->maxGrayValue = 255;

  // allocate memory for a COLUMN
  pgmImage->image = (unsigned char * *) 
                    calloc(pgmImage->height, sizeof(char *));
  if(pgmImage->image == (unsigned char * *)0)
  { fclose(imageFilePointer);
    return - 1;
  }

  // allocate memory for the ROWS
  for(row = 0; row < pgmImage->height; row++)
  { pgmImage->image[row] = (unsigned char *) 
                         calloc(pgmImage->width, sizeof(char));
    if(pgmImage->image[row] == (unsigned char *)0)
    { fclose(imageFilePointer);
      return - 1;
    }
  }

  /*-------------------*/
  /* READ IN THE IMAGE */
  /*-------------------*/

  /*--------------*/
  /* ASCII FORMAT */
  /*--------------*/
  if(!raw)
    for(row = 0; row < pgmImage->height; row++)
      for(col = 0; col < pgmImage->width; col++)
        pgmImage->image[row][col] = geti(imageFilePointer);

  /*------------*/
  /* RAW FORMAT */
  /*------------*/
  if(raw)
    for(row = 0; row < pgmImage->height; row++)
      for(col = 0; col < pgmImage->width; col++)
        pgmImage->image[row][col] = getc(imageFilePointer);

  // success
  fclose(imageFilePointer);

  return 0; 
}

/*-------------------------------------------------*/
/* THE PGM 'CONSTRUCTOR' WHICH CREATES A NEW IMAGE */
/*-------------------------------------------------*/
int create_PGM_Image(struct PGM_Image * pgmImage, 
                     int width, int height, int maxGrayValue)
{ // for loop variables
  int row;

  // initialize the width, height and max gray value of the image
  pgmImage->width = width; 
  pgmImage->height = height;
  pgmImage->maxGrayValue = maxGrayValue;
  
  if(pgmImage->width<0 || pgmImage->height<0 || pgmImage->maxGrayValue<0) 
    return - 1;

  if(pgmImage->maxGrayValue > 255) 
    pgmImage->maxGrayValue = 255;

  // allocate memory for a COLUMN
  pgmImage->image = (unsigned char * *)
                    calloc(pgmImage->height, sizeof(char *));

  if(pgmImage->image == (unsigned char * *)0) return -1;

  // allocate memory for the ROWS
  for(row = 0; row < pgmImage->height; row++)
  { pgmImage->image[row] = (unsigned char *)
                         calloc(pgmImage->width, sizeof(char));
    if(pgmImage->image[row] == (unsigned char *)0) return -1;
  } 

  // success
  return 0;
}

/*--------------------------------------*/
/* FREES MEMORY CONSUMED BY A PGM IMAGE */
/*--------------------------------------*/
void free_PGM_Image(struct PGM_Image * pgmImage)
{ // free the ROWS
  int row;
  for(row = 0; row < pgmImage->height; row++)
    free(pgmImage->image[row]);

  // free the COLUMN
  free(pgmImage->image); 
}

/*-----------------------------*/
/* SAVES THE PGM IMAGE TO FILE */
/*-----------------------------*/
int save_PGM_Image(struct PGM_Image * pgmImage, char * fileName, bool raw)
{ /*----------------------*/
  /* VARIABLE DECLARATION */
  /*----------------------*/

  // for loop variables
  int row, col;

  // the file to save to
  FILE * imageFilePointer = fileOpener(WRITE, fileName);
  if(imageFilePointer == NULL) return - 1;

  // write the header
  if(!raw) 
    fprintf(imageFilePointer, "P2\n%d %d\n%d\n",
            pgmImage->width, pgmImage->height, pgmImage->maxGrayValue);
  else
    fprintf(imageFilePointer, "P5\n%d %d\n%d\n",
            pgmImage->width, pgmImage->height, pgmImage->maxGrayValue);

  /*-----------------*/
  /* WRITE THE IMAGE */
  /*-----------------*/

  /*--------------*/
  /* ASCII FORMAT */
  /*--------------*/
  if(!raw)
    for(row = 0; row < pgmImage->height; row++)
      for(col = 0; col < pgmImage->width; col++)
        fprintf(imageFilePointer, "%d ", pgmImage->image[row][col]);

  /*------------*/
  /* RAW FORMAT */
  /*------------*/
  if(raw)
    for(row = 0; row < pgmImage->height; row++)
      for(col = 0; col < pgmImage->width; col++)
        fputc(pgmImage->image[row][col], imageFilePointer);

  fclose(imageFilePointer);

  return 0;
}

/*------------------------------------------------------*/
/* THE PPM 'CONSTRUCTOR' WHICH LOADS AN IMAGE FROM FILE */
/*------------------------------------------------------*/
int load_PPM_Image(struct PPM_Image * ppmImage, char * fileName)
{ /*----------------------*/
  /* VARIABLE DECLARATION */
  /*----------------------*/

  // to read from file
  char c; bool raw;

  // for loop variables
  int row, col; enum Color color;

  // open the file forreading
  FILE * imageFilePointer = fileOpener(READ, fileName);
  if(imageFilePointer == NULL)
  { return - 1;
  }

  // make sure the first char is P
  if(fgetc(imageFilePointer) != 'P')
  { fclose(imageFilePointer);
    return - 1;
  }

  // make sure the second char is either a 3 or 6
  c = fgetc(imageFilePointer);
  if(c != '3' && c != '6')
  { fclose(imageFilePointer);
    return - 1;
  }

  if(c == '6') raw = true; else raw = false;

  // get the width, height and max gray value of the image
  ppmImage->width = geti(imageFilePointer); 
  ppmImage->height = geti(imageFilePointer);
  ppmImage->maxGrayValue = geti(imageFilePointer);
  
  if(ppmImage->width < 0 || ppmImage->height < 0 || 
      ppmImage->maxGrayValue < 0)
  { fclose(imageFilePointer);
    return - 1;
  }

  if(ppmImage->maxGrayValue > 255) ppmImage->maxGrayValue = 255;

  // allocate memory for a COLUMN
  ppmImage->image = (unsigned char * * *)
                     calloc(ppmImage->height, sizeof(char * *));
  if(ppmImage->image == (unsigned char * * *)0)
  { fclose(imageFilePointer);
    return - 1;
  }

  // allocate memory for the ROWS
  for(row = 0; row < ppmImage->height; row++) 
  { ppmImage->image[row] = (unsigned char * *) 
                         calloc(ppmImage->width, sizeof(char *));
    if(ppmImage->image[row] == (unsigned char * *)0)
    { fclose(imageFilePointer);
      return - 1;
    }
  }

  // allocate memory for the pixels
  for(row = 0; row < ppmImage->height; row++)
    for(col = 0; col < ppmImage->width; col++)
    { ppmImage->image[row][col] = (unsigned char *) calloc(3, sizeof(char));
      if(ppmImage->image[row][col] == (unsigned char *)0)
      { fclose(imageFilePointer);
        return - 1;
      }
    }

  /*-------------------*/
  /* READ IN THE IMAGE */
  /*-------------------*/

  /*--------------*/
  /* ASCII FORMAT */
  /*--------------*/
  if(!raw)
    for(row = 0; row < ppmImage->height; row++)
      for(col = 0; col < ppmImage->width; col++)
        for(color = RED; color <= BLUE; color++)
          ppmImage->image[row][col][color] = geti(imageFilePointer);

  /*------------*/
  /* RAW FORMAT */
  /*------------*/
  if(raw)
    for(row = 0; row < ppmImage->height; row++)
      for(col = 0; col < ppmImage->width; col++)
        for(color = RED; color <= BLUE; color++)
          ppmImage->image[row][col][color] = getc(imageFilePointer);

  // success
  fclose(imageFilePointer);

  return 0; 
}

/*-------------------------------------------------*/
/* THE PPM 'CONSTRUCTOR' WHICH CREATES A NEW IMAGE */
/*-------------------------------------------------*/
int create_PPM_Image(struct PPM_Image * ppmImage,
                     int width, int height, int maxGrayValue)
{ // for loop variables
  int row, col;

  // get the width, height and max gray value of the image
  ppmImage->width = width; 
  ppmImage->height = height; 
  ppmImage->maxGrayValue = maxGrayValue;
  
  if(ppmImage->width < 0 || ppmImage->height < 0 || ppmImage->maxGrayValue < 0)
    return - 1;

  if(ppmImage->maxGrayValue > 255) ppmImage->maxGrayValue = 255;

  // allocate memory for a COLUMN
  ppmImage->image = (unsigned char * * *)
                    calloc(ppmImage->height, sizeof(char * *));
  if(ppmImage->image == (unsigned char * * *)0) return -1;

  // allocate memory for the ROWS
  for(row = 0; row < ppmImage->height; row++) 
  { ppmImage->image[row] = (unsigned char * *) 
                         calloc(ppmImage->width, sizeof(char *));
    if(ppmImage->image[row] == (unsigned char * *)0) return -1; 
  }

  // allocate memory for the pixels
  for(row = 0; row < ppmImage->height; row++)
    for(col = 0; col < ppmImage->width; col++)
    { ppmImage->image[row][col] = (unsigned char *) calloc(3, sizeof(char));
      if(ppmImage->image[row][col] == (unsigned char *)0) return -1; 
    } 
  
  // success
  return 0; 
}

/*--------------------------------------*/
/* FREES MEMORY CONSUMED BY A PPM IMAGE */
/*--------------------------------------*/
void free_PPM_Image(struct PPM_Image * ppmImage)
{ // forl oop variables
  int row, col;

  // free the pixels
  for(row = 0; row < ppmImage->height; row++)
     for(col = 0; col < ppmImage->width; col++)
        free(ppmImage->image[row][col]);

  // free the ROWS
  for(row = 0; row < ppmImage->height; row++)
     free(ppmImage->image[row]);

  // free the COLUMN
  free(ppmImage->image);
}

/*-----------------------------*/
/* SAVES THE PPM IMAGE TO FILE */
/*-----------------------------*/
int save_PPM_Image(struct PPM_Image * ppmImage, char * fileName, bool raw)
{ /*----------------------*/
  /* VARIABLE DECLARATION */
  /*----------------------*/

  // forl oop variables
  int row, col; enum Color color;

  // the file to save to
  FILE * imageFilePointer = fileOpener(WRITE, fileName);
  if(imageFilePointer == NULL) return - 1;

  // write the header
  if(!raw)
    fprintf(imageFilePointer, "P3\n%d %d\n%d\n",
            ppmImage->width, ppmImage->height, ppmImage->maxGrayValue);
  else
    fprintf(imageFilePointer, "P6\n%d %d\n%d\n",
            ppmImage->width, ppmImage->height, ppmImage->maxGrayValue);

  /*-----------------*/
  /* WRITE THE IMAGE */
  /*-----------------*/

  /*--------------*/
  /* ASCII FORMAT */
  /*--------------*/
  if(!raw)
    for(row = 0; row < ppmImage->height; row++)
      for(col = 0; col < ppmImage->width; col++)
        for(color = RED; color <= BLUE; color++)
          fprintf(imageFilePointer, "%d ", ppmImage->image[row][col][color]);

  /*------------*/
  /* RAW FORMAT */
  /*------------*/
  if(raw)
    for(row = 0; row < ppmImage->height; row++)
      for(col = 0; col < ppmImage->width; col++)
        for(color = RED; color <= BLUE; color++)
          fputc(ppmImage->image[row][col][color], imageFilePointer);

  fclose(imageFilePointer);

  return 0; 
}

/*-----------------------------------*/
/* COPIES A PBM IMAGE TO A PGM IMAGE */
/*-----------------------------------*/
int copy_PBM_to_PGM(struct PBM_Image * pbmImage, struct PGM_Image * pgmImage)
{ // for loop variables
  int row, col;

  // initialize the pgm image
  if(create_PGM_Image(pgmImage, pbmImage->width, 
                      pbmImage->height, MAX_GRAY_VALUE) == -1) return -1;

  // copy the values
  for(row = 0; row < pbmImage->height; row++)
    for(col = 0; col < pbmImage->width; col++)
      if(pbmImage->image[row][col] == WHITE)
        pgmImage->image[row][col] = 255;
      else 
        pgmImage->image[row][col] = 0;

  // success
  return 0; 
}

/*-----------------------------------*/
/* COPIES A PBM IMAGE TO A PPM IMAGE */
/*-----------------------------------*/
int copy_PBM_to_PPM(struct PBM_Image * pbmImage, struct PPM_Image * ppmImage) 
{ // for loop variables
  int row, col; enum Color color;

  // initialize the pgm image
  if(create_PPM_Image(ppmImage, pbmImage->width, 
                      pbmImage->height, MAX_GRAY_VALUE) == -1) return -1;

  // copy the values
  for(row = 0; row < pbmImage->height; row++)
    for(col = 0; col < pbmImage->width; col++)
      for(color = RED; color <= BLUE; color++)
        if(pbmImage->image[row][col] == WHITE)
           ppmImage->image[row][col][color] = 255;
        else
           ppmImage->image[row][col][color] = 0;
  
  // success
  return 0;
}

/*-----------------------------------*/
/* COPIES A PGM IMAGE TO A PBM IMAGE */
/*-----------------------------------*/
int copy_PGM_to_PBM(struct PGM_Image * pgmImage, struct PBM_Image * pbmImage)
{ // for loop variables
  int row, col;

  // initialize the pgm image
  if(create_PBM_Image(pbmImage, pgmImage->width, pgmImage->height) == -1)
    return -1;

  // copy the values
  for(row = 0; row < pgmImage->height; row++)
    for(col = 0; col < pgmImage->width; col++)
      if(pgmImage->image[row][col] >= (pgmImage->maxGrayValue / 2))
        pbmImage->image[row][col] = WHITE;
      else
        pbmImage->image[row][col] = BLACK;

  // success
  return 0; 
}

/*-----------------------------------*/
/* COPIES 3 PGM IMAGES TO A PPM IMAGE */
/*-----------------------------------*/
int copy_3_PGM_to_PPM(struct PGM_Image * pgmImage_R,
          struct PGM_Image * pgmImage_G,
          struct PGM_Image * pgmImage_B,
          struct PPM_Image * ppmImage)
{ // forloop variables
  int row, col; enum Color color;

  if((pgmImage_R->width != pgmImage_G->width) ||
      (pgmImage_R->width != pgmImage_B->width) ||
      (pgmImage_R->height != pgmImage_G->height) ||
      (pgmImage_R->height != pgmImage_B->height) ||
      (pgmImage_R->maxGrayValue != pgmImage_G->maxGrayValue) ||
      (pgmImage_R->maxGrayValue != pgmImage_B->maxGrayValue))
      return -1;

  // initialize the ppm image
  if(create_PPM_Image(ppmImage, pgmImage_R->width, pgmImage_R->height,
                      pgmImage_R->maxGrayValue) == -1)
    return -1;

  // copy the values
  for(row = 0; row < pgmImage_R->height; row++)
     for(col = 0; col < pgmImage_R->width; col++)
           for(color = RED; color <= BLUE; color++)
     {  ppmImage->image[row][col][RED]   = pgmImage_R->image[row][col];
        ppmImage->image[row][col][GREEN] = pgmImage_G->image[row][col];
        ppmImage->image[row][col][BLUE]  = pgmImage_B->image[row][col];
     }

  // success
  return 0; 
}

/*-----------------------------------*/
/* COPIES A PGM IMAGE TO A PPM IMAGE */
/*-----------------------------------*/
int copy_PGM_to_PPM(struct PGM_Image * pgmImage, struct PPM_Image * ppmImage)
{ // for loop variables
  int row, col; enum Color color;

  // initialize the pgm image
  if(create_PPM_Image(ppmImage, pgmImage->width, 
                      pgmImage->height, pgmImage->maxGrayValue) == -1)
    return -1;

  // copy the values
  for(row = 0; row < pgmImage->height; row++)
    for(col = 0; col < pgmImage->width; col++)
      for(color = RED; color <= BLUE; color++)
        ppmImage->image[row][col][color] = pgmImage->image[row][col];

  // success
  return 0; 
}

/*-----------------------------------*/
/* COPIES A PPM IMAGE TO A PBM IMAGE */
/*-----------------------------------*/
int copy_PPM_to_PBM(struct PPM_Image * ppmImage, 
                    struct PBM_Image * pbmImage, enum Color color)
{ // for loop variables
  int row, col;

  // initialize the pgm image
  if(create_PBM_Image(pbmImage, ppmImage->width, ppmImage->height) == -1)
    return -1;

  // copy the values
  for(row = 0; row < ppmImage->height; row++)
    for(col = 0; col < ppmImage->width; col++)
      if(ppmImage->image[row][col][color] >= (ppmImage->maxGrayValue / 2))
        pbmImage->image[row][col] = WHITE;
      else
        pbmImage->image[row][col] = BLACK;

  // success
  return 0; 
}

/*-----------------------------------*/
/* COPIES A PPM IMAGE TO A PGM IMAGE */
/*-----------------------------------*/
int copy_PPM_to_PGM(struct PPM_Image * ppmImage,
                    struct PGM_Image * pgmImage, enum Color color)
{ // for loop variables
  int row, col;

  // initialize the pgm image
  if(create_PGM_Image(pgmImage, ppmImage->width,
                      ppmImage->height, ppmImage->maxGrayValue) == -1)
    return -1;

  // copy the values
  for(row = 0; row < ppmImage->height; row++)
    for(col = 0; col < ppmImage->width; col++)
      pgmImage->image[row][col] = ppmImage->image[row][col][color];

  // success
  return 0; 
}

/*-----------------------------------------------------------*/
/* CONVERTS A PPM IMAGE TO A PGM IMAGE USING THE Y COMPONENT */
/*-----------------------------------------------------------*/
int convert_PPM_to_PGM(struct PPM_Image * ppmImage,
                       struct PGM_Image * pgmImage)
{ // for loop variables
  int row, col;

  // initialize the pgm image
  if(create_PGM_Image(pgmImage, ppmImage->width,
                      ppmImage->height, ppmImage->maxGrayValue) == -1)
    return -1;

  // copy the values
  for(row = 0; row < ppmImage->height; row++)
    for(col = 0; col < ppmImage->width; col++)
      pgmImage->image[row][col] = (unsigned char)
                 ( (0.299 * ppmImage->image[row][col][RED]) 
                 + (0.587 * ppmImage->image[row][col][GREEN]) 
                 + (0.114 * ppmImage->image[row][col][BLUE]));

  // success
  return 0; 
}

/*-----------------------------------------------------------*/
/* CONVERTS A PPM IMAGE TO A PGM IMAGE USING AVERAGE */
/*-----------------------------------------------------------*/
int convert_PPM_to_PGM_using_average(struct PPM_Image * ppmImage,
                                     struct PGM_Image * pgmImage)
{ // for loop variables
  int row, col;

  // initialize the pgm image
  if(create_PGM_Image(pgmImage, ppmImage->width,
                      ppmImage->height, ppmImage->maxGrayValue) == -1)
    return -1;

  // copy the values
  for(row = 0; row < ppmImage->height; row++)
    for(col = 0; col < ppmImage->width; col++)
      pgmImage->image[row][col] = (unsigned char)
                                ( (ppmImage->image[row][col][RED]  / 3.0)
                                + (ppmImage->image[row][col][GREEN]/ 3.0)
                                + (ppmImage->image[row][col][BLUE] / 3.0)
                                );

  // success
  return 0; 
}

/*--------------------*/
/* COPIES A PBM IMAGE */
/*--------------------*/
int copy_PBM(struct PBM_Image * pbmImage, struct PBM_Image * copy)
{ // for loop variables
  int row, col;

  // initialize the copy
  if(create_PBM_Image(copy, pbmImage->width, pbmImage->height) == -1)
    return -1;

  // copy the values
  for(row = 0; row < pbmImage->height; row++)
    for(col = 0; col < pbmImage->width; col++)
      copy->image[row][col] = pbmImage->image[row][col];

  // success
  return 0; 
}

/*--------------------*/
/* COPIES A PGM IMAGE */
/*--------------------*/
int copy_PGM(struct PGM_Image * pgmImage, struct PGM_Image * copy)
{ // for loop variables
  int row, col;

  // initialize the copy
  if(create_PGM_Image(copy, pgmImage->width,
                      pgmImage->height, pgmImage->maxGrayValue) == -1)
    return -1;

  // copy the values
  for(row = 0; row < pgmImage->height; row++)
    for(col = 0; col < pgmImage->width; col++)
      copy->image[row][col] = pgmImage->image[row][col];

  // success
  return 0; 
}

/*--------------------*/
/* COPIES A PPM IMAGE */
/*--------------------*/
int copy_PPM(struct PPM_Image * ppmImage, struct PPM_Image * copy)
{ // for loop variables
  int row, col; enum Color color;

  // initialize the copy
  if(create_PPM_Image(copy, ppmImage->width,
                      ppmImage->height, ppmImage->maxGrayValue) == -1)
    return -1;

  // copy the values
  for(row = 0; row < ppmImage->height; row++)
    for(col = 0; col < ppmImage->width; col++)
      for(color = RED; color <= BLUE; color++)
        copy->image[row][col][color] = ppmImage->image[row][col][color];

  // success
  return 0; 
}

