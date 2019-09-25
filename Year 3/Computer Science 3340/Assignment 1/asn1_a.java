/**
 * Name: Jameel Kaba
 * Student#: 250796017
 * UWO ID: jkaba
 * CS3340b Assignment 1
 * Question 7a
 */

public class asn1_a
{
	
    // fibonacci method
    // This method calculates F(n) = n-1 + n-2
	public static int fibbonacci(int n)
	{
        // If n is 0, return 0
		if(n == 0)
		{
			return 0;
		}
        
        // If n is 1, return 1
		else if(n == 1)
		{
			return 1;
		}
        
        // Else return the sum of the fibonacci number of n-1 and n-2
		else
		{
			return fibbonacci(n-1) + fibbonacci(n-2);
		}
	}
    
    // Main method
    public static void main(String[] args)
    {
        // For loop to calculate up to F(35)
        for(int i = 0; i <= 7; i++)
        {
            System.out.println("F(" + i*5 + ") = " + fibbonacci(i*5));
        }
    }
}

			
