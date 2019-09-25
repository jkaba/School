using UnityEngine;
using UnityEngine.SceneManagement;
using UnityEngine.UI;
using System.IO;
using System;

/*
 * GameOverScript class
 * This script is run once the player is out of lives
 */
public class GameoverScript : MonoBehaviour
{
    // Lots of variables
    public Text Score1;
    public Text Score2;
    public Text Score3;
    public Text Score4;
    public Text Score5;
    public Text lp;
    public Text congrats;
    private string name1;
    private string name2;
    private string name3;
    private string name4;
    private string name5;
    private string s1;
    private string s2;
    private string s3;
    private string s4;
    private string s5;
    private string lifeCopy;
    public string playerName;
    public int score;

    // Display method which takes a bool to determine whether to show the screen
    public void Display(bool show)
    {
        // Set the gameOver screen to whatever the value of show is
        this.gameObject.SetActive(show);
    }

    // Alternate Display method used when game is over, takes a bool and an int
    public void Display2(bool show, int score)
    {
        // The display should be active/true
        this.gameObject.SetActive(show);

        // Call Load method to load up the scores
        Load();

        // Convert the scores from the file into ints
        int first = Convert.ToInt32(s1);
        int second = Convert.ToInt32(s2);
        int third = Convert.ToInt32(s3);
        int fourth = Convert.ToInt32(s4);
        int five = Convert.ToInt32(s5);
        int life = Convert.ToInt32(lp.text);

        // Increase and update the lifetime total score
        life += score;
        lp.text = "LifeTime Total: " + life;
        this.lifeCopy = life + "";

        // Make copies of top 4 names, in case of player making top 5
        string nameCopy1 = name1;
        string nameCopy2 = name2;
        string nameCopy3 = name3;
        string nameCopy4 = name4;
   
        // Player ranks 1st
        if (score > first)
        {
            // Show Congratulations text
            congrats.gameObject.SetActive(true);

            // Update first place ranking with player name and score
            this.name1 = playerName;
            this.s1 = score + "";
            Score1.text = "1: " + name1 + " " + s1;

            // Update second place ranking
            this.name2 = nameCopy1;
            this.s2 = first + "";
            Score2.text = "2: " + name2 + " " + s2;

            // Update third place ranking
            this.name3 = nameCopy2;
            this.s3 = second + "";
            Score3.text = "3: " + name3 + " " + s3;

            // Update fourth place ranking
            this.name4 = nameCopy3;
            this.s4 = third + "";
            Score4.text = "4: " + name4 + " " + s4;

            // Update fifth place ranking
            this.name5 = nameCopy4;
            this.s5 = fourth + "";
            Score5.text = "5: " + name5 + " " + s5;
        }

        // Player ranks 2nd
        else if (score > second)
        {
            // Set Congratulations text to be active
            congrats.gameObject.SetActive(true);

            // Update 2nd place ranking;
            this.name2 = playerName;
            this.s2 = score + "";
            Score2.text = "2: " + name2 + " " + s2;

            // Update 3rd place ranking;
            this.name3 = nameCopy2;
            this.s3 = second + "";
            Score3.text = "3: " + name3 + " " + s3;

            // Update 4th place ranking;
            this.name4 = nameCopy3;
            this.s4 = third + "";
            Score4.text = "4: " + name4 + " " + s4;

            // Update 5th place ranking;
            this.name5 = nameCopy4;
            this.s5 = fourth + "";
            Score5.text = "5: " + name5 + " " + s5;
        }

        // Player ranks 3rd
        else if (score > third)
        {
            // Set congratulations text to be active
            congrats.gameObject.SetActive(true);

            // Update 3rd place ranking
            this.name3 = playerName;
            this.s3 = score + "";
            Score3.text = "3: " + name3 + " " + s3;

            // Update 4th place ranking
            this.name4 = nameCopy3;
            this.s4 = third + "";
            Score4.text = "4: " + name4 + " " + s4;

            // Update 5th place ranking
            this.name5 = nameCopy4;
            this.s5 = fourth + "";
            Score5.text = "5: " + name5 + " " + s5;
        }

        // Player ranks 4th
        else if (score > fourth)
        {
            // Set congratulations text to be active
            congrats.gameObject.SetActive(true);

            // Update 4th place
            this.name4 = playerName;
            this.s4 = score + "";
            Score4.text = "4: " + name4 + " " + s4;

            // Update 5th place
            this.name5 = nameCopy4;
            this.s5 = fourth + "";
            Score5.text = "5: " + name5 + " " + s5;
        }

        // Player ranks 5th
        else if (score > five)
        {
            // Set congratulations text to be active
            congrats.gameObject.SetActive(true);

            // Update 5th place ranking
            this.name5 = playerName;
            this.s5 = score + "";
            Score5.text = "5: " + name5 + " " + s5;
        }

        // Call the Save method to save scores
        Save();
    }

    void Load()
    {
        // Path to File
        string path = "Assets/Resources/save.txt";

        // Create a StreamReader
        StreamReader read = new StreamReader(path);

        // First line is the lifetime score
        lp.text = read.ReadLine();

        // Remaining lines alternate between name and score
        this.name1 = read.ReadLine();
        this.s1 = read.ReadLine();
        this.name2 = read.ReadLine();
        this.s2 = read.ReadLine();
        this.name3 = read.ReadLine();
        this.s3 = read.ReadLine();
        this.name4 = read.ReadLine();
        this.s4 = read.ReadLine();
        this.name5 = read.ReadLine();
        this.s5 = read.ReadLine();

        // Close the file
        read.Close();
        
        // Load up the name file to get the player name
        string path2 = "Assets/Resources/name.txt";
        read = new StreamReader(path2);

        // Set the player name
        playerName = read.ReadLine();

        // Close the file
        read.Close();
    }

    void Save()
    {
        // Path to File set as a string
        string path = "Assets/Resources/save.txt";

        // Create a Stream Writer, that overwrites the contents
        StreamWriter writer = new StreamWriter(path, false);

        // Save the lifetime score in the first line
        writer.WriteLine(lifeCopy);

        // Save the name and score in alternating lines
        writer.WriteLine(name1);
        writer.WriteLine(s1);
        writer.WriteLine(name2);
        writer.WriteLine(s2);
        writer.WriteLine(name3);
        writer.WriteLine(s3);
        writer.WriteLine(name4);
        writer.WriteLine(s4);
        writer.WriteLine(name5);
        writer.WriteLine(s5);

        // Close the StreamWriter
        writer.Close();
    }
}