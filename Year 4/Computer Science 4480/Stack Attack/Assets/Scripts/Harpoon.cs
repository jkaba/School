using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace StackAttack
{
    public class Harpoon : MonoBehaviour
    {

        LineRenderer lrenderer;
        public GameObject whoShotMe;
        public float speed;
        public float maxDistance;
        GameObject whoWasShot;
        Vector3[] positions;

        private void Awake()
        {
            lrenderer = GetComponent<LineRenderer>();
            positions = new Vector3[2];
        }

        private void Update()
        {
            if (whoShotMe != null)
            {
                positions[0] = transform.position;
                positions[1] = whoShotMe.transform.position;
                lrenderer.SetPositions(positions);

                if (Vector3.Distance(transform.position, whoShotMe.transform.position) > maxDistance)
                {
                    lrenderer.startWidth = 0f;
                    lrenderer.endWidth = 0f;

                    //whoShotMe.GetComponent<Character>().harpoonActive = false;

                    Destroy(gameObject);
                }
            }
        }

        private void OnTriggerEnter2D(Collider2D collision)
        {
            Character c = collision.transform.GetComponent<Character>();
            if (c != null && c.gameObject != whoShotMe.gameObject)
            {
                whoWasShot = c.gameObject;
                c.FreezeShootInput(1f);
                StartCoroutine(HarpoonedCo());
            }
            else
            {
                lrenderer.startWidth = 0f;
                lrenderer.endWidth = 0f;

                //whoShotMe.GetComponent<Character>().harpoonActive = false;

                Destroy(gameObject);
            }
        }

        private IEnumerator HarpoonedCo()
        {
            Debug.Log("harpooned!");

            Vector2 offset = new Vector2(0f, 1f);

            Rigidbody2D r1 = whoShotMe.GetComponent<Rigidbody2D>();
            Rigidbody2D r2 = whoWasShot.GetComponent<Rigidbody2D>();

            while (Vector3.Distance(r1.position, r2.position + offset) > 0.1)
            {
                r1.MovePosition(Vector2.MoveTowards(r1.position, r2.position + offset, Time.deltaTime * speed));
                yield return null;
            }

            r1.MovePosition(r2.position + offset);

            yield return null;

            Debug.Log("Stacking!");
            //whoShotMe.GetComponent<Character>().StackTogether(whoWasShot, whoShotMe.GetComponent<Character>().m_CharacterStack);

            lrenderer.startWidth = 0f;
            lrenderer.endWidth = 0f;
            Destroy(gameObject);
        }
    }
}