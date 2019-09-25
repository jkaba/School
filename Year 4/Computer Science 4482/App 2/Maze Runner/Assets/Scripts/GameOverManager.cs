using System.Collections;
using System.Collections.Generic;
using UnityEngine;

/*
 * GameOverManager class
 * This class handles the ending sequence once player.gameOver is true
 * This class also handles the opening and closing of both the pause
 * and Name Entry menus
 */
public class GameOverManager : MonoBehaviour {

    // Public Variables
    public PlayerMovement player;
    public float restart = 5f;
    Animator anim;
    float restartTimer;
    bool pause = false;

    // Panels which open and close
    public GameObject nameEntry;
    public GameObject leaderboard;
    public GameObject pauseMenu;

    void Awake()
    {
        anim = GetComponent<Animator>();
    }
    private void Update()
    {
        // If the game is over
        if(player.gameOver == true)
        {
            // Run GameOver animation
            anim.SetTrigger("GameOver");

            // Timer for transition
            restartTimer += Time.deltaTime;

            // When timer hits set time, activate the leaderboard
            if(restartTimer >= restart)
            {
                leaderboard.SetActive(true);
            }
        }

        // If the game is paused, open the pause menu
        if(Input.GetKeyDown(KeyCode.Escape) == true)
        {
            if (pause == true)
            {
                pause = false;
                player.pause = false;
                pauseMenu.SetActive(false);
                
            }
            else
            {
                pause = true;
                player.pause = true;
                pauseMenu.SetActive(true);
                
            }
        }

        // If the game has just started, then open the NameEntry screen
        if(player.start == true)
        {
            nameEntry.SetActive(true);
        }

        // If the player name has been entered, close the NameEntry screen
        if(player.start == false)
        {
            nameEntry.SetActive(false);
        }
    }
}
