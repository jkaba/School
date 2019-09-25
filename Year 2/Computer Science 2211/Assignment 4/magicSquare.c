/* CS2211A Assignment 4
   Name: Jameel Kaba
   GAUL ID: jkaba
   Student #: 250796017

   This program prints out a magic square of size n
   where n is an odd number between 0 and 13 determined by 
   the user */

#include <stdio.h>

int main(void){
  /* initialize n to 0 inorder to enter the loop */
  int n = 0;
  /* while n is an odd number between 0 and 13 */
  while ((n<0 || n>13) || (n%2==0))
  {

    /* Ask the user to enter an n value and set it as n */
    printf("Enter a positive odd value between 1 and 13: ");              
    scanf("%d", &n);                        
  }

  /* initialize variables */
  int magicSquare[n][n];                                  
  int col = n/2;                                    
  int row = 0;                                     
  int num = 2;                                    
  int tempCol, tempRow;                                     
  int i, j;                 

  /* nested for loops to set every element in magicSquare to 0 */                      
  for(i=0;i<n;i++)
  {
    for(j=0;j<n;j++)
    {
      /* Use pointer notation to set element at row i, column j to 0 */
       *((*(magicSquare + i)) + j)=0;
    }
  }
  
  /* Set the middle element in the first row to 1 */
  *((*(magicSquare + row)) + col) = 1;              

  /* while loop to insert number referenced by num into the array */              
  while (num <= n*n)
  {
    
    /* if the column is equal to n-1 */
    if (col == (n-1))
    {                          
 
      /* let the tempCol reference col */
      tempCol = col;                     
   
      /* Set the column to reference 0 */      
      col = 0;                           
    }

    else
    {

      /* else set tempCol to reference col */
      tempCol = col;                           

      /* increment col */
      col++;
    }                    

    /* if the value of row is equal to 0 */       
    if (row == 0)
    {
 
      /* Set the tempRow to equal 1 */
      tempRow = 1;
 
      /* Set row to reference n-1 */ 
      row = (n-1);
    }
    
    /* else if row is equal to n-1 */
    else if(row == (n-1))
    {

      /* Set tempRow to 0 and decrement row */
      tempRow = 0;
      row--;
    }

    else
    {

      /* Set tempRow to reference row + 1 */
      tempRow = (row+1);

      /* decrement row */
      row--;
    }
    
    /* if the element at row, col, is not 0 */
    if ( *((*(magicSquare + row)) + col) !=0)
    {
  
      /* Set the row to temp row */                     
      row = tempRow;               

      /* Set the col to temp col */            
      col = tempCol;
    }

     /* Set the element at row, col to num */
     *((*(magicSquare + row)) + col) = num;  

     /* increment num */                      
     num++;                                  
  }

  /* nested loop to print out the magic square */
  for(i=0;i<n;i++)
  {                               
    for(j=0;j<n;j++)
      {
   
        /* print out the element at row i, column j */
        printf("%d\t",  *((*(magicSquare + i)) + j));
      }

    /* print a new line */
    printf("\n");
  }
 return 0;
}
