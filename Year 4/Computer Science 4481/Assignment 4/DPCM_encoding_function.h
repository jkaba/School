/*
 * CS4481B Assignment 4
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
void Encode_Using_DPCM(char *in_PGM_filename_Ptr, int prediction_rule, float *avg_abs_error_Ptr, float *std_abs_error_ptr);

// Quicksort function prototypes
int partition (int arr[], int low, int high);
void quickSort(int arr[], int low, int high);
