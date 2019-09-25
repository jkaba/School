using UnityEngine;

// enemyLaserScript class this script handles the enemy laser
public class enemylaserScript : MonoBehaviour {

    // Variables
    public float speed = 2;
    public Light sourceLight;
    private Transform mTransform;
    //private Light lightObject;

    void Start()
    {
        // Create the laser based on the laser light
        mTransform = transform;
        Instantiate(sourceLight, mTransform.position, Quaternion.identity);
    }

    void Update()
    {
        // Movement for the laser
        mTransform.Translate(Vector3.down * speed * Time.deltaTime);

        // If off screen then destroy the laser
        if (mTransform.position.y < -10f)
        {
            Destroy(gameObject);
        }
    }

    void OnTriggerEnter(Collider collider)
    {
        // If the laser hits the player
        if (collider.gameObject.tag.Equals("Player"))
        {
            // Run the method for when player is hit
            collider.GetComponent<PlayerMovementScript>().Dead();

            // destroy the enemy laser
            Destroy(gameObject);
        }

        // If the laser hits a block
        else if (collider.tag.Equals("Block"))
        {
            // Destroy the laser
            Destroy(gameObject);

            // Run the method for when a block is hit
            collider.GetComponent<BlockScript>().Collision();
        }
    }
}
