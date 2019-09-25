using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using System.IO;

/*
 * LoadLeaderBoard class
 * This class is only run when the leaderboard panel is opened
 * from the main menu
 */
public class LoadLeaderBoard : MonoBehaviour {

    // Score Rankings / Public Variables
    public Text first;
    public Text second;
    public Text third;
    public Text fourth;
    public Text fifth;

	// Start method, loads the names, and scores from a file and updates rankings
	void Start () {
        // Set file location as a path
        string path = "Assets/Resources/save.txt";

        // Set up a StreamReader to read the file
        StreamReader read = new StreamReader(path);

        // Get first place name and score
        string name1 = read.ReadLine();
        string score1 = read.ReadLine();

        // Update the first place ranking
        first.text = "1) " + name1 + " " + score1;

        // Get second place name and score
        string name2 = read.ReadLine();
        string score2 = read.ReadLine();

        // Update the second place ranking
        second.text = "2) " + name2 + " " + score2;

        // Get third place name and score
        string name3 = read.ReadLine();
        string score3 = read.ReadLine();

        // Update the third place ranking
        third.text = "3) " + name3 + " " + score3;

        // Get fourth place name and score
        string name4 = read.ReadLine();
        string score4 = read.ReadLine();

        // Update the fourth place ranking
        fourth.text = "4) " + name4 + " " + score4;

        // Get fifth place name and score
        string name5 = read.ReadLine();
        string score5 = read.ReadLine();

        // Update the fifth place ranking 
        fifth.text = "5) " + name5 + " " + score5;

        // Close the StreamReader
        read.Close();
    }
	
}
