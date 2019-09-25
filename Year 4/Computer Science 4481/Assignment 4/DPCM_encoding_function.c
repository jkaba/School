/*
 * CS4481B Assignment 4
 * Name: Jameel Kaba
 * UWO/GAUL ID: jkaba
 * student #: 250796017
 */

// Include header file
#include "DPCM_encoding_function.h"

// Encoding function to encode an image passed in as parameter
void Encode_Using_DPCM(char *in_PGM_filename_Ptr, int prediction_rule, float *avg_abs_error_Ptr, float *std_abs_error_ptr){
    
    // Get the image to be encoded
    struct PGM_Image pgmPic;
    load_PGM_Image(&pgmPic, in_PGM_filename_Ptr);
    
    // Determine how long of an array will be needed
    long int imageLength = pgmPic.width*pgmPic.height;
    
    // Counter used for positioning in the array
    int counter = 0;
    
    // Array's used for encoding
    int offset_array[imageLength];
    int calic[imageLength];
    
    // counters used for determining encoded value in calic
    int c = 0;
    int t = 0;
    
    // MAIN LOOP
    
    // This loop performs the DPCM Predictions and stores the error values
    for(int i = 0; i < pgmPic.height; i++){
        for(int j = 0; j < pgmPic.width; j++){
            
            // First pixel, prediction is 128
            if(i == 0 && j == 0){
                offset_array[counter] = pgmPic.image[i][j] - 128;
                counter++;
            }
            
            // Remainder of first row, prediction is W
            else if(i == 0 && j != 0){
                offset_array[counter] = pgmPic.image[i][j] - pgmPic.image[i][j-1];
                counter++;
            }
            
            // Second row, prediction is N
            else if(i == 1){
                offset_array[counter] = pgmPic.image[i][j] - pgmPic.image[i-1][j];
                counter++;
            }
            
            // Third row until end of image
            else{
                
                // First, Second, or Last column, prediction is N
                if(j == 0 || j == 1 || j == pgmPic.width){
                    offset_array[counter] = pgmPic.image[i][j] - pgmPic.image[i-1][j];
                    counter++;
                }
                
                // Prediction Rule 1, prediction is W
                else if(prediction_rule == 1){
                    offset_array[counter] = pgmPic.image[i][j] - pgmPic.image[i][j-1];
                    counter++;
                }
                
                // Prediction Rule 2, prediction is N
                else if(prediction_rule == 2){
                    offset_array[counter] = pgmPic.image[i][j] - pgmPic.image[i-1][j];
                    counter++;
                }
                
                // Prediction Rule 3, Prediction is (W/2 + N/2)
                else if(prediction_rule == 3){
                    offset_array[counter] = pgmPic.image[i][j] - ((pgmPic.image[i][j-1]/2) + pgmPic.image[i-1][j]/2);
                    counter++;
                }
                
                // Prediction Rule 4, CALIC
                else if(prediction_rule == 4){
                    
                    // Initial Setup and getting surrounding pixels
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
                    
                    // Surrounding pixels stored in an array
                    int directions[7] = {w, ww, n, nw, ne, nn, nne};
                    
                    // Loop to determine whether binary or continuous mode
                    for(int a = 0; a < 7; a++){
                        if(directions[0] != directions[a]){
                            if(t == 0){
                                s1 = directions[a];
                                t++;
                            }
                        }
                    }
                    
                    // Second Loop, to determine if binary or continuous mode
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
                    
                    // If pixel matches s0, and we're in binary
                    if(pgmPic.image[i][j] == s0 && t != 2){
                        
                        // Encode pixel as 0
                        offset_array[counter] = 0;
                    }
                    
                    // If pixel matches s1, and we're in binary
                    else if (pgmPic.image[i][j] == s1 && t != 2){
                        
                        // Encode pixel as 1
                        offset_array[counter] = 1;
                    }
                    
                    // If pixel doesn't match s0 or s1, and in binary
                    else if(pgmPic.image[i][j] != s0 && pgmPic.image[i][j] != s1 && t != 2){
                        
                        // Encode as 2 (Prediction error encoded shortly)
                        calic[counter] = 2;
                        
                        // Increment counter
                        c++;
                        
                        // Set t to 2, as we're going into continuous mode
                        t = 2;
                    }
                    
                    // Continuous mode, encode the GAP Prediction Error
                    if(t == 2){
                        
                        // Calculate values for dh and dv
                        int dh = abs(w-ww) + abs(n-nw) + abs(ne-n);
                        int dv = abs(w-nw) + abs(n-nn) + abs(ne-nne);
                        
                        // If sharp horizontal edge, prediction is W
                        if(dv - dh > 80){
                            prediction = w;
                        }
                        
                        // If sharp vertical edge, prediction is N
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
                            
                            // Weak Horizontal edge
                            else if(dv - dh > 8){
                                prediction = (3/4 * prediction + 1/4 * w);
                            }
                            
                            // Weak Vertical edge
                            else if(dh - dv > 8){
                                prediction = (3/4 * prediction + 1/4 * n);
                            }
                        }
                        
                        // Encode the GAP prediction error
                        offset_array[counter] = pgmPic.image[i][j] - prediction;
                    }
                    
                    // increment counter
                    counter++;
                }
            }
        }
    }
    
    // Initialize the filenames for compressed image and .csv file
    FILE * f;
    FILE * f1;
    
    // Initialize the filenames to null
    char compressed_filename_Ptr[1024] = "\0";
    char error_csv[1024] = "\0";
    
    // Concatenate the input image filename to the 2 filenames
    strcat(compressed_filename_Ptr, in_PGM_filename_Ptr);
    strcat(error_csv, in_PGM_filename_Ptr);
    
    // Based on the prediction rule, append the according ending to the filename
    
    // Prediction rule 1
    if(prediction_rule == 1){
        strcat(compressed_filename_Ptr, ".1.DPCM");
        strcat(error_csv, ".1.errors.csv");
    }
    
    // Prediction rule 2
    else if(prediction_rule == 2){
        strcat(compressed_filename_Ptr, ".2.DPCM");
        strcat(error_csv, ".2.errors.csv");
    }
    
    // Prediction rule 3
    else if(prediction_rule == 3){
        strcat(compressed_filename_Ptr, ".3.DPCM");
        strcat(error_csv, ".3.errors.csv");
    }
    
    // Prediction rule 4
    else{
        strcat(compressed_filename_Ptr, ".4.DPCM");
        strcat(error_csv, ".4.errors.csv");
    }
    
    // Check that the files can be opened, if not then there is an error
    if (!(f = fopen(compressed_filename_Ptr, "w"))){
        
        // Print an error message and exit
        printf("Error: The compressed file could not be opened\n");
        exit(0);
    }
    if (!(f1 = fopen(error_csv, "w"))){
        
        // Print an error message and exit
        printf("Error: The offset.csv file could not be opened\n");
        exit(0);
    }
    
    // Combine the 2 arrays, to get 1 total array for encoding
    int total[counter+c];
    int sec = 0;
    
    // Loop to combine the arrays
    for(int i=0; i <= counter; i++){
        // If calic was encoded as 2, then place 2 in array followed by GAP
        if(calic[i] == 2){
            total[sec] = calic[i];
            sec++;
        }
        total[sec] = offset_array[i];
        sec++;
    }
    
    // Save the header information into the compressed image
    fprintf(f, "%d\n", pgmPic.height);
    fprintf(f, "%d\n", pgmPic.width);
    fprintf(f, "%d\n", pgmPic.maxGrayValue);
    fprintf(f, "%d\n", counter+c);
    fprintf(f, "%d\n", prediction_rule);
    
    // Save the encoded pixel values
    for(int j = 0; j <= counter+c; j++){
        fprintf(f, "%d ", total[j]);
    }
    
    // Save a new line
    fprintf(f, "\n");
    
    // Close the compressed file
    fclose(f);
    
    // Calculating average and standard deviation
    
    // Initialize variables
    float avg = 0;
    float std = 0;
    
    // Calculate offset average
    for (int i = 0; i <= counter+c; i++){
        avg += abs(total[i]);
        total[i] = abs(total[i]);
    }
    avg /= counter+c;
    
    // Calculate offset standard deviation
    for(int i = 0; i <= counter+c; i++){
        std += pow(total[i] - avg, 2);
    }
    
    // Set average and standard deviation
    *avg_abs_error_Ptr = avg;
    *std_abs_error_ptr = sqrt(std/(counter+c));
    
    // Reset variables to calculate for match length
    avg = 0;
    std = 0;
    
    // Initialize variables for sorting the arrays
    int temp;
    int count = 0;
    
    // GENERIC QUICKSORT USED FOR FASTER IMPLEMENTATION
    int n = sizeof(total)/sizeof(total[0]);
    quickSort(total, 0, n-1);
    
    // Reset variables for saving into .csv
    temp = total[0];
    count = 0;
    
    // Write the data names into the .csv files
    fprintf(f1, "Prediction Error Value, Frequency\n");
    
    
    // Loop to write data into .csv files
    for(int j = 0; j <= counter+c; j++){
        
        // If temp is same as the value in array then increase frequency
        if(temp == total[j]){
            count++;
        }
        
        // Otherwise, there is a new value
        else{
            if(total[j-1] == 2){
                count += c;
            }
            // Save the previous value and it's frequency into the .csv
            fprintf(f1, "%d, %d\n", total[j-1], count);
            
            // Set temp to be current value and frequency of 1
            temp = total[j];
            count = 1;
        }
    }
    
    // Close the .csv values and finish
    fclose(f1);
}

// General partition method, used for quick sort algorithm
int partition (int arr[], int low, int high){
    
    // Setup
    int temp;
    int pivot = arr[high];
    int i = (low - 1);
    
    // Loop to compare each element, sorting when needed
    for (int j = low; j <= high- 1; j++){
        if (arr[j] <= pivot){
            i++;
            temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    
    // Swap elements and return to caller
    temp = arr[i + 1];
    arr[i+1] = arr[high];
    arr[high] = temp;
    return (i + 1);
}

// Generic Quick sort algorithm, used to improve efficiency of program
void quickSort(int arr[], int low, int high){
    if (low < high){
        
        // Calculate the partition index
        int index = partition(arr, low, high);
        
        // Split into 2 halves and sort
        quickSort(arr, low, index - 1);
        quickSort(arr, index + 1, high);
    }
}
