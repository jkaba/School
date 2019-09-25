using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

/*
 * ResumeOnClicked class
 * This class is used at the start of the game
 * This brings up the player name entry screen
 * If an appropriate name is entered then the game starts upon submission
 * Else an error message appears
 */
public class ResumeOnClicked : MonoBehaviour {

    // Public Variables
    public PlayerMovement player;
    public InputField nameField;
    public Text Error;

    /*
     * resume method
     * This method checks to see if the name entered is of 3 char length
     * before allowing the user to start/resume the game
     */ 
    public void Resume()
    {
        // If the length of name is 3 char, then save name and start game
        if (nameField.text.Length == 3)
        {
            player.userName = nameField.text;
            player.start = false;
        }
        // Else bring up the error message
        else
        {
            Error.gameObject.SetActive(true);
        }
    }
}
