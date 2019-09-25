using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

// This class is from the Unity Tutorial "Making a Main Menu"

public class LoadSceneOnClicked : MonoBehaviour {

    /*
     * LoadByIndex method that takes an int representing 
     * a scene as the parameter
     */
    public void LoadByIndex(int sceneIndex)
    {
        SceneManager.LoadScene(sceneIndex);
    }
}
