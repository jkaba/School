using UnityEngine;
using UnityEngine.UI;
using System.IO;
using System;

// Reused and Modified from previous project

public class GameScript : MonoBehaviour
{
    // Global variables, lot's of global variables

    // GameObject Variables
    public GameObject Enemyprefab;
    public GameObject EnemyLaser;
    public GameObject EnemySpaceship;
    public GameObject Block;
    public GameObject Gameover;
    GameObject[,] enemys;
    public GameObject pauseMenu;

    // Script Variables
	public Paddle p1;
	public Paddle bigp1;
	public Ball ball;
	public Ball clone1;
	public Ball clone2;
	public Ball large;
    private GameoverScript gameoverScript;

    // Text variables
    public Text scoreboard;
    public Text liveCount;

    // float, int, and bool variables
    float xStartOffset = -10;
    float yStartOffset = 2f;
    public int lives = 3;
    public int Score = 0;
    public int powerType = 0;
    float timesinceLastTurn = 0;
    float powerTime = 0;
    float laserchance = 0.7f;
    int enemyLaseractivity = 0;
    int extraLife = 0;
    public bool pause = false;
    int spaceship = 0;
    private bool pUp = false;
	int type;
	int ballCount = 1;

    void Start()
    {      
        // Load and apply powerup
		string path = "Assets/Resources/survival.txt";
		StreamReader read = new StreamReader(path);
		string pType = read.ReadLine();
		powerType = Convert.ToInt32(pType);

		// Close the file
		read.Close();

        // Find the gameover script
        gameoverScript = GameObject.Find("GameOverModel").GetComponent<GameoverScript>();

		if (powerType == 1)
        {
			p1.gameObject.SetActive (false);
			bigp1.gameObject.SetActive (true);
		} 
		else if (powerType == 2)
        {
			ball.gameObject.SetActive (false);
			large.gameObject.SetActive (true);
			large.type = 1;
		}
		else if (powerType == 3)
        {
			clone1.gameObject.SetActive (true);
			clone2.gameObject.SetActive (true);
			ballCount = 3;
		}
		else if (powerType == 5)
        {
			p1.type = 2;
		}

        // Create a new game
        this.NewGame();
    }

    public void AddToScore(string enemyTag)
    {
        // If spaceships haven't been spawned
        if (spaceship == 0)
        {
            // If score is >= 1000, then spawn a spaceship
            if (Score >= 1000)
            {
                Instantiate(this.EnemySpaceship, new Vector3(-20, 8, 0), Quaternion.AngleAxis(89, Vector3.up));
                spaceship++;
            }
        }
        else
        {
            // For every 1000 points spawn a spaceship
            if(Score >= ( 1000 * (spaceship + 1)))
            {
                Instantiate(this.EnemySpaceship, new Vector3(-20, 8, 0), Quaternion.AngleAxis(89, Vector3.up));
                spaceship++;
            }
        }

        // Switch case to give points based on the enemy killed
        switch (enemyTag)
        {
            case "EnemyThree":
                Score += 100;
                break;
            case "EnemyTwo":
                Score += 200;
                break;
            case "EnemyOne":
                Score += 300;
                break;
            case "EnemySpaceship":
                Score += 500;
                break;
            default:
                Score += 100;
                break;
        }

        // Update the score text
        scoreboard.text = "Score: " + Score;
        
        // If the player has not gotten an extra life
        if(extraLife == 0)
        {
            // If score >= 1000 then player gets an extra life, update life text
            if(Score >= 1000)
            {
                lives++;
                liveCount.text = "Lives Left: " + lives;
                extraLife++;
            }
        }
        else
        {
            // For every 10000 points the player gets an extra life
            if (Score >= (10000 * (extraLife + 1)))
            {
                lives++;
                liveCount.text = "Lives Left: " + lives;

                extraLife++;
            }
        }
        
    }

