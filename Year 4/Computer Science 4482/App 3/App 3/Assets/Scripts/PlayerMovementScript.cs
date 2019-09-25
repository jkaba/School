using UnityEngine;
using System.IO;
using System;

public class PlayerMovementScript : MonoBehaviour
{
    // Lot's of variables

    // Ship Parameters
    public float playerSpeed = 5;
    private int character = 0;
    private int weapon = 1;
    private int shotSpeed = 1;
    private int shotPower = 1;
    public int health = 1;

    // Powerup variables
    public bool powerUp = false;
    public bool enemyP = false;
    private float copyMS = 0;
    private int copySS = 0;
    private int copySP = 0;

    // Laser variables
    public GameObject laserPrefab;
    public LaserScript laserScript;

    // Life variables
    private bool alive = true;
    private bool invincible = true;
    private float invincibleTimer;
    public float invincibleBlinkInterval = 0.33F;
    private float explodeTime = 0;
    private float revivalTime = 0;

    // Material variables
    public Material[] materials;
    private Renderer renderer;

    private GameScript gameScript;

    private void Start()
    {
        // Load up which ship to use
        Load();

        // Ship is alive
        alive = true;

        // Starting invincible timer as player is invincible for 2 seconds to start
        invincibleTimer = Time.time + 2.0f;

        // Find the GameScript
        gameScript = FindObjectOfType<GameScript>();

        // Set up the health text
        gameScript.healthText(health);

        // Set up renderer
        renderer = GetComponent<Renderer>();

        // Set the laser speed
        laserScript.setLaserSpeed(shotSpeed);
    }

    private void Update()
    {
        // If the player is alive
        if (alive)
        {
            // Movement calculations
            Vector3 v = Vector3.left * Input.GetAxisRaw("Horizontal") * Time.deltaTime * playerSpeed;

            // Keep the player within bounds
            if (v.x > 0)
            {
                if (transform.position.x > -12)
                {
                    transform.Translate(v);
                }
            }
            else if (v.x < 0)
            {
                if (transform.position.x < 12)
                {
                    transform.Translate(v);
                }
            }
            // If the player presses space they shoot
            if (Input.GetKeyDown("space"))
            {
                Vector3 perf;

                // Based on which weapon determines how many lasers are shot
                switch (weapon)
                {
                    // If weapon is single then 1 center laser
                    case 1:
                        Instantiate(laserPrefab, transform.position, Quaternion.identity);
                        break;

                    // If weapon is double then 2 lasers off to the left and right
                    case 2:
                        perf = new Vector3(transform.position.x + 1, transform.position.y, transform.position.z);
                        Instantiate(laserPrefab, perf, Quaternion.identity);
                        perf = new Vector3(transform.position.x - 1, transform.position.y, transform.position.z);
                        Instantiate(laserPrefab, perf, Quaternion.identity);
                        break;

                    // If weapon is triple then combine case 1 and 2
                    case 3:
                        Instantiate(laserPrefab, transform.position, Quaternion.identity);
                        perf = new Vector3(transform.position.x + 1, transform.position.y, transform.position.z);
                        Instantiate(laserPrefab, perf, Quaternion.identity);
                        perf = new Vector3(transform.position.x - 1, transform.position.y, transform.position.z);
                        Instantiate(laserPrefab, perf, Quaternion.identity);
                        break;

                    // Default case is single laser
                    default:
                        Instantiate(laserPrefab, transform.position, Quaternion.identity);
                        break;
                }
            }

            // If the player is invincible
            if (invincible)
            {
                // If it's been longer than the invincible timer 
                if (Time.time > invincibleTimer)
                {
                    // Set the collider trigger to true
                    gameObject.GetComponent<Collider>().isTrigger = true;

                    // Player no longer invincible, set the character material
                    invincible = false;
                    renderer.sharedMaterial = materials[character];
                }
                
                // Player is still invincible
                else
                {
                    // Calculate index for blinking
                    int index = (int)(Time.time / invincibleBlinkInterval);
                    index = index % 2;

                    // if index is 0 then set material
                    if (index == 0)
                    {
                        renderer.sharedMaterial = materials[character];
                    }

                    // Else material is blank
                    else
                    {
                        renderer.sharedMaterial = materials[6];
                    }
                }
            }
        }
        // Player is dead
        else
        {
            // If time is passed the explode time then set material to revival
            if (Time.time > explodeTime)
            {
                renderer.sharedMaterial = materials[6];
            }

            // If time is passed the revival time 
            if (Time.time > revivalTime)
            {
                // Run method for killed in gamescript
                gameScript.Killed();

                // destroy the character
                Destroy(gameObject);
            }
        }
    }

