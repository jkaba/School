using UnityEngine;
using System;
using System.IO;

// Enemy class used for handling enemies and there properties
public class Enemy : MonoBehaviour
{
    // Variables

    // Movement variables
    public static float enemyMoveDir = 1;
    public static float enemyMoveSpeed = 2;
    public float changeInterval = 0.33F;
    private Transform mTransform;
    private Vector3 calc;

    // Material variables
    public Material[] materials;
    public int enemyType;

    // Death variables
    private float killtime = -1;
    private bool killed = false;
   
    // Parameter variables
    public int health;
    private int playerType;
    private int damage = 1;

    // Set Enemy Type method used to set the enemy based on an int
    public void SetEnemyType(int type)
    {
        // Switch case to assign the type of enemy
        switch (type)
        {
            // Back row / first row
            case 4:
                enemyType = 0;
                gameObject.tag = "EnemyOne";
                health = 5;
                break;
            // Second Row
            case 3:
                enemyType = 2;
                gameObject.tag = "EnemyTwo";
                health = 3;
                break;

            // Third row
            case 2:
                enemyType = 2;
                gameObject.tag = "EnemyTwo";
                health = 3;
                break;

            // Fourth row
            case 1:
                enemyType = 4;
                gameObject.tag = "EnemyThree";
                health = 1;
                break;

            // Fifth row / front row
            case 0:
                enemyType = 4;
                gameObject.tag = "EnemyThree";
                health = 1;
                break;
        }
    }

    void Start()
    {
        // Load called to determine how much damage is taken
        Load();
        mTransform = transform;
    }

    void Update()
    {
        // Calculate movement
        calc = Vector3.back * enemyMoveSpeed * enemyMoveDir * Time.deltaTime;
        mTransform.Translate(calc);

        // Set material
        this.SetMaterial();
    }

    // Used to set material during movement
    void SetMaterial()
    {
        // Calculate index used for changing the material while moving
        int index = (int)(Time.time / changeInterval);
        index = index % 2;

        // If the enemy is killed, then destroy it
        if (killed)
        {
            if (Time.time > this.killtime)
            {
                Destroy(this.gameObject);
            }
        }
        // Else set the materials
        else
        {
            GetComponent<Renderer>().sharedMaterial = materials[index + enemyType];
        }
    }

    // Used when collision is detected
    public void Dead()
    {
        // Reduce health by damage taken
        health -= damage;

        // If health is less than or equal to 0 the enemy is dead
        if (health <= 0)
        {
            // Set trigger to false
            GetComponent<Collider>().isTrigger = false;

            // Set killed to true and set kill time
            killed = true;
            killtime = Time.time + 0.25f;

            // Material is set to the exploded material
            GetComponent<Renderer>().sharedMaterial = materials[6];
        }
    }

    void Load()
    {
        // Load up the ship file to determine damage value
        string path = "Assets/Resources/ship.txt";
        StreamReader read = new StreamReader(path);
        playerType = Convert.ToInt32(read.ReadLine());
        read.Close();

        // Based on which ship, the damage changes accordingly
        switch (playerType)
        {
            case 4:
                damage = 5;
                break;
            case 3:
                damage = 1;
                break;
            case 2:
                damage = 5;
                break;
            case 1:
                damage = 3;
                break;
            case 0:
                damage = 1;
                break;
        }
    }
}
