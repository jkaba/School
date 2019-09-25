# Assignment 3

## Description
Implement the Prim’s minimum spanning tree algorithm for a weighted undirected graph using a heap data structure. The time complexity of the algorithm should be O((|V | + |E|) log |V |).

The heap data structure should be implemented as an abstract data type (a class in C++) on a set of elements, where each element has an id and a key, with the following operations.

• heap ini(keys, n): initializes a heap with the array keys of n elements indexed from 1 to n, where key[i] is the key of the element whose id is i.
• in heap(id): returns true if the element whose id is id is in the heap;
• min key(): returns the minimum key of the heap;
• min id(): returns the id of the element with minimum key in the heap;
• key(id): returns the key of the element whose id is id in the heap;
• delete min(): deletes the element with minimum key from the heap;
• decrease key(id, new key): sets the key of the element whose id is id to new key if its current key is greater than new key.

An input graph file will be available. The format of the input file is the following:
• The first line of the input file contains an integer indicating the number of vertices of the input graph.
• Each of the remaining lines contains a triple ′′i j w′′ indicating an edge between vertex i and vertex j with cost w.
Vertex 1 can be considered as the root.

The output of your program should be the following:
• The input graph in adjacency list representation format listing each edge with its weight.
• The edges (with their weights) of the minimum spanning tree, in the order in which they are produced by the Prim’s algorithm.
