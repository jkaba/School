/*
 * CS4481B Assignment 3
 * Name: Jameel Kaba
 * UWO/GAUL ID: jkaba
 * student #: 250796017
 */

// Include headers
#include "libpnm.h"
#include <string.h>
#include <math.h>
#include <time.h>

// Function prototypes
void Encode_Using_LZ77(char *in_PGM_filename_Ptr, unsigned int searching_buffer_size, float *avg_offset_Ptr, float *std_offset_Ptr, float *avg_length_Ptr, float *std_length_Ptr);

// Used to obtain the 3 parts to a token for LZ 77
int Tokenizer(int *current_length, int max_length, unsigned char *imagePointer,long int arrayLength,long int counter, int *offset_val, int *length_val, unsigned char *next_symbol_val);
