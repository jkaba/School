using System.Collections;
using System.Collections.Generic;
using UnityEngine;

// Powerup class used to determine which powerup spawns
public class PowerUp : MonoBehaviour {

    // Variables
    public float laserSpeed = 2;
    public Light lightsource;
    private Transform mTransform;
    private Light lightsourceObject;
    public Material[] materials;
    private Renderer renderer;
    private int color = 0;
    private float randColor;

    void Start()
    {
        // Set the renderer
        renderer = GetComponent<Renderer>();

        // Random number generator between 0 and 100
        randColor = Random.Range(0, 100);

        // 81 < x < 100 set powerup to player speed
        if (randColor <= 100 && randColor >= 81)
        {
            color = 4;
        }

        // 61 < x < 80 set powerup to shot power
        else if (randColor <= 80 && randColor >= 61)
        {
            color = 3;
        }

        // 41 < x < 60 set powerup to health+1
        else if (randColor <= 60 && randColor >= 41)
        {
            color = 2;
        }

        // 21 < x < 40 set powerup to shot speed
        else if (randColor <= 40 && randColor >= 21)
        {
            color = 1;
        }

        // otherwise it is enemy slowdown
        else
        {
            color = 0;
        }

        // Set transform, and create lightsource
        mTransform = transform;
        Instantiate(lightsource, mTransform.position, Quaternion.identity);
    }

    void Update()
    {
        // Set the material
        renderer.sharedMaterial = materials[color];

        // Calculate movement
        mTransform.Translate(Vector3.down * laserSpeed * Time.deltaTime);

        // If offscreen, then destroy powerup
        if (mTransform.position.y < -10f)
        {
            Destroy(gameObject);
        }
    }

    void OnTriggerEnter(Collider collider)
    {
        // If the player hits the powerup
        if (collider.gameObject.tag.Equals("Player"))
        {
            // Activate powerup in the player
            collider.GetComponent<PlayerMovementScript>().Power(color);

            // Destroy the powerup
            Destroy(gameObject);
        }
    }
}
