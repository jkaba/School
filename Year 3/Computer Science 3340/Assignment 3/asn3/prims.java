/**
 * Name: Jameel Kaba
 * Student#: 250796017
 * UWO ID: jkaba
 * CS3340b Assignment 3
 * Question 11
 * prims class used to implement prims algorithm
 */

// import statements
import java.util.Scanner;
import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.List;
import java.util.StringTokenizer;
import java.io.*;
import java.util.*;

public class prims{
    
    //Global Variable
    static int numV;
    
    /* MST_Prim method
     * This method creates a minimum spanning tree 1 edge at a time
     * The output will show each node added, it's parent, and it's weight
     */
    public static void MST_Prim(ArrayList<LinkedList<Edge>> Graph, int root){
        
        // Make the keys and initialize parent array
        Edge[] keys = new Edge[numV+1];
        int[] pi = new int[numV+1];
        
        //initialize keys for the heap
        for (int i = 0; i <= numV; i++){
            
            // Each key defaults as 0,0,and inf, it's parent is -1
            Edge e = new Edge(0,0,Integer.MAX_VALUE);
            keys[i] = e;
            pi[i] = -1;
        }
        
        // Set the values for the root node, weight = 0, it is it's own parent
        keys[root].weight = 0;
        keys[root].u = root;
        keys[root].v = root;
        pi[root] = root;
        
        // Create the heap based off of the keys
        Heap heap = new Heap();
        heap.heap_ini(keys, keys.length);
        
        // Print Statement
        System.out.println("Order added to MST by Prim's Algorithm:");
        
        int cost = 0;
        Edge minEdge = new Edge(0,0,0);
        
        //get the minimum value until all values have been used
        while((cost = (minEdge = heap.delete_min()).getWeight()) != Integer.MAX_VALUE){
            
            // If either endpoint points does not point to 0
            if(minEdge.u != 0 && minEdge.v != 0){
                
                // Get the list of adjacent edges for the second end point
                LinkedList<Edge> list = Graph.get(minEdge.v);
                
                // Loop through all adjacent edges
                for(int i = 0; i < list.size(); i++){
                    
                    // Create a reference to the edge at position i of the list
                    Edge listEdge = list.get(i);
                    
                    // If the edge isn't in the heap and the weight is less than the current recorded
                    if(!heap.in_heap(listEdge) && listEdge.weight < keys[listEdge.v].weight){
                        
                        // Update keys, pi, and heap
                        pi[listEdge.v] = listEdge.u;
                        keys[listEdge.v] = listEdge;
                        heap.decrease_key(listEdge.v, listEdge.weight);
                    }
                }
                // Print block
                // If the weight of the edge is 0, then this is the root
                if(minEdge.weight == 0){
                    
                    // Print out the root message
                    System.out.println("Added: " + minEdge.u + "\tRoot Node " + "\tWeight: " + minEdge.weight);
                }
                
                // Else print out the normal message in regards to the node added, parent, and weight
                else{
                    System.out.println("Added: " + minEdge.v + "\tParent: " + pi[minEdge.v] + "\tWeight: " + minEdge.weight);
                }
            }
        }
    }
    
    public static void main(String[] args) {
        
        // initialize varables
        int inp = -1;
        File f;
        Scanner in;
        
        // If args is not 1 or no arguments
        if(args.length != 1){
            
            // Print Out Warning Message
            System.out.println();
            System.out.println("NOTE IF THIS PROGRAM, DOES NOT RUN. EXIT AND ENTER THE FOLLOWING");
            System.out.println("asn3.sh < file");
            System.out.println("This is how it was specified to run in the assignment description");
            System.out.println();
            
            // Set inp to 1
            inp = 1;
        }
        
        try{
            
            // If inp is 1, then scanner will come from a file from input
            if(inp == 1){
                in = new Scanner(System.in);
            }
            
            // else scanner comes from a file from args[0]
            else{
                in = new Scanner(new FileReader(args[0]));
            }
            
            // Read the first integer from the file, it represents number of vertices
            numV = Integer.parseInt(in.nextLine());
            
            // Initialize the Adjacency list
            ArrayList<LinkedList<Edge>> adj_list = new ArrayList<LinkedList<Edge>>();
            
            for(int i = 0; i <= numV; i++){
                adj_list.add(new LinkedList<Edge>());
            }
            
            // While the file is not at the end
            while(in.hasNext()){
                
                // Get the next line
                String s = in.nextLine();
                
                // initialize more variables
                int u;
                int v;
                int w;
                
                // tokenize the string and set the values to u, v, and w
                StringTokenizer tok = new StringTokenizer(s);
                u = Integer.parseInt(tok.nextToken());
                v = Integer.parseInt(tok.nextToken());
                w = Integer.parseInt(tok.nextToken());
                
                // Create an edge going from u to v and v to u
                Edge newEdge = new Edge(u, v, w);
                Edge newEdge2 = new Edge(v, u, w);
                
                // Add the edges into the appropriate list
                adj_list.get(u).addLast(newEdge);
                adj_list.get(v).addLast(newEdge2);
            }
            
            // Print Block
            System.out.println("Adjacency List Representation");
            System.out.println("Note: x(y) where x = end point and y = weight");
            
            // Loop through the first lists
            for(int i = 1; i <= numV; i++){
                
                // Print out what node we are looking at
                System.out.print("Adjacent to " + adj_list.get(i).get(0).getFirstEndPoint() + ": ");
                
                // Loop through for the adjacent edges
                for(int j = 0; j < adj_list.get(i).size(); j++){
                    
                    // Print out the adjacent edges with the appropriate weight
                    System.out.print(adj_list.get(i).get(j).getLastEndPoint() + " (" + adj_list.get(i).get(j).getWeight() + "), ");
                }
                
                // Print a blank line
                System.out.println();
            }
            
            // Set the root to be the first possible node in the adjacency list
            int root = adj_list.get(1).get(0).getFirstEndPoint();
            System.out.println();
            
            // Call Prim's algorithm
            MST_Prim(adj_list, root);
            
        }
        
        // Catch the Exception if necessary
        catch(FileNotFoundException e){
            System.out.println("Unable to load File");
            return;
        }
    }
}