    void NewLevel()
    {
        // Assign values
        laserchance += 0.01f;
        Enemy.enemyMoveSpeed += 0.5f;
		if (powerType == 4)
        {
			enemyTime ();
		}

        // Spawn a wave of enemies
        enemys = new GameObject[10, 5];

         
        for (int y = 0; y < 5; y++)
        {
            for (int x = 0; x < 10; x++)
            {
                enemys[x, y] = (GameObject)Instantiate(this.Enemyprefab, new Vector3(x * 1.3f + xStartOffset, y * 1.1f + yStartOffset, 0), Quaternion.AngleAxis(89, Vector3.up));
                enemys[x, y].GetComponent<Enemy>().SetEnemyType(y);
            }
        }
    }

    void NewGame()
    {
        // Assign values
        laserchance = 0.7f;
        Enemy.enemyMoveSpeed = 2;
        scoreboard.text = "Score: " + 0;
        extraLife = 0;

        // Create/Start a new level
        NewLevel();

        // Do not display the leaderboard
        gameoverScript.Display(false);

        // Player starts with 3 lives
        lives = 3;
        liveCount.text = "Lives Left: " + 3;

    }


    public void Killed()
    {
        // If the player is out of lives
        if (lives == 0)
        {
            // Display the leaderboard
            gameoverScript.Display2(true, Score);
        }
        else
        {
            print(ballCount);
            ballCount--;
            if (ballCount == 0)
            {
                // Take a life away
                lives--;
                liveCount.text = "Lives Left: " + lives;
                if (powerType == 2)
                {
                    large.dead();
                    ballCount = 1;
                }
                else if (powerType == 3)
                {
                    ball.dead();
                    clone1.dead();
                    clone2.dead();
                    ballCount = 3;
                }
                else
                {
                    ball.dead();
                    ballCount = 1;
                }
            }
        }
    }
		
    public void enemyTime()
    {
        // Player has a powerup
        pUp = true;

        // Enemy speed cut in half
        Enemy.enemyMoveSpeed /= 2;
        
        // Enemy Space ship speed cut in half
        EnemySpaceshipScript.enemyMoveSpeed /= 2;

    }

    void Update()
    {
        // If the player presses 'esc' pause/unpause the game
		if (Input.GetKeyDown(KeyCode.Escape) == true && (this.ball.hasStarted == false && large.hasStarted == false))
        {
            // If the Game is paused
            if (pause == true)
            {
                // Set pause to false
                pause = false;

                // Retain the enemy move speed
                Enemy.enemyMoveSpeed = 2.5f;
                EnemySpaceshipScript.enemyMoveSpeed = 4f;

				if (powerType == 4)
                {
					enemyTime ();
				}

                // Unactivate the pause menu
                pauseMenu.SetActive(false);
            }
            else
            {
                // Pause to true
                pause = true;

                // Display the pause menu
                pauseMenu.SetActive(true);

                // Stop enemy movement
                Enemy.enemyMoveSpeed = 0;
                EnemySpaceshipScript.enemyMoveSpeed = 0;
                
            }
        }

        // If the game is not paused
        if (pause == false)
        {
			if (Input.GetKeyDown (KeyCode.Escape) && ((this.ball.hasStarted == true && clone1.hasStarted == true && clone2.hasStarted == true) || large.hasStarted == true || this.ball.hasStarted == true))
            {
				Killed ();
			}
            // For each enemy
            int count = 0;
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
                if (UnityEngine.Random.Range(0, enemyLaseractivity) == 1 && go != null)
                {
                    Instantiate(this.EnemyLaser, go.transform.position, Quaternion.identity);
                }

                // For each enemy alive, increment count
                if (go != null && go.activeInHierarchy)
                {
                    count++;
                }
            }

            // If no more enemies are alive, then spawn a new level
            if (count == 0)
            {
                this.NewLevel();
            }

            // Set the laser activity
            enemyLaseractivity = (int)((count % 50) * 20 / laserchance);
        }
    }
}
