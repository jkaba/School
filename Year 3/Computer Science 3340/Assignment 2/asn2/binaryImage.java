/**
 * Name: Jameel Kaba
 * Student#: 250796017
 * UWO ID: jkaba
 * CS3340b Assignment 2
 * Question 10b
 */

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Arrays;

public class binaryImage{
    
    public static void main(String[] args){
        
        // Initialize variables
        int[][] image = null;
        boolean[][] flag = null;
        int[] sets = null;
        int[] chars = null;
        
        // Load the image
        try {
            
            // Get the file from input
            BufferedReader input = new BufferedReader(new InputStreamReader(System.in));
            
            // Set up image and flag arrays
            image = new int[71][71];
            flag = new boolean[71][71];
            
            String string;
            
            // Read through each line; for each + image to 1 and flag to true
            for(int i = 0; input.ready(); i++){
                string = input.readLine();
                for(int j = 0; j < string.length(); j++){
                    if(string.charAt(j) == '+'){
                        image[i][j] = 1;
                        flag[i][j] = true;
                    }
                }
            }
            
            // Close the buffer
            input.close();
        }
        
        // Catch FileNotFound exception
        catch (FileNotFoundException e){
            System.out.println("File Not Found");
        }
        
        // Catch IO Exception
        catch (IOException e){
            System.out.println("Can't Read File.");
        }
        
        // Print out part 1
        for(int i = 0; i < image.length; i++){
            for(int j = 0; j < image.length; j++){
                System.out.print(image[i][j]);
            }
            System.out.println();
        }
        System.out.println();
        
        // Create the UnionFind and connect components
        uandf imageSet = new uandf(image.length * image.length + 1);
        for(int i = 0; i < image.length; i++){
            for(int j = 0; j < image.length; j++){
                if (image[i][j] == 1){
                    imageSet.makeSet((i * image.length + j) + 1);
                    if (j > 0 && image[i][j - 1] == 1){
                        imageSet.unionSets(i * image.length + (j - 1) + 1, i * image.length + j + 1);
                    }
                    if (i > 0 && image[i - 1][j] == 1){
                        imageSet.unionSets((i - 1) * image.length + j + 1, i * image.length + j + 1);
                    }
                }
            }
        }
        
        sets = new int[imageSet.finalSets()];
        chars = new int[sets.length];
        
        // Print part 2
        int k;
        for(int i = 0; i < image.length; i++){
            for(int j = 0; j < image.length; j++){
                
                // Assign a character to k
                k = imageSet.findSet(i * image.length + j + 1) + 96;
                
                // If k is 96, then remove/print space
                if (k == 96){
                    System.out.print(' ');
                }
                else{
                    
                    // Print out the character and increment set
                    System.out.print((char)k);
                    sets[k - 97]++;
                }
            }
            System.out.println();
        }
        System.out.println();
        
        // Sort the lists for part 3
        int[] sortedSets = new int[sets.length];
        for(int i = 0; i < sets.length; i++){
            sortedSets[i] = sets[i];
        }
        for(int i = 0; i < sortedSets.length; i++){
            chars[i] = sortedSets[i];
        }
        Arrays.sort(sortedSets);
        
        // Print part 3
        for(int i = 0; i < sortedSets.length; i++){
            for(int j = 0; j < chars.length; j++){
                if(sortedSets[i] == chars[j]){
                    
                    // Print out the character and it's size
                    System.out.println((char)(j + 97) + "\t  \t" + sortedSets[i]);
                    chars[j] = -1;
                    break;
                }
            }
        }
        System.out.println();
        
        // Print part 4
        for (int i = 0; i < image.length; i++) {
            for (int j = 0; j < image.length; j++) {
                
                // Assign the character to k
                k = imageSet.findSet(i * image.length + j + 1) + 96;
                
                // If size is 1 or 2 then remove it
                if (k == 96 || sets[k - 97] == 1 || sets[k - 97] == 2){
                    System.out.print(' ');
                }
                
                // Otherwise print out the character
                else
                    System.out.print((char)k);
            }
            System.out.println();
        }
        System.out.println();
    }
}
