using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using System.IO;

public class NextClicked : MonoBehaviour {

	public void Resume(int num)
	{
		
			// File location
			string path = "Assets/Resources/survival.txt";

			// Create a Stream Writer, that overwrites the contents
			StreamWriter writer = new StreamWriter(path, false);

			// Write the player name to the file
			writer.WriteLine(num);

			// Close the StreamWriter
			writer.Close();

			// De-activate the name entry page
			


		
	}
}
