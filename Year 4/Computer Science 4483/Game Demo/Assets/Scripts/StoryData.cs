using UnityEngine;
using UnityEngine.UI;
using System.IO;
using System;

public class StoryData : MonoBehaviour {

	// Use this for initialization
	public void Data(int type){

		if (type == -1)
        {
            // Load data
			string path = "Assets/Resources/story.dat";
			StreamReader read = new StreamReader (path);
			string pType = read.ReadLine ();
			int level = Convert.ToInt32 (pType);
			pType = read.ReadLine ();
			int progress = Convert.ToInt32 (pType);
			read.Close ();

			// Create a Stream Writer, that overwrites the contents
			StreamWriter writer = new StreamWriter (path, false);

            // Save new data
			if ((level + 1) > progress) {
				progress += 1;
			}

			level = -1 * level;

			// Write the player name to the file
			writer.WriteLine (level);
			writer.WriteLine (progress);

			// Close the StreamWriter
			writer.Close ();

		}

        else
        {
            // Load data
			string path = "Assets/Resources/story.dat";
			StreamReader read = new StreamReader (path);
			string pType = read.ReadLine ();
			pType = read.ReadLine ();
			int progress = Convert.ToInt32 (pType);
			read.Close ();

            // Save data
			// Create a Stream Writer, that overwrites the contents
			StreamWriter writer = new StreamWriter (path, false);

			// Write the player name to the file
			writer.WriteLine (type);
			writer.WriteLine (progress);

			// Close the StreamWriter
			writer.Close ();
		}
	}
}
