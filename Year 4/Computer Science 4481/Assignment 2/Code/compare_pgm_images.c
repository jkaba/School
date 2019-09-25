/*
 * CS4481B Assignment 2
 * Name: Jameel Kaba
 * UWO/GAUL ID: jkaba
 * student #: 250796017
 */

// Include the header for question 7
#include "mean_absolute_error.h"

// compare_pgm_images runs the program written in question 7 to
// compare whether or not 2 images are the same
int main(int argc, char *argv[]){
    
    // If there are too many or not enough images, return an error
    if(argc != 3){
        
        // Message to let the user know what arguments are needed
        printf("Error: This program requires two arguments\n");
        printf("1: The First input image filename used for comparison\n");
        printf("2: The Second input image filename used for comparison\n");
        
        // Stop the program as there was an error
        return 0;
    }
    
    // Calculate the mean absolute error, using the program from q7
    float MAE = mean_absolute_error(argv[1], argv[2]);
    
    // If the result was -1, then there was an error and an appropriate message is displayed
    if(MAE == -1){
        printf("Error: Please ensure that the input files exist and are of the same size and type\n");
    }
    
    // If not, then the MAE was calculated and is printed
    else{
        printf("The MAE between these two images is %f\n", MAE);
    }
    
    // return 0 to end program
    return 0;
}
