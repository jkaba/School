/* Name: Jameel Kaba
   GAUL ID: jkaba
   Student #: 250796017

   This program takes a small number from the user
   and keeps adding terms to the constant e until the
   value of the current term is less than the user input */

#include <stdio.h>

int main(void)
{

/* Initialize variables */
  float input = -1.0;
  float term = 1.0;
  float e = 1.0;
  int count = 1;
  
/* while the value of input is not between 0 and 1 */
  while(input < 0 || input > 1)
  {
  
    /* Ask the user for input */
    printf("Please enter a number between 0 and 1: ");
    
    /* read the user input */
    scanf("%f", &input);
  }

  
  /* while the value of term is greater than input */
  while(term > input)
  {
    /* set i to 0 and the term to 1 */
    float i = 1;
    term = 1.0;

    /* increment the counter */
    count++;
 
    /* for as long as i is less than count */
    for(i = 1; i < count; i++)
    {
      /* calculate the factorial for term */
      term = term / i;
    }
    
    /* set e to e plus the value of term */
    e = e + term;
    
    }

    /* print the value of e to 15 decimal points and the count */
    printf("The value of e is %.15f after %d terms\n", e, count);

    return 0;
}
