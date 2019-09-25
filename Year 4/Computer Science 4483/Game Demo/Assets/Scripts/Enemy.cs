using UnityEngine;
using System;
using System.IO;

// Re-used and modified from a previous project

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
                health = 3;
                break;
            // Second Row
            case 3:
                enemyType = 2;
                gameObject.tag = "EnemyTwo";
                health = 2;
                break;

            // Third row
            case 2:
                enemyType = 2;
                gameObject.tag = "EnemyTwo";
                health = 2;
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
	public void Dead(int damage)
    {
        // Reduce health by damage taken
        health -= damage;

        // Change sprites based on health remaining
		if (health == 2)
        {
			this.SetEnemyType (3);
		}
		if (health == 1)
        {
			this.SetEnemyType (1);
		}

        // If health is less than or equal to 0 the enemy is dead
        if (health <= 0)
        {
            // Set trigger to false
            GetComponent<Collider2D>().isTrigger = false;

            // Set killed to true and set kill time
            killed = true;
            killtime = Time.time + 0.25f;

            // Material is set to the exploded material
            GetComponent<Renderer>().sharedMaterial = materials[6];
        }
    }
}
