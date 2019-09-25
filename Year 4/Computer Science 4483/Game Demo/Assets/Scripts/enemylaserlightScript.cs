using UnityEngine;

// Re-used from a previous project

// EnemyLaserLightScript this script is used to move the laser light
public class enemylaserlightScript : MonoBehaviour
{
    // Set speed of laser
    public float speed = 2;

    // Start moves the laser forward
    void Start()
    {
        transform.Translate(Vector3.forward * -2f);
    }

    void Update()
    {
        // Move the laser
        transform.Translate(Vector3.down * speed * Time.deltaTime);

        // If off screen then destroy
        if (transform.position.y < -10f)
        {
            Destroy(gameObject);
        }
    }
}
