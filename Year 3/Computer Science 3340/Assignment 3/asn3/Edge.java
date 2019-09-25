/**
 * Name: Jameel Kaba
 * Student#: 250796017
 * UWO ID: jkaba
 * CS3340b Assignment 3
 * Question 11
 * Edge class used to implement Edges for graph and Heap
 */

public class Edge{

    // Components of an Edge
    public int u;
    public int v;
    public int weight;
    
    /*
     * Edge Constructor
     * input: the endpoints of the edge and it's weight
     * This constructor creates an edge with endpoints and weight
     * passed in as parameters
     */
    public Edge(int s, int f, int weight){
        this.u = s;
        this.v = f;
        this.weight = weight;
    }
    
    /*
     * getFirstEndPoint method
     * output: the first end point
     * This method returns the first end point of an edge
     */
    public int getFirstEndPoint(){
        return this.u;
    }
    
    /*
     * getLastEndPoint method
     * output: the second/last end point
     * This method returns the last end point of an edge
     */
    public int getLastEndPoint(){
        return this.v;
    }
    
    /*
     * getWeight method
     * output: the weight of the edge
     * This method returns the weight of the edge
     */
    public int getWeight(){
        return this.weight;
    }
    
    /*
     * toString method
     * output: The edge in string form
     * This method prints out the components of an edge
     */
    public String toString(){
        return "U = " + this.u + " V = " + this.v + " Weight = " + this.weight + "\n";
    }
}