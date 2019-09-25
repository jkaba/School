using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace StackAttack
{

    public class Fireball : MonoBehaviour
    {

        // Variables

        // Movement variables
        public static float enemyMoveDir = 1;
        public static float enemyMoveSpeed = 2;
        public float changeInterval = 1F;
        private Transform mTransform;
        private Vector3 calc;

        // Material variables
        public Material[] materials;
        public int enemyType;

        // Death variables
        private float killtime = -1;
        private bool killed = false;

        // Parameter variables
        private int playerType;

        // Set Enemy Type method used to set the enemy based on an int
        public void SetEnemyType(int type)
        {
            // Switch case to assign the type of enemy
            enemyType = 0;
            gameObject.tag = "EnemyOne";
        }

        void Start()
        {
            mTransform = transform;
            this.SetMaterial();
        }

        void Update()
        {
            if (enemyType == 0)
            {
                calc = new Vector3(0, 0.1f, 0);//, Quaternion.AngleAxis(89, Vector3.up);//Vector3.back * enemyMoveSpeed * enemyMoveDir * Time.deltaTime;
                mTransform.Translate(calc);
                if (this.transform.position.y > 5)
                {
                    //this.transform.position = new Vector3(25f, 5f, 0f);
                    // Set material
                    this.SetMaterial();
                }
            }
            else
            {
                // Calculate movement
                calc = new Vector3(0, -0.1f, 0);//, Quaternion.AngleAxis(89, Vector3.up);//Vector3.back * enemyMoveSpeed * enemyMoveDir * Time.deltaTime;
                mTransform.Translate(calc);

                if (this.transform.position.y < -5)
                {
                    //this.transform.position = new Vector3(25f, 5f, 0f);
                    // Set material
                    this.SetMaterial();
                }

            }
        }

        // Used to set material during movement
        void SetMaterial()
        {
            int index = 0;
            if(enemyType == 0)
            {
                enemyType = 1;
                index = 1;
            }

            else
            {
                enemyType = 0;
                index = 0;
            }

            // Else set the materials

            GetComponent<Renderer>().sharedMaterial = materials[index];
        }

        private void OnTriggerEnter2D(Collider2D collision)
        {

            Character c;
            if ((collision.gameObject.tag == "Player" || collision.gameObject.tag == "CPU"))
            {
                c = collision.gameObject.GetComponent<Character>();
                c.TakeDamage(5f);
            }
        }
    }
}
