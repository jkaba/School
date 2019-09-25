using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace StackAttack
{
    [RequireComponent(typeof(Character))]
    public class AICharacterController : MonoBehaviour
    {
        public GameObject arrow = null;
        private Character m_Character;
        private List<GameObject> players;
        private List<GameObject> platforms;
        private List<GameObject> spikes;

        private float m_Speed;
        private bool m_Jump;

        private bool m_IsMoving;
        private Collider2D leftWall;
        private Collider2D rightWall;
        new private Collider2D collider;
        private float attackTimer = 0f;
        private float unstackTimer = 0f;
        private float attackDelay = 1f;
        private bool justStacked = false;

        // Use this for initialization
        void Start()
        {
            attackTimer = 0f;
            unstackTimer = 0f;
            attackDelay = 1f;
            justStacked = false;
            m_Character = GetComponent<Character>();
            GameManager gm = GameObject.Find("GameManager").GetComponent<GameManager>();
            players = new List<GameObject>(gm.players);
            platforms = new List<GameObject>(gm.platforms);
            spikes = new List<GameObject>(gm.spikes);
            leftWall = GameObject.Find("Left Wall").GetComponent<Collider2D>();
            rightWall = GameObject.Find("Right Wall").GetComponent<Collider2D>();
            collider = GetComponent<Collider2D>();
            for (int i = players.Count - 1; i >= 0; i--)
            {
                if (players[i] == this.gameObject)
                {
                    players.RemoveAt(i);
                }
            }
        }

        private void Shoot(GameObject enemy, GameObject projectile)
        {
            Vector3 aim = enemy.transform.position - transform.position;
            aim.z = 0f;
            aim.x += Random.Range(-1f, 1f) / 5;
            aim.y += Random.Range(-1f, 1f) / 5;
            aim = aim * 1f / Mathf.Abs(aim.magnitude);
            m_Character.Attack(aim.x, aim.y, aim.x, aim.y);
        }

        GameObject GetClosest(List<GameObject> gos)
        {
            GameObject tMin = null;
            float minDist = Mathf.Infinity;
            Vector3 currentPos = transform.position;
            foreach (GameObject t in gos)
            {
                float dist = Vector3.Distance(t.transform.position, currentPos);
                if (dist < minDist)
                {
                    tMin = t;
                    minDist = dist;
                }
            }
            return tMin;
        }

        private void Update()
        {
            if (m_Character.IsStacked() && !justStacked)
            {
                justStacked = true;
                unstackTimer += Time.deltaTime;
            }
            if (!m_Character.IsStacked() && unstackTimer == 0f)
            {
                m_Character.TryStacking(-1);
            }
            else if (attackTimer > attackDelay && Random.Range(0, 100) > 90 && unstackTimer == 0f)
            {
                m_Character.TryStacking(1);
                StartCoroutine(GoLeft(0.3f));
                justStacked = false;
                unstackTimer += Time.deltaTime;
            }

            if (unstackTimer > 3f)
            {
                unstackTimer = 0f;
            }
            else if (unstackTimer != 0)
            {
                unstackTimer += Time.deltaTime;
            }

            if (attackTimer > attackDelay)
            {
                attackTimer = 0f;
                attackDelay = Random.Range(0.1f, 1f);
            }
            else if (attackTimer != 0f)
            {
                attackTimer += Time.deltaTime;
            }
            GameObject closestEnemy = players[0];
            float closestDistance = 999;
            float distance;
            for (int i = players.Count - 1; i >= 0; i--)
            {
                if (players[i] == null || !players[i].activeInHierarchy || players[i].GetComponent<Character>().stationary)
                {
                    players.RemoveAt(i);
                    continue;
                }
                //find closest enemy that is not in our stack
                distance = Vector3.Distance(transform.position, players[i].transform.position);
                if (!m_Character.m_CharacterStack.Contains(players[i]) && distance < closestDistance)
                {
                    closestDistance = distance;
                    closestEnemy = players[i];
                }
            }
            JumpCheck(closestEnemy, closestDistance);//jump if enemy beside us
            if (!m_IsMoving)
            {
                float xDistance = Mathf.Abs(closestEnemy.transform.position.x - transform.position.x);
                if (attackTimer == 0f && arrow != null && !m_Character.shootDisable && ((m_Character.weapon == Projectile.Weapon.melee && xDistance < 1f) || (m_Character.weapon != Projectile.Weapon.melee && xDistance < 10f)))
                {
                    attackTimer = Time.deltaTime;
                    switch (m_Character.weapon)
                    {
                        case Projectile.Weapon.melee:
                            Shoot(closestEnemy, m_Character.ranged);
                            break;
                        case Projectile.Weapon.ranged:
                            Shoot(closestEnemy, m_Character.ranged);
                            break;
                        case Projectile.Weapon.bomb:
                            Shoot(closestEnemy, m_Character.bomb);
                            break;
                        case Projectile.Weapon.bullets:
                            Shoot(closestEnemy, m_Character.bullets);
                            break;
                        case Projectile.Weapon.rocks:
                            Shoot(closestEnemy, m_Character.rocks);
                            break;
                        default:
                            break;
                    }
                }
                Move(closestEnemy, closestDistance);
            }
        }

        private void FixedUpdate()
        {
            m_Character.Move(m_Speed, m_Jump);
            m_Jump = false;
        }

        private void JumpCheck(GameObject closestEnemy, float distance)
        {
            if (closestEnemy != null && closestEnemy.activeInHierarchy && closestEnemy.transform.position.y <= transform.position.y)
            {
                m_Jump = distance < 2.5f;
            }
        }

        void Move(GameObject closestEnemy, float distance)
        {
            const float MOVEDURATION = 0.5f;

            GameObject spike = GetClosest(spikes);
            if (spike != null && Vector3.Distance(transform.position, spike.transform.position) < 1f)
            {
                if (transform.position.x - spike.transform.position.x > 0)
                {
                    StartCoroutine(GoRight(MOVEDURATION));
                    return;
                }
                else
                {
                    StartCoroutine(GoLeft(MOVEDURATION));
                    return;
                }
            }

            float platformDistance;
            foreach (GameObject platform in platforms)
            {
                platformDistance = (platform.transform.position.x - platform.GetComponent<Collider2D>().bounds.size.x / 2) - (transform.position.x - collider.bounds.size.x / 2);
                float toRight = platformDistance - collider.bounds.size.x;
                float toLeft = platformDistance + platform.GetComponent<Collider2D>().bounds.size.x;

                if (!((toRight < 2 && toRight > 0) || (toLeft > -2 && toLeft < 0)))
                {// not close to platform
                    continue;
                }

                if ((platform.transform.position.y + platform.GetComponent<Collider2D>().bounds.size.y / 2) < (transform.position.y - collider.bounds.size.y / 2))
                {//above platform
                    if (toRight < 2 && toRight > 0)
                    {
                        StartCoroutine(GoRight(MOVEDURATION));
                    }
                    else
                    {
                        StartCoroutine(GoLeft(MOVEDURATION));
                    }
                }
                else
                {//close to platform so jump
                    m_Jump = true;
                }
            }
            if (distance < 3f)
            {
                if (closestEnemy.transform.position.x < transform.position.x)
                {
                    if (!collider.IsTouching(rightWall))
                    {
                        StartCoroutine(GoRight(MOVEDURATION));
                    }
                    else
                    {
                        StartCoroutine(GoLeft(MOVEDURATION));
                    }
                }
                else
                {
                    if (!collider.IsTouching(leftWall))
                    {
                        StartCoroutine(GoLeft(MOVEDURATION));
                    }
                    else
                    {
                        StartCoroutine(GoRight(MOVEDURATION));
                    }
                }
            }
            else
            {
                if (closestEnemy.transform.position.x > transform.position.x)
                {
                    StartCoroutine(GoRight(MOVEDURATION));
                }
                else
                {
                    StartCoroutine(GoLeft(MOVEDURATION));
                }
            }
        }

        IEnumerator GoLeft(float time)
        {
            m_IsMoving = true;
            float t = 0f;
            while (t < time)
            {
                t += Time.deltaTime;
                m_Speed = -3f;
                if (collider.IsTouching(leftWall))
                {
                    m_IsMoving = false;
                    yield break;
                }
                yield return null;
            }

            m_IsMoving = false;
        }

        IEnumerator GoRight(float time)
        {
            m_IsMoving = true;
            float t = 0f;
            while (t < time)
            {
                t += Time.deltaTime;
                m_Speed = 3f;
                if (collider.IsTouching(rightWall))
                {
                    m_IsMoving = false;
                    yield break;
                }
                yield return null;
            }

            m_IsMoving = false;
        }
    }
}

