using UnityEngine;
using UnityEngine.UI;
using System.IO;
using System;

public class StoryGameScript : MonoBehaviour
{
	// Global variables, lot's of global variables

	// GameObject Variables
	public GameObject Enemyprefab;
	public GameObject EnemyLaser;
	public GameObject EnemySpaceship;
	public GameObject Gameover;
	public BossScript Boss;
	GameObject[,] enemys;
	public GameObject pauseMenu;

	// Script Variables
	public Paddle p1;
	public Ball ball;
	public GameObject gameoverScript;
	public GameObject victory;

	// Text variables
	public Text scoreboard;
	public Text liveCount;
	public Text timer;

	// float, int, and bool variables
	float xStartOffset = -10;
	float yStartOffset = 2f;
	public int lives = 3;
	public int Score = 0;
	public int level = 0;
	public float countdown = 0;
	int count = 0;
	float timesinceLastTurn = 0;
	float laserchance = 0.7f;
	int enemyLaseractivity = 0;
	public bool pause = false;
	public bool complete = false;
	public bool end = false;
	int type;
	int ballCount = 1;

	void Start ()
	{      
        // Load up the level
		string path = "Assets/Resources/story.dat";
		StreamReader read = new StreamReader (path);
		string pType = read.ReadLine ();
		level = Convert.ToInt32 (pType);
		
        // Close the file
		read.Close ();
 
		// Create a new game
		this.NewGame ();
	}


	void NewLevel (int level)
	{
		// Spawn a wave of enemies based on level

		if (level == 1)
        {
			enemys = new GameObject[15, 1];
			timer.gameObject.SetActive (false);
			for (int y = 0; y < 1; y++)
            {
				for (int x = 0; x < 15; x++)
                {
					enemys [x, y] = (GameObject)Instantiate (this.Enemyprefab, new Vector3 (x * 1.3f + xStartOffset, y * 1.1f + yStartOffset, 0), Quaternion.AngleAxis (89, Vector3.up));
					enemys [x, y].GetComponent<Enemy> ().SetEnemyType (y);
				}
			}
		}

		if (level == 2)
        {
			laserchance += 0.01f;
			enemys = new GameObject[10, 5];
			countdown = 120;
			timer.text = "Time: 2:00";
			for (int y = 0; y < 5; y++)
            {
				for (int x = 0; x < 10; x++)
                {
					enemys [x, y] = (GameObject)Instantiate (this.Enemyprefab, new Vector3 (x * 1.3f + xStartOffset, y * 1.1f + yStartOffset, 0), Quaternion.AngleAxis (89, Vector3.up));
					enemys [x, y].GetComponent<Enemy> ().SetEnemyType (y);
				}
			}
		}

		if (level == 3)
        {
			countdown = 180;
			timer.text = "Time: 3:00";
			enemys = new GameObject[15, 2];
			for (int y = 0; y < 2; y++)
            {
				for (int x = 0; x < 15; x++)
                {
					enemys [x, y] = (GameObject)Instantiate (this.Enemyprefab, new Vector3 (x * 1.3f + xStartOffset, y * 1.1f + yStartOffset, 0), Quaternion.AngleAxis (89, Vector3.up));
					enemys [x, y].GetComponent<Enemy> ().SetEnemyType (y);
				}
			}
		}

		if (level == 4)
        {
			laserchance += 0.01f;
			enemys = new GameObject[10, 5];
			timer.gameObject.SetActive (false);
			for (int y = 0; y < 5; y++)
            {
				for (int x = 0; x < 10; x++)
                {
					if (y % 2 != 0)
                    {
						if (x % 2 != 0)
                        {
							enemys [x, y] = (GameObject)Instantiate (this.Enemyprefab, new Vector3 (x * 1.3f + xStartOffset, y * 1.1f + yStartOffset, 0), Quaternion.AngleAxis (89, Vector3.up));
							enemys [x, y].GetComponent<Enemy> ().SetEnemyType (y);
						}
					}
                    else if (x % 2 == 0)
                    {
						enemys [x, y] = (GameObject)Instantiate (this.Enemyprefab, new Vector3 (x * 1.3f + xStartOffset, y * 1.1f + yStartOffset, 0), Quaternion.AngleAxis (89, Vector3.up));
						enemys [x, y].GetComponent<Enemy> ().SetEnemyType (y);
					} 

				}
			}
		}

        if (level == 5)
        {
            timer.gameObject.SetActive(false);
            Boss.gameObject.SetActive(true);
            scoreboard.text = "Boss Health: " + Boss.health;
        }
	}

	void NewGame ()
	{
        // Set enemy parameters based on level
		if (level == 1 || level == 3)
        {
			// Assign values
			laserchance = 0.1f;
			Enemy.enemyMoveSpeed = 0;
		}
        else
        {
			laserchance = 0.1f;
			Enemy.enemyMoveSpeed = 0.5f;
		}
        
        // Set up how many enemies remain
		scoreboard.text = "Enemies Remaining: " + 0;

		// Create/Start a new level
		NewLevel (level);

        // Set up life counter
		lives = 3;
		liveCount.text = "Lives Left: " + 3;
	}

