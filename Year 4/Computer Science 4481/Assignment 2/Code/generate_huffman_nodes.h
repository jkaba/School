/*
 * CS4481B Assignment 2
 * Name: Jameel Kaba
 * UWO/GAUL ID: jkaba
 * student #: 250796017
 */

#ifndef _GENERATE_HUFFMAN_NODES_H_
#define _GENERATE_HUFFMAN_NODES_H_
#include "libpnm.h"

// Node structure contains two values which is an ordered pair of pixel values
struct node {
    int first_value;
    int second_value;
};

struct node *generate_huffman_nodes(long int *pixel_frequency, int max_gray_value, int number_of_non_zero_values_in_the_frequency_array);
#endif
