/**
 * Name: Jameel Kaba
 * Student#: 250796017
 * UWO ID: jkaba
 * CS3340b Assignment 3
 * Question 11
 * Heap ADT
 */

public interface HeapADT{
    
    // initialize heap
    void heap_ini(Edge keys[], int n);
    
    // checks if the edge is in the heap
    boolean in_heap(Edge id);
    
    // returns the minimum key
    int min_key();
    
    // returns the minimum id
    int min_id();
    
    // returns the key at position id
    int key(int id);
    
    // deletes the minimum edge
    Edge delete_min();
    
    // decreases the key at position id
    void decrease_key(int id, int new_key);
}