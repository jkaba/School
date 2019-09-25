using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace StackAttack
{
    // Powerup class used to determine which powerup spawns
    public class PowerUp : MonoBehaviour
    {

        // Variables
        private Transform mTransform;
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

            // 81 < x < 100 set powerup to speed boost
            if (randColor <= 100 && randColor >= 81)
            {
                color = 4;
            }

            // 61 < x < 80 set powerup to increase jumps
            else if (randColor <= 80 && randColor >= 61)
            {
                color = 3;
            }

            // 41 < x < 60 set powerup to increase damage
            else if (randColor <= 60 && randColor >= 41)
            {
                color = 2;
            }

            // 21 < x < 40 set powerup to health recovery
            else if (randColor <= 40 && randColor >= 21)
            {
                color = 1;
            }

            // otherwise increase jump height
            else
            {
                color = 0;
            }

            // Set transform, and create lightsource
            mTransform = transform;
            //Instantiate(lightsource, mTransform.position, Quaternion.identity);
        }

        void Update()
        {
            // Set the material
            renderer.sharedMaterial = materials[color];

            // Calculate movement
           // mTransform.Translate(Vector3.down * 1 * Time.deltaTime);

            // If offscreen, then destroy powerup
            //if (mTransform.position.y < -10f)
            //{
             //   Destroy(gameObject);
            //}
        }

        // Projectile Hitting Player / Ground
        private void OnTriggerEnter2D(Collider2D collision)
        {
            Debug.Log("Arrow Hit!");

            

            Character c;
            if ((c = collision.GetComponent<Character>()) != null)
            {
                c.powerUp(color);
               
                Destroy(gameObject);
                
            }

        }

    }
}