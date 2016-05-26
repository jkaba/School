/* Name: Jameel Kaba
   GAUL ID: jkaba
   Student #: 250796017

   This program calculates the remaining balance on a loan
   after each of the first n monthly payments, by taking user input */

#include <stdio.h>

int main(void)
{

/* initialize variables to -1 */
  float loan = -1;
  float interest = -1;
  float payment = -1;
  int n = -1;

/* while the loan amount is less than or equals 0 */
  while(loan <= 0)
  {
    /* Ask the user for the amount of the loan */
    printf("Enter the amount of the loan: ");
    
    /* read the input from the user */
    scanf("%f", &loan);
  }

/* while the interest rate is less than 0 */
  while(interest < 0)
  {

    /* Ask the user for the interest rate */
    printf("Enter the interest rate: ");

    /* read the input from the user */
    scanf("%f", &interest);
  }

/* while the monthly payment value is less than 0 */
  while(payment < 0)
  {

    /* Ask the user for the monthly payment value */
    printf("Enter the monthly payment: ");

    /* read the input from the user */
    scanf("%f", &payment);
  }

/* while the number of monthly payments is less than 0 */	
  while(n < 0)
  {
 
    /* Ask the user for the number of monthly payments */
    printf("Enter the number of monthly payments ");

    /* read the input from the user */
    scanf("%d", &n);
  }

/* convert the interest rate from a whole number to a decimal (percentage) */
  interest = interest / 1200;

/* initialize a variable i */
  int i;

/* for i being less than or equal to the number of monthly payments */
  for(i=1; i <= n; i++)
  {

    /* Calculate the loan by subtracting the payment from the loan 
    and adding the loan times the interest to the amount */
   
    loan = loan - payment + (loan * interest);

    /* if the value of the loan is less than  0 */
    if(loan <= 0)
    {

      /* calculate the final loan payment */
      loan = loan + payment;

      /* let the user know the final loan payment */
      printf("The final payment will be $%.2f after %d months\n", loan, i);

      /* break from the loop */
      break;
    }
    /* let the user know how much the remaining value of the loan is */
    printf("The remaining value of the loan after %d months is $%.2f\n", i, loan);
  }
  return 0;
}
