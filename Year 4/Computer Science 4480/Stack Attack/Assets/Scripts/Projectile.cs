using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace StackAttack
{
    public class Projectile : MonoBehaviour
    {

        public enum Weapon
        {
            melee,
            ranged,
            bomb,
            bullets,
            rocks
        };

        public float m_Speed;
        public float m_Damage;
        public float m_Knockback;
        public float m_StunTime;

        public Character whoShotMe;

        Rigidbody2D m_Rigidbody;

        // Use this for initialization
        void Awake()
        {
            m_Rigidbody = GetComponent<Rigidbody2D>();
            // Projectile lasts 5 seconds
            Destroy(gameObject, 3f);
        }

        public static Weapon GetWeapon(int index)
        {
            switch (index)
            {
                case 0:
                    return Weapon.melee;
                case 1:
                    return Weapon.ranged;
                case 2:
                    return Weapon.bomb;
                case 10:
                    return Weapon.bullets;
                case 20:
                    return Weapon.rocks;
                default:
                    return Weapon.ranged;
            }
        }

        // Projectile Hitting Player / Ground
        private void OnTriggerEnter2D(Collider2D collision)
        {

            Character c;
            if ((c = collision.GetComponent<Character>()) != null)
            {
                if (c != whoShotMe)
                {
                    c.TakeDamage(m_Damage);
                    if (m_Rigidbody != null)
                    {
                        c.KnockBack(m_Rigidbody.mass, m_Rigidbody.velocity, m_StunTime);
                    }
                    Destroy(gameObject);
                }
            }
        }
    }
}

