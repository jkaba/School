using System.Collections;
using System.Collections.Generic;
using UnityEngine;

// QuitonClicked Class used to quit the application
public class QuitOnClicked : MonoBehaviour {
    public void Quit()
    {
        // If in the Unity_Editor then set isPlaying to false
#if UNITY_EDITOR
        UnityEditor.EditorApplication.isPlaying = false;
        // Else Quit the Application
#else
        Application.Quit();
#endif
    }
}
