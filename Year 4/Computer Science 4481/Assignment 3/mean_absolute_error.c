/*
 * CS4481B Assignment 3
 * Name: Jameel Kaba
 * UWO/GAUL ID: jkaba
 * student #: 250796017
 */

// Include header file
#include "mean_absolute_error.h"

// mean_absolute_error calculates the mean absolute error between 2 images
float mean_absolute_error(char *file_name_1_ptr, char *file_name_2_ptr){
    
    // Initialize variables
    struct PGM_Image pic1;
    struct PGM_Image pic2;
    int p1 = load_PGM_Image(&pic1, file_name_1_ptr);
    int p2 = load_PGM_Image(&pic2, file_name_2_ptr);
    
    // If the image could not be loaded, return with -1
    if(p1 == -1 || p2 == -1){
        return -1;
    }
    
    // If the image height's and width's are not the same return -1
    if(pic1.height != pic2.height || pic1.width != pic2.width){
        return -1;
    }
    
    // Initial scale
    int scale= 1;
    
    // If the max gray values are not the same scaling is needed
    
    // If the first gray value is larger
    if(pic1.maxGrayValue > pic2.maxGrayValue){
        
        // Scale is pic1 gray / pic2 gray to have smaller match bigger
        scale =  pic1.maxGrayValue / pic2.maxGrayValue;
        pic2.maxGrayValue *= scale;
    }
    
    // If the second gray is larger
    else if(pic1.maxGrayValue < pic2.maxGrayValue){
        
        // Scale is pic2 gray / pic1 gray to have smaller match bigger
        scale =  pic2.maxGrayValue / pic1.maxGrayValue;
        pic1.maxGrayValue *= scale;
    }
    
    // Algorithm calculations
    // Key functionality is based on equation on slide 28 of topic 2
    
    // array to contain error values, needs to be same size as the images
    int *error = malloc((pic1.width * pic2.height)*sizeof(int));
    
    int i = 0;
    
    // Loop through the picture
    for (int row = 0; row < pic1.height; row++){
        for (int col = 0; col < pic1.width; col++){
            
            // If pic2 gray value is larger, apply scaling to pic1
            if(pic1.maxGrayValue > pic2.maxGrayValue){
                
                // |(f(x,y)*scale) - f'(x,y)|
                error[i] = abs((int) (pic1.image[row][col] - (pic2.image[row][col]*scale)));
            }
            
            // If pic1 gray value is larger, apply scaling to pic2
            else if(pic1.maxGrayValue < pic2.maxGrayValue){
                
                // |f(x,y) = (f'(x,y)*scale)|
                error[i] = abs((int) ((pic1.image[row][col]*scale) - pic2.image[row][col]));
            }
            
            // Max gray values are equal, so perform calculation as normal
            else{
                
                // |f(x,y) - f'(x,y)|
                error[i] = abs((int) ((pic1.image[row][col]) - pic2.image[row][col]));
            }
            
            // Increment summation counter
            i++;
            
        }
    }
    
    // Loop through the errors, sum them together *summation part of equation*
    long int total = 0;
    
    for(i = 0; i < (pic1.width * pic2.height); i++){
        total += error[i];
    }
    
    // Calculate and return MAE by dividing total over width x height
    return (float) total / (pic1.width * pic2.height);
}
