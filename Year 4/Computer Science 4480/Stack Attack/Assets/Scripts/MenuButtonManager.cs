using System.Collections;
using UnityEngine;
using UnityEngine.SceneManagement;

/// <summary>
/// Allows buttons to move between scenes and allows the user to 
/// quit the game in both a game build and in the editor.
/// </summary>
public class MenuButtonManager : MonoBehaviour
{

    /// <summary>
    /// Allows user to select scene to load on-click.
    /// </summary>
    /// <param name="sceneIndex">Scene index.</param>
    public void LoadByIndex(int sceneIndex)
    {
        StartCoroutine(LoadSceneWithWait(sceneIndex));
    }

    public void LoadByName(string name)
    {
        SceneManager.LoadScene(name);
    }

    IEnumerator LoadSceneWithWait(int sceneIndex)
    {
        yield return new WaitForSeconds(0.3f);
        SceneManager.LoadScene(sceneIndex);
    }

    /// <summary>
    /// Allows a user to quit the game in both the editor and from
    /// the actual game.
    /// </summary>
    public void ExitGame()
    {
#if UNITY_EDITOR

        UnityEditor.EditorApplication.isPlaying = false;
#else
        Application.Quit();

#endif
    }
}