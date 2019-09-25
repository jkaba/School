using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace StackAttack
{
    public class Explosive : MonoBehaviour
    {
        public GameObject explosionPrefab;

        public float fuseTime;
        public float damage;
        public float radius;

        public bool exploding;

        private void Start()
        {

        }

        private void Update()
        {
            fuseTime -= Time.deltaTime;
            if (!exploding && fuseTime <= 0)
            {
                Explode();
            }
        }

        void Explode()
        {
            exploding = true;
            Instantiate(explosionPrefab, transform.position, transform.rotation);

            Collider2D[] results = Physics2D.OverlapCircleAll(transform.position, radius);

            foreach (Collider2D c2D in results)
            {
                Character c;
                if ((c = c2D.GetComponent<Character>()) != null)
                {
                    c.TakeDamage(damage);
                }
            }

            DestroyImmediate(gameObject);
        }
    }
}