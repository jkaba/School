using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace StackAttack {
    public class DamageTrap : MonoBehaviour {

        public bool instantDeath;
        public float damage;

        private void OnTriggerEnter2D(Collider2D collision)
        {
            Character c = null;
            if ((c = collision.GetComponent<Character>()) != null)
            {
                if (instantDeath)
                {
                    c.TakeDamage(c.GetCurrentHealth() + 1f);
                }
                else
                {
                    c.TakeDamage(damage);
                }
            }
        }
    }
}
