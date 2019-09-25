/* CS2211A Assignment 5
   Name: Jameel Kaba
   GAUL ID: jkaba
   Student #: 250796017

   This program consists of the functions to be used in the main method */

/* include header files */
#include <stdio.h>
#include <stdlib.h>
#include "operation_functions.h"

/* Multiplication function that takes two complex_tags and returns a
   Complex_type consisting of the multiplication results */

Complex_type multiplication(struct complex_tag c1, struct complex_tag c2)
{
  /* Create the Complex_type to be returned */
  Complex_type product;
 
  /* Calculate the real and imaginary parts of the Complex_type */
  product.real = c1.real*c2.real - c1.imaginary*c2.imaginary;
  product.imaginary = c2.real*c1.imaginary + c1.real*c2.imaginary;

  /* return the Complex_type structure */
  return product;
}

/* Division function that takes three pointers to complex_tags and
   sets the third pointer to store the division results of the other
   two complex_tags.
   Returns -2 if division by 0 or 0 if successful */

int divide(struct complex_tag *c1, struct complex_tag *c2, struct complex_tag *c3)
{
  /* if the denominator is 0 return -2 */
  if((c2->real*c2->real + c2->imaginary*c2->imaginary) == 0)
  {
    return -2;
  }

  /* Calculate the real and imaginary parts to be stored in the third pointer */
  c3->real = (c1->real*c2->real+c1->imaginary*c2->imaginary)/(c2->real*c2->real+c2->imaginary*c2->imaginary);
  c3->imaginary = (c2->real*c1->imaginary - c1->real*c2->imaginary)/(c2->real*c2->real + c2->imaginary*c2->imaginary);

  /* return 0 to exit successfully */
  return 0;
}

/* add_subtract function that takes two complex_tags and two pointer to a pointer to a complex_tag
   and calculates the sum and difference, storing the sum in one pointer and the difference
   in the other pointer */

int add_subtract(struct complex_tag c1, struct complex_tag c2, struct complex_tag **c3, struct complex_tag **c4){

  /* allocate memory for the two pointers */
  *c3 = malloc(sizeof(struct complex_tag));
  *c4 = malloc(sizeof(struct complex_tag)); 

  /* if the memory allocation resulted in 0 */
  if (*c3==0)
  {                

    /* print an error message and return -1 */
    printf("Memory Error: Need more memory");
    return -1;
  }
	
  /* if the memory allocation resulted in 0 */
  if (*c4==0)
  {

    /* print an error message and return -1 */
    printf("Memory Error: Need more memory");
    return -1;
  }

  /* calculate the sum of the two complex_tags and
     store it in one of the pointers */

  (*c3)->real = (c1.real+c2.real);
  (*c3)->imaginary = (c1.imaginary+c2.imaginary);
    
  /* calculate the difference of the two complex_tags
     and store it in the other pointer */

  (*c4)->real = (c1.real-c2.real);
  (*c4)->imaginary = (c1.imaginary-c2.imaginary);
   
  /* return 0 to successfully exit */
  return 0;
}

