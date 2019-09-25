using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using System.IO;

// LoadLifePoints class this class loads the total life points for Menu use
public class LoadLifePoints : MonoBehaviour {

    // Text field to display points
    public Text lPoints;

    void Start()
    {
        // Load the file
        string path = "Assets/Resources/save.txt";
        StreamReader read = new StreamReader(path);

        // Total Lifepoints on line 1, display in text field
        lPoints.text = "Lifetime Points: " + read.ReadLine();

        // Close the file
        read.Close();
    }
}
