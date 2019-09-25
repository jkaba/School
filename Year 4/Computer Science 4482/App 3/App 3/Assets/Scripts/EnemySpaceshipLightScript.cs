using UnityEngine;

// EnemySpaceShipLightScript this class is used for moving the spaceship light
public class EnemySpaceshipLightScript : MonoBehaviour
{
    // Variables for movement
    public static float moveSpeed = 4;
    private Transform mTransform;

    void Start()
    {
        // Set transform
        mTransform = transform;
    }

    void Update()
    {
        // Move the light
        mTransform.Translate(Vector3.forward * moveSpeed * Time.deltaTime);

        // If the light is off the screen then destroy it
        if (mTransform.position.x > 20)
        {
            Destroy(gameObject);
        }
    }
}
