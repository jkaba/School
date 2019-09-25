/**
 * Name: Jameel Kaba
 * Student#: 250796017
 * UWO ID: jkaba
 * CS3340b Assignment 3
 * Question 11
 * Heap class used to implement a Heap of Edges for prims
 */

public class Heap implements HeapADT{
    
    // global variables
    public Edge[] A;
    public int[] H;
    private int max;
    private int hMax;
    
    /* Heap constructor
     * Empty constructor
     * Used for initializing
     */
    public Heap(){
        
    }
    
    /*
     * heap_ini method
     * Input: An array of Edges to represent keys, int n to represent ids
     *  method initializes a heap with the array keys of n elements
     * indexed from 1 to n, where key[i] is the key of the element whose id is i
     */
    public void heap_ini(Edge keys[], int n){
        
        // Set A to reference the array of edges
        A = keys;
        
        // Set the max to be n-1
        max = n-1;
        
        // Set H to be an array of 2*max elements
        H = new int[2*max];
        
        // hMax refers to 2n-1 --> 2max - 1
        hMax = 2*max-1;
        
        // Call heapify to create the heap
        heapify();
    }
    
    /*
     * heapify method
     * method creates the heap, by sorting and rearranging the id's
     */
    private void heapify(){
        
        // for i from n to 2n-1
        for(int i = max; i <= hMax; i++){
            
            // H[i] = i - n + 1
            H[i] = i - max + 1;
        }
        
        // for i from n - 1 to 1
        for(int i = max - 1; i >= 1; i--){
            
            // if A[H[2i]] < A[H[2i+1] then H[i] = H[2i] else H[i] = H[2i+1]
            if(A[H[2*i]].getWeight() < A[H[2*i+1]].getWeight()){
                H[i] = H[2*i];
            }
            
            else{
                H[i] = H[2*i+1];
            }
        }
    }
    
    /*
     * in_heap method
     * input: the edge to check if it is in the heap
     * output: true if id is in the heap, false otherwise
     * returns true if the element whose id is id is in the heap
     */
    public boolean in_heap(Edge id){
        
        // We create an edge to use for comparison
        Edge check = new Edge(0,0,0);
        
        // loop through the array of keys
        for(int i = 0; i < A.length; i++){
            
            // check will reference the key at position i
            check  = A[i];
            
            // If the endpoints and weight of check match id return true
            if(check.u == id.u && check.v == id.v && check.weight == id.weight){
                return true;
            }
            
            // If endpoints are reversed but still match then return true
            else if (check.u == id.v && check.v == id.u && check.weight == id.weight){
                return true;
            }
        }
        
        // return false as id is not in the heap
        return false;
    }
    
    /*
     * min_key method
     * returns the minimum key of the heap
     */
    public int min_key(){
        return A[H[1]].getWeight();
    }
    
    /*
     * min_id method
     * returns the minimum id of the heap
     */
    public int min_id(){
        return H[1];
    }
    
    /*
     * key method
     * returns the key of the element whose id is id in the heap
     */
    public int key(int id){
        return A[id].getWeight();
    }
    
    /*
     * delete_min method
     * deletes the element with minimum key from the heap
     */
    public Edge delete_min(){
        
        // We create an edge to reference removed
        Edge removed = new Edge(0,0,Integer.MAX_VALUE);
        
        // Set A[0] to be the removed edge
        A[0] = removed;
        
        // We set H[H[1] + n - 1] = 0
        H[H[1] + max - 1] = 0;
        
        // We create an edge v to reference A[H[1]
        Edge v = A[H[1]];
        
        // i = floor((H[1]+n-1)/2)
        int i = (int)Math.floor((H[1]+max-1)/2);
        
        // reheapify
        while (i >=1){
            
            // if A[H[2i]] < A[H[2i+1]] then H[i] = H[2i] else H[i] = H[2i+1]
            if(A[H[2*i]].getWeight() < A[H[2*i+1]].getWeight()){
                H[i] = H[2*i];
            }
            
            else{
                H[i] = H[2*i+1];
            }
            
            // i = floor(i/2)
            i = (int)Math.floor(i/2);
        }
        
        // return the element we removed
        return v;
        
    }
    
    /*
     * decrease_key method
     * sets the key of the element whose id is id
     * to new_key if its current key is greater than new_key
     */
    public void decrease_key(int id, int new_key){
        
        // A[id] = new_key
        A[id].weight = new_key;
        
        // i = floor((id + n - 1)/2)
        int i = (int)Math.floor((id+max-1)/2);
        
        // reheapify
        while (i >=1){
            
            // if A[H[2i] < A[H[2i+1] then H[i] = H[2i] else H[i] = H[2i+1]
            if (A[H[2*i]].weight < A[H[2*i+1]].weight){
                H[i] = H[2*i];
            }
            
            else{
                H[i] = H[2*i+1];
            }
            
            // i = floor(i/2)
            i = (int)Math.floor(i/2);
        }
    }
}
