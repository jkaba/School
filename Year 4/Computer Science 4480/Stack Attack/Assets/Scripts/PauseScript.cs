using System.Collections;
using System.Collections.Generic;
using UnityEngine;

/// <summary>
/// This class handles pausing the game. It is based on the video 
/// found here: https://www.youtube.com/watch?v=PyEmRVRHWL8
/// </summary>
public class PauseScript : MonoBehaviour
{
    public Transform canvas;    
	
	void Update ()
    {
		if(Input.GetKeyDown(KeyCode.Escape))
        {
            PauseGame();
        }
	}

    public void PauseGame()
    {
        if (canvas.gameObject.activeInHierarchy == false)
        {
            canvas.gameObject.SetActive(true);
            Time.timeScale = 0.0f;
        }
        else
        {
            canvas.gameObject.SetActive(false);
            Time.timeScale = 1.0f;
        }
    }
}
