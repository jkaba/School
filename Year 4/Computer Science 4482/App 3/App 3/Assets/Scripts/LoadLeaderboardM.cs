using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using System.IO;

// LoadLeaderboardM class this class loads the leaderboard from the main menu
public class LoadLeaderboardM : MonoBehaviour
{
    // Variables
    public Text first;
    public Text second;
    public Text third;
    public Text fourth;
    public Text fifth;

    void Start()
    {
        // Load the scores
        string path = "Assets/Resources/save.txt";
        StreamReader read = new StreamReader(path);

        // Skip the first line (lifetime points)
        read.ReadLine();

        // Alternate between name and score on each line
        string name1 = read.ReadLine();
        string score1 = read.ReadLine();
        first.text = "1: " + name1 + " " + score1;
        string name2 = read.ReadLine();
        string score2 = read.ReadLine();
        second.text = "2: " + name2 + " " + score2;
        string name3 = read.ReadLine();
        string score3 = read.ReadLine();
        third.text = "3: " + name3 + " " + score3;
        string name4 = read.ReadLine();
        string score4 = read.ReadLine();
        fourth.text = "4: " + name4 + " " + score4;
        string name5 = read.ReadLine();
        string score5 = read.ReadLine();
        fifth.text = "5: " + name5 + " " + score5;

        // Close the file
        read.Close();
    }
}
