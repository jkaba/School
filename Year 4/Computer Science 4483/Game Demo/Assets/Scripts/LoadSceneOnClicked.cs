using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

// LoadSceneOnClicked class this class loads a scene by its index
public class LoadSceneOnClicked : MonoBehaviour {

    public void LoadByIndex(int sceneIndex)
    {
        // Load the Scene specified by the int passed through
        SceneManager.LoadScene(sceneIndex);
    }
}
