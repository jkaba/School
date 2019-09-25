using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
using UnityEngine.UI;
using System.IO;
using System;

public class LoadPowerUp : MonoBehaviour {

    // Variables
	string lPoints = "";
	int lp;
	public GameObject power1;
	public GameObject power2;
	public GameObject power3;
	public GameObject power4;
	public GameObject power5;
	public GameObject lock1;
	public GameObject lock2;
	public GameObject lock3;
	public GameObject lock4;
	public GameObject lock5;

    // Unlock based on total lifepoints
	void Start()
    {
		Unlock ();
	}

	// Unlock based on loaded lifepoints
	public void Unlock ()
    {
		string path = "Assets/Resources/save.txt";

		// Streamreader to get the lifetime points
		StreamReader read = new StreamReader(path);

		// get the lifetime points
		lPoints = read.ReadLine();

		// Close the StreamReader
		read.Close();

		// Convert the text into an int
		lp = Convert.ToInt32(lPoints);

        if (lp >= 500000)
        {
            power1.SetActive(true);
            lock1.SetActive(false);
            power2.SetActive(true);
            lock2.SetActive(false);
            power3.SetActive(true);
            lock3.SetActive(false);
            power4.SetActive(true);
            lock4.SetActive(false);
            power5.SetActive(true);
            lock5.SetActive(false);
        }
        else if (lp >= 400000)
        {
            power1.SetActive(true);
            lock1.SetActive(false);
            power2.SetActive(true);
            lock2.SetActive(false);
            power3.SetActive(true);
            lock3.SetActive(false);
            power4.SetActive(true);
            lock4.SetActive(false);
            power5.SetActive(false);
            lock5.SetActive(true);
        }
        else if (lp >= 300000)
        {
            power1.SetActive(true);
            lock1.SetActive(false);
            power2.SetActive(true);
            lock2.SetActive(false);
            power3.SetActive(true);
            lock3.SetActive(false);
            power4.SetActive(false);
            lock4.SetActive(true);
            power5.SetActive(false);
            lock5.SetActive(true);
        }
        else if (lp >= 200000)
        {
            power1.SetActive(true);
            lock1.SetActive(false);
            power2.SetActive(true);
            lock2.SetActive(false);
            power3.SetActive(false);
            lock3.SetActive(true);
            power4.SetActive(false);
            lock4.SetActive(true);
            power5.SetActive(false);
            lock5.SetActive(true);
        }
        else if (lp >= 100000)
        {
            power1.SetActive(true);
            lock1.SetActive(false);
            power2.SetActive(false);
            lock2.SetActive(true);
            power3.SetActive(false);
            lock3.SetActive(true);
            power4.SetActive(false);
            lock4.SetActive(true);
            power5.SetActive(false);
            lock5.SetActive(true);
        }
        else
        {
            power1.SetActive(false);
            lock1.SetActive(true);
            power2.SetActive(false);
            lock2.SetActive(true);
            power3.SetActive(false);
            lock3.SetActive(true);
            power4.SetActive(false);
            lock4.SetActive(true);
            power5.SetActive(false);
            lock5.SetActive(true);
        }
	}
}
