using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace StackAttack
{

    public class Eel : MonoBehaviour
    {

        // Variables

        // Movement variables
        public static float enemyMoveDir = 1;
        public static float enemyMoveSpeed = 2;
        public float changeInterval = 1F;
        private Transform mTransform;
        private Vector3 calc;

        private AudioSource electricitySound;

        // Material variables
        public Material[] materials;
        public int enemyType;

        // Death variables
        private float killtime = -1;
        private bool killed = false;

        // Parameter variables
        private int playerType;

        bool elec = false;

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
            electricitySound = GetComponent<AudioSource>();
        }

        void Update()
        {
            // Calculate movement
            calc = new Vector3(0.1f, 0, 0);//, Quaternion.AngleAxis(89, Vector3.up);//Vector3.back * enemyMoveSpeed * enemyMoveDir * Time.deltaTime;
            mTransform.Translate(calc);

            if(this.transform.position.x < -30)
            {
                this.transform.position = new Vector3(30f, 4.5f, 0f) ;
            }

            // Set material
            this.SetMaterial();
        }

        // Used to set material during movement
        void SetMaterial()
        {
            // Calculate index used for changing the material while moving
            int index = (int)(Time.time / changeInterval);
            index = index % 2;

            // Else set the materials

            GetComponent<Renderer>().sharedMaterial = materials[index + enemyType];
            if (elec == true)
            {
                
                elec = false;
            }
            else
            {
                elec = true;
                
            }
        }

        private void OnTriggerEnter2D(Collider2D collision)
        {

            Character c;
            if ((collision.gameObject.tag == "Player" || collision.gameObject.tag == "CPU"))
            {
                c = collision.gameObject.GetComponent<Character>();
                if (elec == true)
                {
                    Debug.Log("EEL HITTER");
                    electricitySound.Play();
                    c.TakeDamage(2f);
                }
                
            }
        }
    }
}