    public void Dead()
    {
        // If the game is not paused
        if (gameScript.pause == false)
        {
            // Take 1 damage
            health--;

            // Update health text
            gameScript.healthText(health);

            // If health is <= 0
            if (health <= 0)
            {
                // Player is dead
                alive = false;

                // Player no longer has a powerup
                powerUp = false;

                // Trigger is false
                gameObject.GetComponent<Collider>().isTrigger = false;

                // Set material to the dead material
                renderer.sharedMaterial = materials[5];

                // Set explode and revival time
                explodeTime = Time.time + 0.5f;
                revivalTime = Time.time + 1.5f;
            }
        }
    }

    public void Power(int tpe)
    {
        // player has a powerup
        powerUp = true;

        // Based on the power up do the following
        switch (tpe)
        {
            // Yellow powerup
            case 4:
                // Increase speed 1 level, reset other stats
                playerSpeed += 2;
                shotSpeed = copySS;
                shotPower = copySP;
                break;
            
            // White powerup
            case 3:
                // Increase shot power by 1 level, reset other stats
                shotPower++;
                shotSpeed = copySS;
                playerSpeed = copyMS;
                break;

            // Red powerup
            case 2:
                // Increase health by 1 and update health text
                health++;
                gameScript.healthText(health);
                break;

            // Green powerup
            case 1:
                // Increase shot speed by 1 level, reset other stats
                shotSpeed += 5;
                shotPower = copySP;
                playerSpeed = copyMS;
                break;

            // Blue powerup
            case 0:
                // Reset stats
                shotPower = copySP;
                shotSpeed = copySS;
                playerSpeed = copyMS;

                // Slow enemies for 5 seconds
                gameScript.enemyTime();
                break;
        }
    }

    void Load()
    {
        // File location
        string path = "Assets/Resources/ship.txt";
        StreamReader read = new StreamReader(path);

        // Read the int from the file
        character = Convert.ToInt32(read.ReadLine());

        // Close the file
        read.Close();

        // If the character chosen is index 0, set stats
        if (character == 0)
        {
            weapon = 1;
            shotSpeed = 5;
            shotPower = 1;
            health = 1;
            playerSpeed = 2;
        }

        // If character chosen is index 1, set stats
        else if (character == 1)
        {
            weapon = 2;
            shotSpeed = 10;
            shotPower = 3;
            health = 2;
            playerSpeed = 4;
        }

        // If character chosen is index 2, set stats
        else if (character == 2)
        {
            weapon = 1;
            shotSpeed = 5;
            shotPower = 5;
            health = 3;
            playerSpeed = 2;
        }

        // If character chosen is index 3, set stats
        else if (character == 3)
        {
            weapon = 3;
            shotSpeed = 10;
            shotPower = 1;
            health = 5;
            playerSpeed = 6;
        }

        // If character chosen is index 4, set stats
        else if (character == 4)
        {
            weapon = 2;
            shotSpeed = 25;
            shotPower = 5;
            health = 5;
            playerSpeed = 10;
        }

        // Create copies of stats for powerup usage
        copyMS = playerSpeed;
        copySS = shotSpeed;
        copySP = shotPower;
    }
}
