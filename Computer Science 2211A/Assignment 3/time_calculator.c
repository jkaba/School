/* Name: Jameel Kaba
   GAUL ID: jkaba
   Student #: 250796017
	
   This program gets a time and duration from the user
   and calculates what the new time would be in a 24 hour clock */

#include <stdio.h>

int main(void)
{

  /*initialize variables to enter loops */
  int time_of_day = -1;
  int duration = 70;
  int time = 0;

/* while the time of day is negative or not within a 24 hour range */
  while(time_of_day < 0 || time_of_day > 2359||(time_of_day % 100)>=60)
  {

    /* Ask the user for the time of day*/
    printf("Enter the Time of Day: ");

    /* read the input from the user */
    scanf("%d", &time_of_day);
  }

/* while the duration of time does not have the proper minutes */	
  while((duration%100)>=60 || (duration%100)*-1 >= 60)
  {

    /* Ask the user for a duration */
    printf("Enter the Duration of time: ");

    /* read the input from the user */
    scanf("%d", &duration);
  }

/* if the duration is a positive amount of time */
  if(duration > 0)
  {
    /* the new time is the time entered by the user 
       with the duration added on */
    time = time_of_day + duration;
  }

  else
  {
    /* if the duration is divisible by 60 */
    if((duration %60)*-1 == 0)
    {
      
      /* the time is the time enetered by the user
         plus the duration (decrements hour)*/
      time = time_of_day + duration;
    }

    /* else if the duration is greater than -1000 */
    else if(duration  > -1000)
    {
      /* determine the minute values for the time */
      time = time_of_day + ((duration - (duration%60))+(60-duration%60))-100;
    }
    else
    {
      /* determine the minute value for the time */		
      time = time_of_day + ((duration +(duration%60))+(60-duration%60))-100;
    }
		
  }

/* if the minute value in time is greater than 60 */
  if(time % 100 >= 60)
  {
    /* add 40 to the time to make it equal to a proper value of time */
    time = time + 40;
  }

/* while the time is greater than 24 hours */
  while(time > 2360)
  {
    /* subtract 2400 from the time to make it within
       a 24 hour clock range */
    time = time - 2400;
  }

/* while the time is a negative value */
  while(time<0)
  {
    /* add 2400 to the time to make it fall within a 
       24 hour clock range */
    time = time + 2400;
  }


/* if statements to make the time be a 4 digit number in 
   a 24 hour clock */

/* if the time is between 10 and 100 */
  if(time < 100 && time >= 10)
  {
    /* add 00 infront to make it 4 digits */
    printf("The new time is: 00%d\n", time);
  }

/* if the time is between 100 and 1000 */
  if(time < 1000 && time > 100)
  {
    /* add a 0 infront of the time to make it 4 digits */
    printf("The new time is: 0%d\n", time);	
  }

/* if the time is a single value */
  if(time < 10)
  {
    /* add three 0's in front to make it 
       a normal value of time */
    printf("The new time is: 000%d\n", time);
  }

/* if the time is between 1000 and 2400 */
  if(time >= 1000 && time <2400)
  {
    /* print the time as is since it is already 4 digits */
    printf("The new time is: %d\n", time);
  }

  return 0;
} 

	