	public void Killed ()
	{
		// If the player is out of lives
		if (lives == 0) {

			// Display the leaderboard
			gameoverScript.gameObject.SetActive (true);
			end = true;
		}
        else
        {
            // subtract ball count
			ballCount--;

            // If no more balls, lose a life
			if (ballCount == 0)
            {
				// Take a life away
				lives--;
				liveCount.text = "Lives Left: " + lives;

				ball.dead ();
				ballCount = 1;

			}
		} 
	}

	public void Win ()
	{
        // If level complete, then display continue
		if (complete == true)
        {
			victory.gameObject.SetActive (true);
		}
	}

	public void CountTimer ()
	{
		if (pause == false && ball.hasStarted == true && complete == false && end == false)
        {
			// Decrease timer by 1 second
			countdown -= Time.deltaTime;
			timer.text = "Time: " + countdown;

			// Round the minute value
			float minutes = Mathf.Floor (countdown / 60);

			// Round the seconds value
			float seconds = Mathf.Floor (countdown % 60); 

			// If time runs out, then game over based on level
			if (minutes == 0 && seconds == 0)
            {
				if (level == 2)
                {
					complete = true;
				}
                else
                {
					lives = 0;
					Killed ();
				}
			}

			// Initialize text for seconds
			string secondsText = "";

			// If less than 10 seconds, add a 0 before seconds value
			if (seconds < 10)
            {
				secondsText = "0" + seconds.ToString ();
			}

			// Otherwise, set text for seconds to contain seconds value
			else
            {
				secondsText = seconds.ToString ();
			}

			// Update the timer text
			timer.text = "Time: " + minutes + ":" + secondsText;
		}
	}

	void Update ()
	{
        // Check if level complete
		Win ();

		// If the player presses 'esc' pause/unpause the game
		if (Input.GetKeyDown (KeyCode.Escape) == true && this.ball.hasStarted == false)
        {

			// If the Game is paused
			if (pause == true)
            {
				// Set pause to false
				pause = false;

				// Retain the enemy move speed
				Enemy.enemyMoveSpeed = 0.5f;
				EnemySpaceshipScript.enemyMoveSpeed = 4f;

				// Unactivate the pause menu
				pauseMenu.SetActive (false);
			}
            else
            {
				// Pause to true
				pause = true;

				// Display the pause menu
				pauseMenu.SetActive (true);

				// Stop enemy movement
				Enemy.enemyMoveSpeed = 0;
				EnemySpaceshipScript.enemyMoveSpeed = 0;
                
			}
		}

		// If the game is not paused
		if (pause == false)
        {
			if (Input.GetKeyDown (KeyCode.Escape) && this.ball.hasStarted == true)
            {
				Killed ();
			}

			CountTimer ();
			// For each enemy
			count = 0;
			if (level != 5)
            {
				foreach (GameObject go in enemys)
                {
			
					// Change direction
					if (go != null && (go.transform.position.x > 11 || go.transform.position.x < -11) && Time.time > this.timesinceLastTurn)
                    {
						this.timesinceLastTurn = Time.time + 1;
						{
							Enemy.enemyMoveDir = Enemy.enemyMoveDir * -1;
						}
					}

					// Shoot lasers
					if (UnityEngine.Random.Range (0, enemyLaseractivity) == 1 && go != null)
                    {
						Instantiate (this.EnemyLaser, go.transform.position, Quaternion.identity);
					}

					// For each enemy alive, increment count
					if (go != null && go.activeInHierarchy)
                    {
						count++;
						scoreboard.text = "Enemies Remaining: " + (count);
					}
				}

				// If no more enemies are alive, level complete
				if (count == 0)
                {
					complete = true;
				}

				// Set the laser activity
				enemyLaseractivity = (int)((count % 50) * 20 / laserchance);

				if (level == 1)
                {
					enemyLaseractivity = (int)((count % 15) * 20 / laserchance);
				}
                else if (level == 2 || level == 4)
                {
					enemyLaseractivity = (int)((count % 50) * 20 / laserchance);
				}
                else if (level == 3)
                {
					enemyLaseractivity = (int)((count % 30) * 20 / laserchance);
				} 
			}
            else if (level == 5 && complete == false)
            {
				scoreboard.text = "Boss Health: " + Boss.health;
				enemyLaseractivity = (int)((1 % 10) * 20 / 0.5);
			
				if (UnityEngine.Random.Range (0, enemyLaseractivity) == 1)
                {
					int rand = UnityEngine.Random.Range (-11, 11);
					Vector3 sp = new Vector3 (this.Boss.transform.position.x + rand, this.Boss.transform.position.y, this.Boss.transform.position.z);
					Instantiate (this.EnemyLaser, sp, Quaternion.identity);
				}
			}
		}
	}
}
