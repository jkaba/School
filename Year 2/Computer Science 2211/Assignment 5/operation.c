/* CS2211A Assignment 5
   Name: Jameel Kaba
   GAUL ID: jkaba
   Student #: 250796017

   This program creates two complex numbers from 4 command line arguments
   It calculates the multiplication, division, sum, and difference
   of the two complex numbers */

/* include header files */
#include <stdio.h>
#include <stdlib.h>
#include "operation_functions.h"

int main(int argc, char *argv[])
{

  /* Create complex tags, pointers to them, and Complex_type structures */
  struct complex_tag c1, c2, c4;
  struct complex_tag c5;
  struct complex_tag *p5 = &c5;
  struct complex_tag c6;
  struct complex_tag *p6 = &c6;
  Complex_type c3;
    
  /* Check the number of arguments */
  if(argc != 5)
  {
    /* If there is not enough arguments print an error message and exit */
    printf("Not enough arguments\n");
    
    /* return unsuccessful status */
    return 1;
  }
    
  /* initialize the real and imaginary portion of the complex numbers */
  c1.real = atof(argv[1]);
  c1.imaginary = atof(argv[2]);
    
  c2.real = atof(argv[3]);
  c2.imaginary = atof(argv[4]);
    
  /* Print out the two complex numbers in the form a+ib */
  printf("The first complex number is %lf + i %lf\n", c1.real, c1.imaginary);
  printf("The second complex number is %lf + i %lf\n", c2.real, c2.imaginary);

  /* Call the multiplication function and print out the results */
  c3 = multiplication(c1, c2);
  printf("The multiplication of the two complex numbers is %lf + i %lf\n", c3.real, c3.imaginary);
    
  /* Create an int that references the result of the divide function */
  int divCheck = divide(&c1, &c2, &c4);

  /* If the value returned was not 0 then print an error message */
  if(divCheck != 0)
  {
    printf("Division by zero\n");
  }
 
  /* else print the result of the division function */
  else{
    printf("The division of the two complex numbers is %lf + i %lf\n", c4.real, c4.imaginary);
  }

  /* Create an int to reference the value returned by the add_subtract function */
  int asCheck = add_subtract(c1, c2, &p5, &p6);

  /* If the value returned was not 0 then print an error message */
  if(asCheck != 0)
  {
    printf("Memory error\n");
  }

  /* else print the sum and difference of the two complex numbers */
  else{
    printf("The addition of the two complex numbers is %lf + i %lf\n", p5->real, p5->imaginary);
    printf("The subtraction of the two complex numbers is %lf + i %lf\n", p6->real, p6->imaginary);
  }
    
  /* print a new line for readability */
  printf("\n");

  /* return 0 to exit the program */
  return 0;
}
