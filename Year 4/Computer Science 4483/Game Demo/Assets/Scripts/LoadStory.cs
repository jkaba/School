using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
using UnityEngine.UI;
using System.IO;
using System;

public class LoadStory : MonoBehaviour
{

    // variables
	public GameObject level1;
	public GameObject level2;
	public GameObject level3;
	public GameObject level4;
	public GameObject level5;
	public GameObject locked1;
	public GameObject locked2;
	public GameObject locked3;
	public GameObject locked4;
	public GameObject locked5;
	private int progress;

    // Unlock levels based on progress
	void Start()
    {
		Unlock ();
	}

    // Load progress
	public void Unlock ()
	{
		string path = "Assets/Resources/story.dat";

		// Streamreader to get the lifetime points
		StreamReader read = new StreamReader (path);

		read.ReadLine ();
		string p = read.ReadLine ();

		// Close the file
		read.Close ();

		progress = Convert.ToInt32 (p);

		if (progress == 0)
        {
			level1.SetActive (false);
			locked1.SetActive (true);
			level2.SetActive (false);
			locked2.SetActive (true);
			level3.SetActive (false);
			locked3.SetActive (true);
			level4.SetActive (false);
			locked4.SetActive (true);
			level5.SetActive (false);
			locked5.SetActive (true);
		} 
		else if (progress == 1)
        {
			level1.SetActive (true);
			locked1.SetActive (false);
			level2.SetActive (false);
			locked2.SetActive (true);
			level3.SetActive (false);
			locked3.SetActive (true);
			level4.SetActive (false);
			locked4.SetActive (true);
			level5.SetActive (false);
			locked5.SetActive (true);
		} 
		else if (progress == 2)
        {
			level1.SetActive (true);
			locked1.SetActive (false);
			level2.SetActive (true);
			locked2.SetActive (false);
			level3.SetActive (false);
			locked3.SetActive (true);
			level4.SetActive (false);
			locked4.SetActive (true);
			level5.SetActive (false);
			locked5.SetActive (true);
		} 
		else if (progress == 3)
        {
			level1.SetActive (true);
			locked1.SetActive (false);
			level2.SetActive (true);
			locked2.SetActive (false);
			level3.SetActive (true);
			locked3.SetActive (false);
			level4.SetActive (false);
			locked4.SetActive (true);
			level5.SetActive (false);
			locked5.SetActive (true);
		} 
		else if (progress == 4)
        {
			level1.SetActive (true);
			locked1.SetActive (false);
			level2.SetActive (true);
			locked2.SetActive (false);
			level3.SetActive (true);
			locked3.SetActive (false);
			level4.SetActive (true);
			locked4.SetActive (false);
			level5.SetActive (false);
			locked5.SetActive (true);
		} 
		else
        {
			level1.SetActive (true);
			locked1.SetActive (false);
			level2.SetActive (true);
			locked2.SetActive (false);
			level3.SetActive (true);
			locked3.SetActive (false);
			level4.SetActive (true);
			locked4.SetActive (false);
			level5.SetActive (true);
			locked5.SetActive (false);
		}

	}
}
