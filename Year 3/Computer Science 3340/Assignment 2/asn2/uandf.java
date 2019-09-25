/**
 * Name: Jameel Kaba
 * Student#: 250796017
 * UWO ID: jkaba
 * CS3340b Assignment 2
 * Question 10a
 */

public class uandf
{
    
    // Private variables
    private int[] parent;
    private int[] rank;
    private boolean finalSet = false;
    
    /*
     * uandf
     * Constructor that creates a UnionFind structure with n elements
     */
    public uandf(int n){
        
        // Set parent and rank
        parent = new int[n];
        rank = new int[n];
    }
    
    /*
     * make set
     * creates a new set whose only member is i
     */
    public void makeSet(int i){
        
        // Set parent at i to be i
        parent[i] = i;
    }
    
    /*
     * union sets
     * Unites the dynamic sets that contain i and j into a
     * new set that is the union of these two sets
     */
    public void unionSets(int i, int j){
        
        // Find the sets for i and j
        i = findSet(i);
        j = findSet(j);
        
        // if rank of i is larger than rank of j
        if(rank[i] > rank[j]){
            
            // Set parent at j to be parent at i
            parent[j] = parent[i];
        }
        
        // if rank of i is smaller than rank of j
        else if(rank[i] < rank[j]){
            
            // Set parent at i to be parent at j
            parent[i] = parent[j];
        }
        
        // Otherwise they are equal
        else
        {
            // set parent at j to be parent at i
            parent[j] = parent[i];
            
            // Increment rank of i
            rank[i]++;
        }
    }
    
    /*
     * find set
     * Returns the representative of the set containing i
     */
    public int findSet(int i){
        
        // If final set is false
        if(finalSet == false){
            
            // if parent at i does not equal i
            if(parent[i] != i){
                
                // return the set that contains parent at i
                return (parent[i] = findSet(parent[i]));
            }
            
            // Otherwise return i
            else{
                return i;
            }
        }
        
        // Otherwise return parent at i
        else{
            return parent[i];
        }
    }
    
    /*
     * final sets
     * returns the total number of current sets, finalizes the current sets
     * and resets the representatives of the sets so that integers from 1 to
     * final sets() will be used as representatives.
     */
    public int finalSets(){
        
        // Loop through parent
        for(int i = 1; i < parent.length; i++){
            
            // If parent at i is not 0
            if(parent[i] != 0){
                
                // Then find the set that i belongs to
                findSet(i);
            }
        }
        int current = 1;
        
        // loop through parent again
        for(int i = 1; i < parent.length; i++){
            
            // if parent at i is i
            if (parent[i] == i){
                
                // parent at i is now incremented current
                parent[i] = current++;
                
                // rank of i is 1
                rank[i] = 1;
            }
            
            // Otherwise rank of i is 0
            else{
                rank[i] = 0;
            }
        }
        
        // loop through parent
        for(int i = 1; i < parent.length; i++){
            
            // If the rank of i is 0, and parent at i is > 0
            if(rank[i] == 0 && parent[i] > 0){
                
                // then parent of i is the parent of the parent of i
                parent[i] = parent[parent[i]];
            }
        }
        
        // Set final set to true and return current - 1
        finalSet = true;
        return current-1;
    }
}
