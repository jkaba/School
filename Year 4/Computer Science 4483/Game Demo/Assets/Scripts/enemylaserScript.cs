using UnityEngine;

// Re-used and modified from a previous project

// enemyLaserScript class this script handles the enemy laser
public class enemylaserScript : MonoBehaviour {

    // Variables
    public float speed = 2;
    public Light sourceLight;
    private Transform mTransform;
	GameObject clone;

    //private Light lightObject;

    void Start()
    {
        // Create the laser based on the laser light
        mTransform = transform;
		sourceLight = Instantiate(sourceLight, mTransform.position, Quaternion.identity);
		clone = this.gameObject;
    }

    void Update()
    {
        // Movement for the laser
        mTransform.Translate(Vector3.down * speed * Time.deltaTime);

        // If off screen then destroy the laser
        if (mTransform.position.y < -12f)
        {
            Destroy(gameObject);
        }
    }

	void OnCollisionEnter2D (Collision2D collision) {
		if (collision.gameObject.tag.Equals ("Paddle")) {
			print (collision.gameObject.tag);

			// Run the method for when player is hit
			Paddle p = (Paddle)collision.gameObject.GetComponent("Paddle");

			// Run the Dead method for the enemy
			p.stun();

			// destroy the enemy laser
			Destroy (sourceLight);
			Destroy (clone);
		}

		// If the laser hits an enemy 
		else if (collision.gameObject.tag.Equals ("Ball")) {			
			Destroy(sourceLight);
			Destroy (clone);
		}
	}
		
}
