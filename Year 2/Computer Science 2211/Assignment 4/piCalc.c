/* CS2211 Assignment 4
   Name: Jameel Kaba
   GAUL ID: jkaba
   Student #: 250796017
 
   This program finds an approximation to the constant pi
   It also calculates the mean and standard deviation of the
   results generated from a number from user input */
 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int main()
{	

  /* Initialize variables */
  srand((unsigned)time(NULL));
  int n = -1;
  double mean = 0;
  double sd =0 ;
  double values[10];
  int k = 0;
  int m = 0;
  
  /* While n is not a positive integer */
  while (n < 0)
  {

    /* Ask the user for a positive integer and set the value to n */
    printf ("Please enter a valid, positive integer: ");
    scanf("%d",&n);
  }
  
  /* while k is less than 10 */
  for (k = 0; k <10; k++)
  {

    /* initialize variables to calculate pi */
    int i = 1;
    double x = 0;
    double y = 0;
    int sample =0;
  
    /* for i less than or equal to n */
    for (i = 1; i <= n; i++)
    {

      /* let x and y both reference random numbers */
      x = (double)rand()/(double)RAND_MAX;
      y = (double)rand()/(double)RAND_MAX;
	
      /* if x squared plus y squared is less than or equal to 1 */
      if ((x*x + y*y) <= 1)
      {

        /* increment the sample */
        sample++;
      }
    }
  
    /* Set the ratio as the sample divided by n */
    double ratio = (double)sample/(double)n;
  
    /* let pi equal the ratio multiplied by 4 */
    double pi = ratio*(double)4;
    
    /* Let pi be referenced in the array at position k */
    values[k] = pi;
    
    /* Print the value of temp pi */
    printf("%f\n", pi);
  }	
  
  /* While m is less than 10 */
  for(m = 0; m < 10; m++)
  {

    /* Let the mean equal itself plus the value in the array at position m */
    mean = mean + values[m];
  }

  /* Let the mean equal itself divided by 10 */
  mean = mean/(double)10;

  /* Print the mean */
  printf("The mean is %f\n", mean);
  
  /* While m is less than 10 */
  for(m = 0; m < 10; m++)
  {

    /* Let sd equal itself plus the value in position m minus the mean times itself */
    sd = sd + (values[m]-mean)*(values[m]-mean);
  }
  
  /* Let sd equal itself divided by 10 */
  sd = sd/ (double)10;
  
  /* Let sd equal the square root of itself */
  sd = sqrt(sd);
  
  /* Print the standard deviation */
  printf ("The standard deviation is %f\n", sd);
  return 0;
}
