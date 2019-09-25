using UnityEngine;

// EnemySpaceshipScript used for controlling the enemy spaceship
public class EnemySpaceshipScript : MonoBehaviour
{
    // Variables
    public static float enemyMoveSpeed = 4;
    public GameObject enemyLaser;
    public GameObject enemySpaceshipLight;
    public GameObject powerUp;
    public Material[] materials;
    private bool dead = false;
    private float explodeTime = 0;
    private Transform mTransform;
    private Renderer renderer;

    void Start()
    {
        // Set the renderer with the material
        renderer = this.GetComponent<Renderer>();
        this.mTransform = transform;
        this.renderer.sharedMaterial = materials[0];

        // Create an instance of the spaceship light
        this.enemySpaceshipLight = (GameObject)Instantiate(this.enemySpaceshipLight, new Vector3(-20, 8, -1.3f), Quaternion.AngleAxis(90, Vector3.up));
    }

    void Update()
    {
        // If the ship is dead
        if (this.dead)
        {
            if (Time.time > this.explodeTime)
            {
                
                // Destroy the light
                Destroy(this.enemySpaceshipLight);

                // Create and drop a powerup
                Instantiate(this.powerUp, this.mTransform.position, Quaternion.identity);

                // Destroy the ship
                Destroy(this.gameObject);
            }

            // Increase the intensity of the light
            this.enemySpaceshipLight.GetComponent<Light>().intensity += 1;
            return;
        }

        // Move the ship
        mTransform.Translate(Vector3.forward * enemyMoveSpeed * Time.deltaTime);

        // If it moves offscreen then destroy it
        if (this.mTransform.position.x > 20)
        {
            Destroy(this.gameObject);
        }

        // 1/100 chance that the ship will shoot
        if (Random.Range(0, 100) == 1)
        {
            // Create an enemy laser to be shot
            Instantiate(this.enemyLaser, this.mTransform.position, Quaternion.identity);
        }
    }

    public void Kill()
    {
        // Change material to the death material
        this.renderer.sharedMaterial = materials[1];

        // Set dead to true and calculate explodeTime
        this.dead = true;
        explodeTime = Time.time + 0.1f;
    }
}
