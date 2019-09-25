using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

/*
 * GameManager class
 * This class handles the timer, and player score calculation
 */
public class GameManager : MonoBehaviour
{
    // Public Variables
    public float countdownTimer;
    public Text countdownTimerText;
    public PlayerMovement player;

    void Start()
    {
        // Player is given 300 seconds / 5 minutes to reach the end of the maze
        countdownTimer = 300f; 
    }
    void Update()
    {
        // Run the timer
        CountdownTimer();
    }
    void CountdownTimer()
    {
        // If the game is being played, then run the timer
        if (player.gameOver == false && player.pause == false && player.start == false)
        {
            // Decrease timer by 1 second
            countdownTimer -= Time.deltaTime;

            // Round the minute value
            float minutes = Mathf.Floor(countdownTimer / 60);

            // Round the seconds value
            float seconds = Mathf.Floor(countdownTimer % 60); 

            // If time runs out, then game over 
            if (minutes == 0 && seconds == 0)
            {
                player.gameOver = true;
            }

            // Initialize text for seconds
            string secondsText = "";

            // If less than 10 seconds, add a 0 before seconds value
            if (seconds < 10)
            {
                secondsText = "0" + seconds.ToString();
            }

            // Otherwise, set text for seconds to contain seconds value
            else
            {
                secondsText = seconds.ToString();
            }

            // If less than 30 seconds left, set text to be Red
            if (minutes == 0 && seconds < 30)
            {
                countdownTimerText.color = Color.red;
            }

            // Update the timer text
            countdownTimerText.text = "Time: " + minutes + ":" + secondsText;
        }
    }

    // getTime method
    // This method returns the amount of time left
    public float getTime()
    {
        // Time left in seconds is the score which is returned
        return countdownTimer;
    }
}