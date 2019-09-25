/*
 * CS4481B Assignment 4
 * Name: Jameel Kaba
 * UWO/GAUL ID: jkaba
 * student #: 250796017
 */

// Include header file
#include "DPCM_decoding_function.h"

// Decoding function, which decompresses a compressed image passed as input
void Decode_Using_DPCM(char *in_compressed_filename_Ptr){
    
    // Initialize variables for header info
    int width = 0;
    int height = 0;
    int maxGrayValue = 0;
    int arrayLength;
    int prediction_rule;
    
    // Try opening the compressed file
    FILE* file;
    if (!(file = fopen(in_compressed_filename_Ptr, "r"))){
        
        // Error with a file, print error and exit
        printf("Error: There was an error trying to open the file\n");
        exit(0);
    }
    
    // Read the header info from the compressed file
    fscanf(file, "%d", &height);
    fscanf(file, "%d", &width);
    fscanf(file, "%d", &maxGrayValue);
    fscanf(file, "%d", &arrayLength);
    fscanf(file, "%d", &prediction_rule);
    
    // Initialize a pgm image to be used for making the decompressed image
    struct PGM_Image pgmPic;
    create_PGM_Image(&pgmPic, width, height,maxGrayValue);
    
    // Create the array representing the prediction error values
    int offset_array[arrayLength];
    
    // Get all of the error values
    for (int i = 0; i <= arrayLength; i++){
        fscanf(file, "%d", &offset_array[i]);
    }
    
    // Obtained all info from the compressed file, so close it
    fclose(file);
    
    // DECODING PROCESS
    
    // Counter to be used for saving the image
    long int counter = 0;
    
    // Counter used for CALIC
    int t = 0;
    
    // Loop which does the decoding
    for(int i = 0; i < pgmPic.height; i++){
        for(int j = 0; j < pgmPic.width; j++){
            
            // If first pixel, prediction was 128
            if(i == 0 && j == 0){
                pgmPic.image[i][j] = offset_array[counter] + 128;
                counter++;
            }
            
            // If first row, prediction was W
            else if(i == 0 && j != 0){
                pgmPic.image[i][j] = offset_array[counter] + pgmPic.image[i][j-1];
                counter++;
            }
            
            // If second row, prediction was N
            else if(i == 1){
                pgmPic.image[i][j] = offset_array[counter] + pgmPic.image[i-1][j];
                counter++;
            }
            
            // Third row until end of image
            else{
                
                // If first, second, or last column, prediction was N
                if(j == 0 || j == 1 || j == pgmPic.width){
                    pgmPic.image[i][j] = offset_array[counter] + pgmPic.image[i-1][j];
                    counter++;
                }
                
                // If prediction rule was 1, then prediction was W
                else if(prediction_rule == 1){
                    pgmPic.image[i][j] = offset_array[counter] + pgmPic.image[i][j-1];
                    counter++;
                }
                
                // If prediction rule was 2, then prediction was N
                else if(prediction_rule == 2){
                    pgmPic.image[i][j] = offset_array[counter] + pgmPic.image[i-1][j];
                    counter++;
                }
                
                // If prediction rule was 3, then prediction was (W/2 + N/2)
                else if(prediction_rule == 3){
                    pgmPic.image[i][j] = offset_array[counter] + ((pgmPic.image[i][j-1]/2) + (pgmPic.image[i-1][j]/2));
                    counter++;
                }
                
                // If prediction rule was 4, then CALIC
                else if(prediction_rule == 4){
                    
                    // Initial setup, and getting surrounding pixels
                    t = 0;
                    int w = pgmPic.image[i][j-1];
                    int ww = pgmPic.image[i][j-2];
                    int n = pgmPic.image[i-1][j];
                    int nw = pgmPic.image[i-1][j-1];
                    int ne = pgmPic.image[i-1][j+1];
                    int nn = pgmPic.image[i-2][j];
                    int nne = pgmPic.image[i-2][j+1];
                    int s0 = w;
                    int s1 = 0;
                    int prediction = 0;
                    
                    // Store surrounding pixels in an array
                    int directions[7] = {w, ww, n, nw, ne, nn, nne};
                    
                    // First loop to determine whether binary or continuous mode
                    for(int a = 0; a < 7; a++){
                        if(directions[0] != directions[a]){
                            if(t == 0){
                                s1 = directions[a];
                                t++;
                            }
                        }
                    }
                    
                    // Second loop to determine if binary or continuous
                    if(t == 1){
                        for(int a = 0; a < 7; a++){
                            for(int b = a; b < 7; b++){
                                if(directions[a] != directions[b] && t != 2){
                                    if(s0 != directions[b] || s1 != directions[b]){
                                        t = 2;
                                    }
                                }
                            }
                        }
                    }
                    
                    // If encoded value is 0, and we're in binary then value is s0
                    if(offset_array[counter] == 0 && t != 2){
                        pgmPic.image[i][j] = s0;
                    }
                    
                    // If encoded value is 1, and we're in binary then value is s1
                    else if(offset_array[counter] == 1 && t != 2){
                        pgmPic.image[i][j] = s1;
                    }
                    
                    // If encoded value is 2, and we're in binary
                    else if(offset_array[counter] == 2 && t != 2){
                        
                        // Set to continuous and get GAP prediction error
                        counter++;
                        t = 2;
                    }
                    
                    // Else, we aren't in binary
                    else{
                        t = 2;
                    }
                    
                    // Continuous mode
                    if(t == 2){
                        
                        // Calculate values for dh and dv
                        int dh = abs(w-ww) + abs(n-nw) + abs(ne-n);
                        int dv = abs(w-nw) + abs(n-nn) + abs(ne-nne);
                        
                        // Sharp horizontal edge
                        if(dv - dh > 80){
                            prediction = w;
                        }
                        
                        // Sharp vertical edge
                        else if(dh - dv > 80){
                            prediction = n;
                        }
                        else{
                            
                            // Calculate prediction
                            prediction = (w+n)/2 +(ne-nw)/4;
                            
                            // Horizontal edge
                            if(dv-dh > 32){
                                prediction = (1/2 * prediction + 1/2 * w);
                            }
                            
                            // Vertical edge
                            else if(dh - dv >32){
                                prediction = (1/2 * prediction + 1/2 * n);
                            }
                            
                            // Weak horizontal edge
                            else if(dv - dh > 8){
                                prediction = (3/4 * prediction + 1/4 * w);
                            }
                            
                            // Weak vertical edge
                            else if(dh - dv > 8){
                                prediction = (3/4 * prediction + 1/4 * n);
                            }
                        }
                        
                        // Determine the value for pixel at this location
                        pgmPic.image[i][j] = offset_array[counter] + prediction;
                    }
                    // Increment counter
                    counter++;
                }
            }
        }
    }
    
    // Create decompressed picture filename
    char out_PGM_filename_Ptr[1024] = "\0";
    strcat(out_PGM_filename_Ptr, in_compressed_filename_Ptr);
    strcat(out_PGM_filename_Ptr, ".pgm");
    
    // Save the decompressed PGM image
    save_PGM_Image(&pgmPic, out_PGM_filename_Ptr, 1);
}
