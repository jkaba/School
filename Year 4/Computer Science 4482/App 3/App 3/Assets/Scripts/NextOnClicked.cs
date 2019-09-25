using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using System.IO;

// NextOnClicked class used for entering the player name
public class NextOnClicked : MonoBehaviour
{
    // Public Variables
    public InputField nameField;
    public Text Error;
    public GameObject page1;
    public GameObject page2;
    public GameObject cube;

    /*
     * resume method
     * This method checks to see if the name entered is of < 10 char length
     * before allowing the user to advance to ship selection
     */
    public void Resume()
    {
        // If the length of name is less than 10 char, then save name and start game
        if (nameField.text.Length < 10)
        {
            // File location
            string path = "Assets/Resources/name.txt";

            // Create a Stream Writer, that overwrites the contents
            StreamWriter writer = new StreamWriter(path, false);

            // Write the player name to the file
            writer.WriteLine(nameField.text);
           
            // Close the StreamWriter
            writer.Close();

            // De-activate the name entry page
            page1.SetActive(false);

            // Activate the ship selection page and the ship model
            page2.SetActive(true);
            cube.SetActive(true);
        }

        // Else bring up the error message
        else
        {
            Error.gameObject.SetActive(true);
        }
    }
}
