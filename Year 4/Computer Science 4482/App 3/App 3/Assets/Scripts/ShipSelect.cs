using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
using UnityEngine.UI;
using System.IO;
using System;

// ShipSelect class used for ship selection
public class ShipSelect : MonoBehaviour
{
    // Public variables
    public int count = 0;
    string lPoints = "";
    int lp;
    public GameObject ship1;
    public GameObject ship2;
    public GameObject ship3;
    public GameObject ship4;
    public GameObject ship5;
    public GameObject submit;
    public Text shipName;
    public Text spread;
    public Text speed;
    public Text power;
    public Text health;
    public Text move;
    public GameObject error;
    public Text errorText;

    // Increase method used to change the page for ship selection
    public void Increase()
    {
        // If on the last page, then reset back to 1st page
        if(count == 4)
        {
            count = 0;
        }
        // Else move to next page
        else
        {
            count++;
        }
        // Refresh page
        Refresh();
    }

    void Refresh()
    {
        // File location
        string path = "Assets/Resources/save.txt";

        // Streamreader to get the lifetime points
        StreamReader read = new StreamReader(path);

        // get the lifetime points
        lPoints = read.ReadLine();

        // Close the StreamReader
        read.Close();

        // Convert the text into an int
        lp = Convert.ToInt32(lPoints);

        // If on page 0/ship 1
        if(count == 0)
        {
            // Set the first ship model to be true
            ship1.SetActive(true);

            // Remaining models set to not active
            ship2.SetActive(false);
            ship3.SetActive(false);
            ship4.SetActive(false);
            ship5.SetActive(false);

            // Display the Stats
            shipName.text = "OLD RELIABLE";
            spread.text = "SHOT SPREAD: SINGLE";
            speed.text = "SHOT SPEED: *";
            power.text = "SHOT POWER: *";
            health.text = "HEALTH: *";
            move.text = "MOVEMENT SPEED: *";
            submit.SetActive(true);
            error.SetActive(false);
        }

        // If on page 1/ship 2
        else if(count == 1)
        {
            // Set ship 2 model to be active, rest not active
            ship1.SetActive(false);
            ship2.SetActive(true);
            ship3.SetActive(false);
            ship4.SetActive(false);
            ship5.SetActive(false);

            // Display ship stats
            shipName.text = "THE CANUCK";
            spread.text = "SHOT SPREAD: DOUBLE";
            speed.text = "SHOT SPEED: **";
            power.text = "SHOT POWER: ***";
            health.text = "HEALTH: **";
            move.text = "MOVEMENT SPEED: **";

            // If the lifetime points are >= 5000
            if(lp >= 5000)
            {
                // Ship is unlocked
                submit.SetActive(true);
            }
            // Else ship is locked, display error
            else
            {
                error.SetActive(true);
                submit.SetActive(false);
                errorText.text = 5000 - lp + " POINTS NEEDED TO USE";
            }
        }

        // If on page 2/ship 3
        else if(count == 2)
        {
            // Display ship 3 model, rest not active
            ship1.SetActive(false);
            ship2.SetActive(false);
            ship3.SetActive(true);
            ship4.SetActive(false);
            ship5.SetActive(false);

            // Display ship stats
            shipName.text = "BLOOD SHOT";
            spread.text = "SHOT SPREAD: SINGLE";
            speed.text = "SHOT SPEED: *";
            power.text = "SHOT POWER: *****";
            health.text = "HEALTH: ***";
            move.text = "MOVEMENT SPEED: *";

            // If the ship is unlocked then the player can use it
            if (lp >= 10000)
            {
                submit.SetActive(true);
            }
            // Else display an error
            else
            {
                error.SetActive(true);
                submit.SetActive(false);
                errorText.text = 10000 - lp + " POINTS NEEDED TO USE";
            }
        }
        // If on page 3/ship 4
        else if(count == 3)
        {
            // Display model for ship 4, rest not active
            ship1.SetActive(false);
            ship2.SetActive(false);
            ship3.SetActive(false);
            ship4.SetActive(true);
            ship5.SetActive(false);

            // Display stats
            shipName.text = "TRAITOR";
            spread.text = "SHOT SPREAD: TRIPLE";
            speed.text = "SHOT SPEED: **";
            power.text = "SHOT POWER: *";
            health.text = "HEALTH: *****";
            move.text = "MOVEMENT SPEED: ***";

            // If ship is unlocked then the player can use it
            if (lp >= 15000)
            {
                submit.SetActive(true);
            }
            // Else display an erro
            else
            {
                error.SetActive(true);
                submit.SetActive(false);
                errorText.text = 15000 - lp + " POINTS NEEDED TO USE";

            }
        }
        // If on page 4/ship 5
        else if(count == 4)
        {
            // Display ship 5, rest not active
            ship1.SetActive(false);
            ship2.SetActive(false);
            ship3.SetActive(false);
            ship4.SetActive(false);
            ship5.SetActive(true);

            // Display stats
            shipName.text = "THE MILLIONAIRE";
            spread.text = "SHOT SPREAD: DOUBLE";
            speed.text = "SHOT SPEED: *****";
            power.text = "SHOT POWER: *****";
            health.text = "HEALTH: *****";
            move.text = "MOVEMENT SPEED: *****";

            // If ship is unlocked then the player can use it
            if (lp >= 20000)
            {
                submit.SetActive(true);
            }
            // Else display an error
            else
            {
                error.SetActive(true);
                submit.SetActive(false);
                errorText.text = 20000 - lp + " POINTS NEEDED TO USE";
            }
        }
    }
}
