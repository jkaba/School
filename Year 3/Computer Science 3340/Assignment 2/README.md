# Assignment 2

## Description

Finding connected components in a binary image.

## Part 1
An Union-Find data structure should be implemented as an abstract data type (a class in C++ or java) with the following operations.

• uandf(n): constructs an union-find data type with n elements, 1, 2, . . . , n.
• make set(i): creates a new set whose only member (and thus representative) is i.
• union sets(i,j): unites the dynamic sets that contains i and j, respectively, into a new set that is the union of these two sets.
• find set(i): returns the representative of the set containing i.
• final sets(): returns the total number of current sets, finalizes the current sets (make set() and union sets() will have no effect after this operation), and resets the representatives of the sets so that integers from 1 to final sets() will be used as representatives.

## Part 2
Design and implement (a program) an algorithm to find the connected components, with 4-connectivity, in a binary image using Union-Find data structure in a).

An ASCII file containing a binary image is available (see girl.img and img readme) as the input of your program. The output of the program should be the following in this specified order:

1. the input binary image,
2. the connected component image where each component is labelled with a unique char- acter,
3. a list sorted by component size, where each line of the list contains the size and the label of a component,
4. same as 2 with the connected component whose size equals to one or two removed.
