using System.Collections;
using System.Collections.Generic;
using UnityEngine;

// This class is from the Unity tutorial "Making a Main Menu"

public class QuitOnClicked : MonoBehaviour {
    public void Quit()
    {
        // If in the Unity Editor set isPlaying to false
#if UNITY_EDITOR
        UnityEditor.EditorApplication.isPlaying = false;
        // Else quit the App
#else
        Application.Quit();
#endif
    }
}
