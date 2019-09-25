using UnityEngine;
using System;
using System.IO;

// LaserScript class this class controls/handles the laser shot by the player
public class LaserScript : MonoBehaviour
{
    // Variables
    public float speed = 5;
    public Light source;
    public GameScript gamescript;
    private Light lightObject;
    private Transform mTransform;

    private void Start()
    {
        // Set transform
        mTransform = transform;

        // Create an instance of the light source
        lightObject = Instantiate(source, mTransform.position, Quaternion.identity) as Light;

        // Set the gamescript
        gamescript = FindObjectOfType<GameScript>();
    }

    private void Update()
    {
        // Move the laser
        mTransform.Translate(Vector3.up * speed * Time.deltaTime);

        // If the laser is off screen then destroy it
        if (mTransform.position.y > 30f)
        {
            Destroy(gameObject);
        }
    }

    void OnTriggerEnter(Collider collider)
    {
        // If the laser hits an enemy space ship
        if (collider.tag.Equals("EnemySpaceship"))
        {
            // Destroy the light source and the laser
            Destroy(lightObject);
            Destroy(gameObject);

            // Run the kill method for enemy space ship
            collider.GetComponent<EnemySpaceshipScript>().Kill();

            // Add to the score based on the enemy tag
            gamescript.AddToScore(collider.tag);
        }

        // If the laser hits an enemy 
        else if (collider.tag.Contains("Enemy"))
        {
            // create an enemy object based on what was hit
            Enemy enemy = (Enemy)collider.gameObject.GetComponent("Enemy");

            // Run the Dead method for the enemy
            enemy.Dead();

            // Add to the score based on the enemy tag
            gamescript.AddToScore(collider.tag);

            // Destroy the light and the laser
            Destroy(lightObject);
            Destroy(gameObject);
        }

        // If the collision was with a block
        else if (collider.tag.Equals("Block"))
        {
            // Destroy the light and the laser
            Destroy(lightObject);
            Destroy(gameObject);

            // Run the collision method for the block
            collider.GetComponent<BlockScript>().Collision();
        }
    }


    // Set speed method which sets the lasers speed  
    public void setLaserSpeed(int newSpeed)
    {
        speed = newSpeed;
    }
}
