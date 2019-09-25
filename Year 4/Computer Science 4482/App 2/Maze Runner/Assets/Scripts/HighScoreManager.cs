using UnityEngine;
using System.Collections;
using System.Collections.Generic;
using System;
using UnityEngine.UI;
using System.IO;

/*
 * High Score Manager class is used in game
 * once the game is over and the leader board appears
 * rankings are loaded, changed if necessary, and saved
 */
public class HighScoreManager : MonoBehaviour
{

    // Lot's of public variables
    public PlayerMovement player;
    public Text Name1;
    public Text Score1;
    public Text Name2;
    public Text Score2;
    public Text Name3;
    public Text Score3;
    public Text Name4;
    public Text Score4;
    public Text Name5;
    public Text Score5;
    public Text congratsText;
    public InputField nameField;

    // Start method, to initialize the leaderboard
    void Start()
    {
        // Load up the rankings
        Load();

        // Convert top 5 scores into int values for comparison
        int first = Convert.ToInt32(Score1.text);
        int second = Convert.ToInt32(Score2.text);
        int third = Convert.ToInt32(Score3.text);
        int fourth = Convert.ToInt32(Score4.text);
        int five = Convert.ToInt32(Score5.text);

        // Make copies of top 4 names, in case of player making top 5
        string nameCopy1 = Name1.text;
        string nameCopy2 = Name2.text;
        string nameCopy3 = Name3.text;
        string nameCopy4 = Name4.text;

        // Player ranks 1st
        if (player.finalScore > first)
        {
            // Show Congratulations text
            congratsText.gameObject.SetActive(true);

            // Update first place ranking with player name and score
            Name1.text = player.userName;
            Score1.text = player.finalScore + "";

            // Update second place ranking
            Name2.text = nameCopy1;
            Score2.text = first + "";

            // Update third place ranking
            Name3.text = nameCopy2;
            Score3.text = second + "";

            // Update fourth place ranking
            Name4.text = nameCopy3;
            Score4.text = third + "";

            // Update fifth place ranking
            Name5.text = nameCopy4;
            Score5.text = fourth + "";
        }

        // Player ranks 2nd
        else if (player.finalScore > second)
        {
            // Set Congratulations text to be active
            congratsText.gameObject.SetActive(true);

            // Update 2nd place ranking;
            Name2.text = player.userName;
            Score2.text = player.finalScore + "";

            // Update 3rd place ranking;
            Name3.text = nameCopy2;
            Score3.text = second + "";

            // Update 4th place ranking;
            Name4.text = nameCopy3;
            Score4.text = third + "";

            // Update 5th place ranking;
            Name5.text = nameCopy4;
            Score5.text = fourth + "";
        }

        // Player ranks 3rd
        else if (player.finalScore > third)
        {
            // Set congratulations text to be active
            congratsText.gameObject.SetActive(true);

            // Update 3rd place ranking
            Name3.text = player.userName;
            Score3.text = player.finalScore + "";

            // Update 4th place ranking
            Name4.text = nameCopy3;
            Score4.text = third + "";

            // Update 5th place ranking
            Name5.text = nameCopy4;
            Score5.text = fourth + "";
        }

        // Player ranks 4th
        else if (player.finalScore > fourth)
        {
            // Set congratulations text to be active
            congratsText.gameObject.SetActive(true);

            // Update 4th place
            Name4.text = player.userName;
            Score4.text = player.finalScore + "";

            // Update 5th place
            Name5.text = nameCopy4;
            Score5.text = fourth + "";
        }

        // Player ranks 5th
        else if (player.finalScore > five)
        {
            // Set congratulations text to be active
            congratsText.gameObject.SetActive(true);

            // Update 5th place ranking
            Name5.text = player.userName;
            Score5.text = player.finalScore + "";
        }
        // Save updated rankings
        Save();
    }

    // Load method to load up rankings
    void Load()
    {
        // Path to File
        string path = "Assets/Resources/save.txt";

        // Create a StreamReader
        StreamReader read = new StreamReader(path);

        // File formated with name in 1 line, score in next
        Name1.text = read.ReadLine();
        Score1.text = read.ReadLine();
        Name2.text = read.ReadLine();
        Score2.text = read.ReadLine();
        Name3.text = read.ReadLine();
        Score3.text = read.ReadLine();
        Name4.text= read.ReadLine();
        Score4.text = read.ReadLine();
        Name5.text = read.ReadLine();
        Score5.text = read.ReadLine();
        
        // Close the StreamReader 
        read.Close();
    }

    // Save method to save the rankings
    void Save()
    {
        // Path to File set as a string
        string path = "Assets/Resources/save.txt";

        // Create a Stream Writer, that overwrites the contents
        StreamWriter writer = new StreamWriter(path, false);

        // Save rankings with name in 1 line and score in the following
        writer.WriteLine(Name1.text);
        writer.WriteLine(Score1.text);
        writer.WriteLine(Name2.text);
        writer.WriteLine(Score2.text);
        writer.WriteLine(Name3.text);
        writer.WriteLine(Score3.text);
        writer.WriteLine(Name4.text);
        writer.WriteLine(Score4.text);
        writer.WriteLine(Name5.text);
        writer.WriteLine(Score5.text);

        // Close the StreamWriter
        writer.Close();
    }
}

