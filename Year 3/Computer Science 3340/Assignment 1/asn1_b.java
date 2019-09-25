/**
 * Name: Jameel Kaba
 * Student #: 250796017
 * UWO ID: jkaba
 * CS3340b Assignment 1
 * Question 7b
 */

public class asn1_b
{
    
    // Size of the array should be large enough to contain F(300)
    private static final int SIZE = 100;

    /*
     * fibonacci method
     * input: double n
     * output: term n in the fibonacci sequence
     * The method initializes arrays and computes
     * F(n) = (n-1) + (n-2)
     */
	public static int[] fibbonacci(double n)
	{
        
        // Create array to store F(n), n-1, and n-2
        int[] value = new int[SIZE];
        plusOne(value);
        
        int[] nMinusOne = new int[SIZE];
        plusOne(nMinusOne);
        
        int[] nMinusTwo = new int[SIZE];
        
        // If n is 0, then just set value to 0
        if(n == 0)
        {
            value = new int[SIZE];
        }
        
        // If n is 1, then do nothing as value is 1
        else if (n == 1)
        {
        }
        
        // if n > 2, compute F(n)
        else{
            for(int i = 2; i <= n; i++)
            {
                value = addLarge(nMinusOne, nMinusTwo);
                nMinusTwo = nMinusOne;
                nMinusOne = value;
            }
        }
        
        // Return F(n) to the main program
        return value;
	}
    
    /*
     * addLarge method
     * input: int[] numberOne, int[] numberTwo
     * output: The addition of two large number represented in an array
     * This method calculates the addition between two integer arrays
     * this is done by adding the index at position i-1 of both arrays
     * returns an array containing the addition
     */
    public static int[] addLarge(int[] numberOne, int[] numberTwo)
    {
        // Create a new array and set a boolean carry to false
        int[] sum = new int[SIZE];
        boolean carry = false;
        
        // for loop that adds up index at i-1 from both arrays
        for(int i = SIZE; i > 0; i--)
        {
            // Set index sum to 0
            int indexSum = 0;
            
            // If the carry is true, set index sum to 1 as there is a carry
            if(carry)
            {
                indexSum = 1;
                carry = false;
            }
            
            // Calculate the sum of index at i-1 from both arrays
            indexSum += numberOne[i-1] + numberTwo[i-1];
            
            // If the index sum is greater than 9, set carry to true
            if(indexSum > 9)
            {
                carry = true;
            }
            
            // Set value for sum at i-1
            sum[i-1] = indexSum % 10;
        }
        
        // return the sum array
        return sum;
    }
    
    /*
     * plusOne method
     * This method is used to add 1 to an array
     * Used only for initialization, to start array at 1
     */
    public static void plusOne(int[] num)
    {
        
        // Array now contains/ends with 1
        num[SIZE-1] = 1;
    }
    
    /*
     * print method
     * This method is used to print out the array 
     * that contains F(n). Leading zeroes are cut, 
     * while the rest of the elements are printed together 
     * on one line to represent a number
     */
    public static void print(int[] num)
    {
        
        // Flag to remove leading zeroes
        boolean removeLeadingZeroes = true;
        
        // For loop to print the number
        for (int i = 0; i < SIZE; i++)
        {
            
            // While loop to remove all leading zeroes
            while(removeLeadingZeroes)
            {
                // If the number is a 0, remove it
                if(i < SIZE && num[i] == 0)
                {
                    i++;
                }
                
                // Otherwise, set flag to false
                else
                {
                    removeLeadingZeroes = false;
                }
            }
            
            // If the array is not all zeroes then print
            if(i < SIZE)
            {
                System.out.print(num[i]);
            }
            
            // Else, the array is 0, so print 0
            else
            {
                System.out.print("0");
            }
        }
        // Print out a new line
        System.out.println();
    }

    
    // Main method
    public static void main(String[] args)
    {
        // Calculate and print F(0) to F(300)
        for(int i = 0; i <= 30; i++)
        {
            System.out.print("F(" + i*10 + ") = ");
            print(fibbonacci(i*10));
        }
    }
}
