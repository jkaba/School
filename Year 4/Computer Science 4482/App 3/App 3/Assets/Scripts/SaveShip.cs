using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.IO;
using System;

// SaveShip class used to save the players choice of ship
public class SaveShip : MonoBehaviour {

    // ShipSelect object used to save the ship chosen
    public ShipSelect ship;

	public void save()
    {
        // File location
        string path = "Assets/Resources/ship.txt";

        // Create a Stream Writer, that overwrites the contents
        StreamWriter writer = new StreamWriter(path, false);

        // Convert the int to a string
        string shipnum = Convert.ToString(ship.count);

        // Write the string to the file
        writer.WriteLine(shipnum);

        // Close the StreamWriter
        writer.Close();
    }
}
