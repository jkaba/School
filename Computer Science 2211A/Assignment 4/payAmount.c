/* CS2211 Assignment 4
   Name: Jameel Kaba
   GAUL ID: jkaba
   Student #: 250796017
   
   This program takes a dollar amount from user input
   and outputs the smallest amount of change in bills and coins
   required to pay it */
 
#include <stdio.h>
#include <stdlib.h>

void pay_amount (int dollars, int *twenties, int *tens, int *fives, int *toonies, int *loonie);
int main()
{

  /* initialize the dollar amounts dollars set to -1 to ensure valid input */
  int dollars = -1;
  int twenties = 0, tens = 0, fives = 0, toonies = 0, loonie = 0;
	
  /* While the value for dollars is not valid */
  while (dollars < 0)
  {

    /* Gets the user to input a dollar amount and sets that value to dollars */
    printf("Please enter in a positive dollar amount that is an integer: ");
    scanf("%d", &dollars);
  }
	
  /* Call method pay_amount to calculate the smallest amount of bills and coins
     needed to pay the user */

  pay_amount(dollars, &twenties, &tens, &fives, &toonies, &loonie);
	
  /* Prints the amount of bills and coins needed to pay the user */
  printf ("The number of twenties is %d\n", twenties);
  printf("The number of tens is %d\n", tens);
  printf("The number of fives is %d\n", fives);
  printf("The number of toonies is %d\n", toonies);
  printf("The number of loonies is %d\n", loonie);
  return 0;
}

/* This method points to the number of different changes (bills and coins)
   and gives the main program the change divided into different amounts */

void pay_amount (int dollars, int *twenties, int *tens, int *fives, int *toonies, int *loonie)
{
	
  /* If the dollar amount is greater than or equal to 20 */
  if (dollars >= 20)
  {

    /* Let the pointer reference temp divided by 20 */
    *twenties= dollars/20;
        
    /* Take away the twenty pointer multiplied by 20 from the dollars */
    dollars -= *twenties*20;
  }
	
 
  /* If the dollar amount is greater than or equal to 10 */
  if (dollars >= 10)
  {

    /* Let the pointer reference temp divided by 10 */
    *tens = dollars/10;
		
    /* Take away the tens pointer multiplied by 10 from the dollars */
    dollars -= *tens*10;
  }
	
	
  /* If the dollar amount is greater than or equal to 5 */
  if (dollars >= 5)
  {

    /* Let the pointer reference temp divided by 5 */
    *fives = dollars/5;
		
    /* Take away the fives pointer multiplied by 5 from the dollars */
    dollars -= *fives*5;
  }
	
  /* If the dollar amount is greater than or equal to 2 */
  if (dollars >= 2)
  {

    /* Let the pointer reference temp divided by 2 */
    *toonies = dollars/2;
        
    /* Take away the toonie pointer multiplied by 2 from dollars */
    dollars -= *toonies*2;
  }
	
  /* If the dollars is equal to 1 */
  if (dollars == 1)
  {

    /* Let the pointer equal to 1 */
    *loonie = 1;
  } 
}
