using UnityEngine;
using UnityEngine.UI;

public class GameScript : MonoBehaviour
{
    // Global variables, lot's of global variables

    // GameObject Variables
    public GameObject Enemyprefab;
    public GameObject Player;
    public GameObject EnemyLaser;
    public GameObject EnemySpaceship;
    public GameObject Block;
    public GameObject Gameover;
    GameObject[,] enemys;
    public GameObject pauseMenu;

    // Script Variables
    public PlayerMovementScript p2;
    private GameoverScript gameoverScript;

    // Text variables
    public Text scoreboard;
    public Text liveCount;
    public Text healthbar;

    // float, int, and bool variables
    float xStartOffset = -10;
    float yStartOffset = 2f;
    public int lives = 3;
    public int Score = 0;
    public int ScoreMultiplyer = 1;
    //float enemykillCount = 0;
    float timesinceLastTurn = 0;
    float powerTime = 0;
    float laserchance = 0.7f;
    int enemyLaseractivity = 0;
    int extraLife = 0;
    public bool pause = false;
    int spaceship = 0;
    private bool pUp = false;

    void Start()
    {      
        // Find the gameover script
        gameoverScript = GameObject.Find("GameOverModel").GetComponent<GameoverScript>();

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
                Instantiate(this.EnemySpaceship, new Vector3(-20, 8, 0), Quaternion.AngleAxis(90, Vector3.up));
                spaceship++;
            }
        }
        else
        {
            // For every 1000 points spawn a spaceship
            if(Score >= ( 1000 * (spaceship + 1)))
            {
                Instantiate(this.EnemySpaceship, new Vector3(-20, 8, 0), Quaternion.AngleAxis(90, Vector3.up));
                spaceship++;
            }
        }

        // Switch case to give points based on the enemy killed
        switch (enemyTag)
        {
            case "EnemyThree":
                Score += 10;
                break;
            case "EnemyTwo":
                Score += 20;
                break;
            case "EnemyOne":
                Score += 30;
                break;
            case "EnemySpaceship":
                Score += 50;
                break;
            default:
                Score += 10;
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
            // For every 1000 points the player gets an extra life
            if (Score >= (1000 * (extraLife + 1)))
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
        laserchance += 0.1f;
        Enemy.enemyMoveSpeed += 0.5f;

        // Spawn a wave of enemies
        enemys = new GameObject[10, 5];
        for (int y = 0; y < 5; y++)
        {
            for (int x = 0; x < 10; x++)
            {
                enemys[x, y] = (GameObject)Instantiate(this.Enemyprefab, new Vector3(x * 1.3f + xStartOffset, y * 1.1f + yStartOffset, 0), Quaternion.AngleAxis(90, Vector3.up));
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

        // Create an instance of player
        Instantiate(this.Player, new Vector3(0, -9, 0), Quaternion.AngleAxis(180, Vector3.up));
        healthbar.text = "Health: " + p2.health;

        // Create the 4 instances of blocks
        this.GenerateBlocks(-10f, -7.5f);
        this.GenerateBlocks(8f, -7.5f);
        this.GenerateBlocks(-5f, -7.5f);
        this.GenerateBlocks(3f, -7.5f);
    }

    void GenerateBlocks(float blockOffsetX, float blockOffsetY)
    {
        // Set the size
        float size = 0.2f;
    
        // Create the blocks 1 piece at a time
        Instantiate(this.Block, new Vector3(0 * size + blockOffsetX, 0 * size + blockOffsetY, 0), Quaternion.identity);
        Instantiate(this.Block, new Vector3(0 * size + blockOffsetX, 1 * size + blockOffsetY, 0), Quaternion.identity);
        Instantiate(this.Block, new Vector3(1 * size + blockOffsetX, 0 * size + blockOffsetY, 0), Quaternion.identity);
        Instantiate(this.Block, new Vector3(1 * size + blockOffsetX, 2 * size + blockOffsetY, 0), Quaternion.identity);
        Instantiate(this.Block, new Vector3(2 * size + blockOffsetX, 1 * size + blockOffsetY, 0), Quaternion.identity);
        Instantiate(this.Block, new Vector3(2 * size + blockOffsetX, 3 * size + blockOffsetY, 0), Quaternion.identity);
        Instantiate(this.Block, new Vector3(3 * size + blockOffsetX, 2 * size + blockOffsetY, 0), Quaternion.identity);
        Instantiate(this.Block, new Vector3(3 * size + blockOffsetX, 4 * size + blockOffsetY, 0), Quaternion.identity);
        Instantiate(this.Block, new Vector3(4 * size + blockOffsetX, 2 * size + blockOffsetY, 0), Quaternion.identity);
        Instantiate(this.Block, new Vector3(4 * size + blockOffsetX, 4 * size + blockOffsetY, 0), Quaternion.identity);
        Instantiate(this.Block, new Vector3(5 * size + blockOffsetX, 2 * size + blockOffsetY, 0), Quaternion.identity);
        Instantiate(this.Block, new Vector3(5 * size + blockOffsetX, 4 * size + blockOffsetY, 0), Quaternion.identity);
        Instantiate(this.Block, new Vector3(6 * size + blockOffsetX, 2 * size + blockOffsetY, 0), Quaternion.identity);
        Instantiate(this.Block, new Vector3(6 * size + blockOffsetX, 4 * size + blockOffsetY, 0), Quaternion.identity);
        Instantiate(this.Block, new Vector3(7 * size + blockOffsetX, 2 * size + blockOffsetY, 0), Quaternion.identity);
        Instantiate(this.Block, new Vector3(7 * size + blockOffsetX, 4 * size + blockOffsetY, 0), Quaternion.identity);
        Instantiate(this.Block, new Vector3(8 * size + blockOffsetX, 1 * size + blockOffsetY, 0), Quaternion.identity);
        Instantiate(this.Block, new Vector3(8 * size + blockOffsetX, 3 * size + blockOffsetY, 0), Quaternion.identity);
        Instantiate(this.Block, new Vector3(9 * size + blockOffsetX, 0 * size + blockOffsetY, 0), Quaternion.identity);
        Instantiate(this.Block, new Vector3(9 * size + blockOffsetX, 2 * size + blockOffsetY, 0), Quaternion.identity);
        Instantiate(this.Block, new Vector3(10 * size + blockOffsetX, 0 * size + blockOffsetY, 0), Quaternion.identity);
        Instantiate(this.Block, new Vector3(10 * size + blockOffsetX, 1 * size + blockOffsetY, 0), Quaternion.identity);
    }


    public void Killed()
    {
        // If the game is paused, then player should not be killed
        if (pause == true)
        {
            Instantiate(this.Player, new Vector3(0, -9, 0), Quaternion.AngleAxis(180, Vector3.up));
        }

        else
        {
            // If the player is out of lives
            if (lives == 0)
            {
                // Display the leaderboard
                gameoverScript.Display2(true, Score);
            }
            else
            {
                // Take a life away
                lives--;

                // Update life text
                liveCount.text = "Lives Left: " + lives;

                // Create a new instance of the player
                Instantiate(this.Player, new Vector3(0, -9, 0), Quaternion.AngleAxis(180, Vector3.up));
            }
        }
    }

    public void healthText(int hea)
    {
        // Update healthbar text
        healthbar.text = "Health: " + hea;
    }

    public void enemyTime()
    {
        // Player has a powerup
        pUp = true;

        // Enemy speed cut in half
        Enemy.enemyMoveSpeed /= 2;
        
        // Enemy Space ship speed cut in half
        EnemySpaceshipScript.enemyMoveSpeed /= 2;

        // Calculate time that powerup is active
        this.powerTime = Time.time + 5;
    }

    void Update()
    {
        // If the player presses 'esc' pause/unpause the game
        if (Input.GetKeyDown(KeyCode.Escape) == true)
        {
            // If the Game is paused
            if (pause == true)
            {
                // Set pause to false
                pause = false;

                // Retain the enemy move speed
                Enemy.enemyMoveSpeed = 2.5f;
                EnemySpaceshipScript.enemyMoveSpeed = 4f;

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
            // For each enemy
            int count = 0;
            foreach (GameObject go in enemys)
            {
                // If the powerup is active, and time is up revert enemy speed
                if (pUp == true && Time.time > this.powerTime)
                {
                    pUp = false;
                    Enemy.enemyMoveSpeed *= 2;
                    Debug.Log(Enemy.enemyMoveSpeed);
                    EnemySpaceshipScript.enemyMoveSpeed *= 2;
                }

                // Change direction
                if (go != null && (go.transform.position.x > 11 || go.transform.position.x < -11) && Time.time > this.timesinceLastTurn)
                {
                    this.timesinceLastTurn = Time.time + 1;
                    {
                        Enemy.enemyMoveDir = Enemy.enemyMoveDir * -1;
                    }
                }

                // Shoot lasers
                if (Random.Range(0, enemyLaseractivity) == 1 && go != null)
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
