using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Audio;

namespace StackAttack
{
    public class PunchDamage : MonoBehaviour
    {
        public float damage;
        Character puncher;
        //public AudioSource punchSource;

        // Use this for initialization
        void Start()
        {
            puncher = transform.parent.GetComponent<Character>();
            //punchSource = GetComponent<AudioSource>();
        }

        void OnTriggerEnter2D(Collider2D collision)
        {
            Character hit;
            if ((hit = collision.GetComponent<Character>()) != null && hit != puncher)
            {
                hit.TakeDamage(damage);
                //punchSource.Play();
            }
        }

    }
}

