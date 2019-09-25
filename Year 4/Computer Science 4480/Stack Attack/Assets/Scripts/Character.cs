using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

namespace StackAttack
{
    public class StackComparer : IComparer<GameObject>
    {
        public int Compare(GameObject x, GameObject y)
        {
            if (x.transform.position.y < y.transform.position.y)
            {
                return -1;
            }
            else if (x.transform.position.y == y.transform.position.y)
            {
                return 0;
            }
            else
            {
                return 1;
            }
        }
    }


    //[RequireComponent(typeof(Rigidbody2D))]
    public class Character : MonoBehaviour
    {
        [SerializeField]
        float m_Speed;
        [SerializeField]
        float m_JumpHeight;
        [SerializeField]
        int m_NumJumps;
        [SerializeField]
        float m_GravityMultiplier;
        [SerializeField]
        float m_Health;
        [SerializeField]
        float currentHealth;

        [SerializeField]
        float m_GroundCheckDistance;
        [SerializeField]
        Transform m_GroundCheck;
        [SerializeField]
        LayerMask m_GroundLayer;

        public GameObject melee;
        public GameObject ranged;
        public GameObject bomb;
        public GameObject bullets;
        public GameObject rocks;


        [SerializeField]
        GameObject healthBar;
        public GameObject stackedTo = null;

        Rigidbody2D m_Rigidbody;
        //Animator m_Animator;
        bool m_IsGrounded;
        public List<GameObject> m_CharacterStack = new List<GameObject>();
        int m_TimesJumped;

        public Projectile.Weapon weapon = Projectile.Weapon.melee;

        public bool moveDisable = false;
        public bool shootDisable = false;

        private List<GameObject> players;
        new private Collider2D collider;
        private int damageCounter = 0;

        public bool stationary;
        private List<GameObject> stationed;

        public bool leftCannon = false;
        public float cooldown = 0f;

        private int powerUpCounter1 = 0;
        private int powerUpCounter2 = 0;
        private int powerUpCounter3 = 0;
        private int powerUpCounter4 = 0;
        float powerUpTime1;
        float powerUpTime2;
        float powerUpTime3;
        float powerUpTime4;


        public float GetCurrentHealth()
        {
            return currentHealth;
        }

        void Awake()
        { 
            players = GameObject.Find("GameManager").GetComponent<GameManager>().players;
            players.Add(gameObject);

            stationed = GameObject.Find("GameManager").GetComponent<GameManager>().stationary;
            if (stationary)
            {
                stationed.Add(gameObject);
            }
            
            m_Rigidbody = GetComponent<Rigidbody2D>();
            collider = GetComponent<Collider2D>();

            m_Rigidbody.constraints = RigidbodyConstraints2D.FreezeRotation;

            currentHealth = m_Health;

            // Stack always contains self
            m_CharacterStack.Add(gameObject);
        }

        public void Move(float x, bool jump)
        {
            if (!moveDisable && m_CharacterStack[0] == gameObject)
            {
                CheckGroundStatus();

                if (!jump)
                {
                    m_Rigidbody.velocity = new Vector2(x * m_Speed, m_Rigidbody.velocity.y);
                }
                else
                {
                    if (m_TimesJumped < m_NumJumps)
                    {
                        m_Rigidbody.velocity = new Vector2(x * m_Speed, m_JumpHeight * m_CharacterStack.Count);
                        m_TimesJumped++;
                    }
                }
            }
        }

        void CheckGroundStatus()
        {
            if (Physics2D.OverlapCircle(m_GroundCheck.position, m_GroundCheckDistance, m_GroundLayer))
            {
                m_IsGrounded = true;
                m_TimesJumped = 0;
            }
            else
            {
                m_IsGrounded = false;
            }
        }

        public void Attack(float lh, float lv, float rh, float rv)
        {
            if (!shootDisable)
            {
                switch (weapon)
                {
                    case Projectile.Weapon.melee:
                        //Shoot(melee);
                        Punch(lh, lv);
                        break;
                    case Projectile.Weapon.ranged:
                        Shoot(ranged, lh, lv);
                        break;
                    case Projectile.Weapon.bomb:
                        Shoot(bomb, lh, lv);
                        break;
                    case Projectile.Weapon.bullets:
                        Shoot(bullets, rh, rv);
                        break;
                    case Projectile.Weapon.rocks:
                        Shoot(rocks, lh, lv);
                        break;
                    default:
                        break;
                }
            }
        }

        public void Punch(float h, float v)
        {
            //Vector3 aim = Camera.main.ScreenToWorldPoint(Input.mousePosition) - transform.position;

            Vector3 aim = new Vector3(h, v, 0f);
            aim.z = 0f;
            aim = Vector3.Normalize(aim);

            bool right = aim.x >= 0;

            GameObject punch = Instantiate(melee, transform.position + (new Vector3(right ? 1.5f : -1.5f, 0, 0)), Quaternion.Euler(new Vector3(0f, 0f, 0f)), transform);
            if (!right) punch.transform.localScale = new Vector3(-1f, 1f, 1f);
        }

        public void Shoot(GameObject projectile, float h = 0f, float v = 0f)
        {
            Vector3 aim = Vector3.zero;
            /*if (h == 0f && v == 0f)
            {
                aim = Camera.main.ScreenToWorldPoint(Input.mousePosition) - transform.position;
            }
            else
            {*/
                //Debug.Log("H=" + h + ", V=" + v);
                aim = new Vector3(h,v,0f);
            //}

            aim.z = 0f;
            aim = Vector3.Normalize(aim);

            bool up = aim.y >= 0;

            //Debug.Log(aim.ToString());

            Vector3 rot = new Vector3(0f, 0f, (up ? Mathf.Acos(aim.x) * 180f / Mathf.PI : 360 - (Mathf.Acos(aim.x) * 180f / Mathf.PI)));

            float angle = aim.x > 0 ? 30f : 150f;
            Vector3 rot2 = new Vector3(0f,0f,angle);

            GameObject shot;

            if (projectile == bullets)
            {
                Vector3 offset = new Vector3(2f, -1f);

                if(aim.x < 0)
                {
                    offset.x = -2f;
                }
                
                shot = Instantiate(projectile, transform.position + aim + offset, Quaternion.Euler(rot));

            }
            else if(projectile == rocks)
            {
                if (Time.time > cooldown + 2)
                {
                    Vector3 offset = new Vector3(2.75f, -1f);
                    if (leftCannon == true)
                    {
                        offset = new Vector3(-2.75f, -1f);
                        cooldown = Time.time;
                    }
                    else
                    {
                        offset = new Vector3(2.75f, -1f);
                        cooldown = Time.time;
                    }
                    shot = Instantiate(projectile, transform.position + offset, Quaternion.Euler(rot));

                }
                else
                {
                    shot = Instantiate(projectile, transform.position, Quaternion.Euler(rot));
                }
            }
            else
            {
                Vector3 offset = new Vector3(aim.x > 0f ? 1f : -1f, 0f, 0f);
                shot = Instantiate(projectile, transform.position + offset, Quaternion.Euler(rot2));
            }

            Projectile p = shot.GetComponent<Projectile>();

            p.m_Damage += damageCounter;

            if (p != null)
            {
                if (projectile == bullets)
                {
                    shot.GetComponent<Rigidbody2D>().velocity = p.m_Speed * aim;
                }
                else
                {
                    shot.GetComponent<Rigidbody2D>().velocity = p.m_Speed * (new Vector2(Mathf.Cos(angle * Mathf.PI / 180f),Mathf.Sin(angle * Mathf.PI/180f)));
                }
                p.whoShotMe = this;
            }
            else
            {
                Destroy(shot);
            }
        }

        public void TryStacking(float verticalAxis)
        {
            if (verticalAxis < 0 && stackedTo == null)
            {
                GameObject stackTo;
                for (int i = players.Count - 1; i >= 0; i--)
                {
                    if(players[i] == null || !players[i].activeInHierarchy)
                    {
                        players.RemoveAt(i);
                        continue;
                    }
                    stackTo = players[i];
                    if (m_CharacterStack.Contains(stackTo))
                        continue;
                    List<GameObject> stack = stackTo.GetComponent<Character>().m_CharacterStack;

                    //make sure they are touching the highest in the stack to stack em together
                    if (stack.Count < 3 && m_CharacterStack.Count < 3 && stackTo != gameObject && stackTo == stack[stack.Count - 1] && collider.IsTouching(stackTo.GetComponent<Collider2D>()) && transform.position.y > stackTo.transform.position.y)
                    {
                        //Debug.Log("STACKING WITH: " + stackTo.name);
                        m_Rigidbody.velocity = Vector3.zero;

                        FixedJoint2D fixedJoint = stackTo.GetComponent<FixedJoint2D>();
                        fixedJoint.connectedBody = m_Rigidbody;
                        fixedJoint.enabled = true;
                        fixedJoint.connectedAnchor = new Vector2(0f, -1f);

                        Vector3 newPosition = transform.position;
                        newPosition.x = stackTo.transform.position.x;
                        newPosition.y = stackTo.transform.position.y + collider.bounds.size.y;
                        transform.position = newPosition;

                        m_CharacterStack.AddRange(stack);
                        m_CharacterStack.Sort(new StackComparer());
                        stackedTo = stackTo;

                        foreach (GameObject teamate in stack)
                        {
                            teamate.GetComponent<Character>().m_CharacterStack = new List<GameObject>(m_CharacterStack);
                            Debug.Log("STACKING WITH: " + teamate.name);
                        }

                        // Set weapons based on # in stack. m_Character stack will always be sorted from lowest to highest.
                        for (int j = 0; j < m_CharacterStack.Count; j++)
                        {
                            if (m_CharacterStack[j].GetComponent<Character>().stationary == true)
                            {
                                if (m_CharacterStack[j].gameObject.tag == "turret")
                                {
                                    m_CharacterStack[j + 1].GetComponent<Character>().weapon = Projectile.GetWeapon(10);
                                    Debug.Log(this.weapon);
                                }
                                else if (m_CharacterStack[j].gameObject.tag == "cannon")
                                {
                                    m_CharacterStack[j + 1].GetComponent<Character>().weapon = Projectile.GetWeapon(20);
                                }
                                else if (m_CharacterStack[j].gameObject.tag == "cannon1")
                                {
                                    m_CharacterStack[j + 1].GetComponent<Character>().weapon = Projectile.GetWeapon(20);
                                    leftCannon = true;
                                }
                                j++;
                            }
                            else
                            {
                                m_CharacterStack[j].GetComponent<Character>().weapon = Projectile.GetWeapon(j);
                            }
                            Debug.Log("STACKING! recieved weapon: " + Projectile.GetWeapon(j));
                        }

                        moveDisable = true;
                        break;
                    }
                }

                // test if 1 stack remains, for victory condition
                TestOneStack();

            }
            else if (verticalAxis > 0 && gameObject != m_CharacterStack[0] && stackedTo != null)
            {
                unstack();
                m_TimesJumped = 0;
            }
        }

        public void unstack()
        {
            //Debug.Log("UNSTACKING?");
            int myIndex = m_CharacterStack.LastIndexOf(gameObject);

            if (myIndex != 0 && stackedTo.activeInHierarchy)
            {
                // disconnect fixed joint
                FixedJoint2D fixedJoint = stackedTo.GetComponent<FixedJoint2D>();
                fixedJoint.connectedBody = null;
                fixedJoint.enabled = false;

                stackedTo = null;

                // Split stack into two groups: lower & upper
                List<GameObject> lowerStack = new List<GameObject>();
                List<GameObject> upperStack = new List<GameObject>();
                for (int i = 0; i < m_CharacterStack.Count; i++)
                {
                    if (i < myIndex)
                    {
                        lowerStack.Add(m_CharacterStack[i]);
                    }
                    else
                    {
                        upperStack.Add(m_CharacterStack[i]);
                    }
                }

                List<GameObject> stackCopy = new List<GameObject>(m_CharacterStack.ToArray());
                for (int i = stackCopy.Count - 1; i >= 0; i--)
                {
                    stackCopy[i].GetComponent<Character>().m_CharacterStack = new List<GameObject>((i < myIndex ? lowerStack : upperStack));
                }

                // Set weapons for lower stack
                for (int i = 0; i < lowerStack.Count; i++)
                {
                    lowerStack[i].GetComponent<Character>().weapon = Projectile.GetWeapon(i);
                }

                // Set weapons for upper stack
                for (int i = 0; i < upperStack.Count; i++)
                {
                    upperStack[i].GetComponent<Character>().weapon = Projectile.GetWeapon(i);
                }

                moveDisable = false;

                // Pop the stacks apart a little
                m_Rigidbody.velocity += new Vector2(0,m_Speed);
            }
        }

        public void TakeDamage(float damage)
        {
            if (!stationary)
            {
                float barHealth;
                currentHealth -= damage;
                barHealth = currentHealth / m_Health;
                SetHealthBar(barHealth);

                if (currentHealth <= 0)
                {
                    // Death
                    unstack();
                    if (m_CharacterStack.Count > 1)
                    {
                        m_CharacterStack[1].GetComponent<Character>().unstack();
                    }
                    players.Remove(gameObject);

                    // Set match rewards for dead player
                    if (GetComponent<UserCharacterController>() != null)
                    {
                        GameSetup gs = FindObjectOfType<GameSetup>();
                        if (gs != null)
                        {
                            int playerIndex = GetComponent<UserCharacterController>().playerId;

                            if (gs.rankings.ContainsKey(playerIndex))
                            {
                                TimerScript ts = FindObjectOfType<TimerScript>();
                                if (ts != null)
                                {
                                    gs.rankings[playerIndex].deathTime = ts.GetElapsedTime();
                                }
                                gs.rankings[playerIndex].coinReward = 0;
                            }
                            else
                            {
                                MatchStats ms = new MatchStats();
                                TimerScript ts = FindObjectOfType<TimerScript>();
                                if (ts != null)
                                {
                                    ms.deathTime = ts.GetElapsedTime();
                                }
                                ms.coinReward = 0;
                                ms.coinTotal = 0;
                                gs.rankings.Add(playerIndex, ms);
                            }
                        }
                    }

                    TestOneStack();

                    Destroy(gameObject);
                }
            }
        }

        void TestOneStack()
        {
            // Test 1 stack remaining
            
            bool onlyOneStack = true;

            List<GameObject> stack = new List<GameObject>();
            foreach (GameObject player in players)
            {
                if (!player.GetComponent<Character>().stationary)
                {
                    stack = player.GetComponent<Character>().m_CharacterStack;
                    break;
                }
            }

            foreach (GameObject player in players)
            {
                if (!player.GetComponent<Character>().stationary)
                {
                    foreach (GameObject player0 in players)
                    {
                        if (!player0.GetComponent<Character>().stationary)
                        {
                            if (!player.GetComponent<Character>().m_CharacterStack.Contains(player0))
                            {
                                onlyOneStack = false;
                                break;
                            }
                        }
                    }
                }

                if (!onlyOneStack)
                    break;
            }

            // if only 1 stack remains, all win.
            if (onlyOneStack)
            {
                GameSetup gs = FindObjectOfType<GameSetup>();

                if (gs != null)
                {
                    foreach (GameObject winner in stack)
                    {
                        // AI don't get points
                        if (winner.GetComponent<UserCharacterController>() != null)
                        {
                            int playerIndex = winner.GetComponent<UserCharacterController>().playerId;

                            if (gs.rankings.ContainsKey(playerIndex))
                            {
                                gs.rankings[playerIndex].deathTime = -1;
                                gs.rankings[playerIndex].coinReward = gs.matchPoints / stack.Count;
                                gs.rankings[playerIndex].coinTotal += gs.rankings[playerIndex].coinReward;
                            }
                            else
                            {
                                MatchStats ms = new MatchStats();
                                ms.deathTime = -1; // winner didn't die
                                ms.coinReward = gs.matchPoints / stack.Count;
                                ms.coinTotal = ms.coinReward;
                                gs.rankings.Add(playerIndex, ms);
                            }
                        }
                    }
                }

                LevelLoader.initialized = false;
                LevelLoader levelLoader = FindObjectOfType<LevelLoader>();
                if (levelLoader != null)
                {
                    Destroy(levelLoader.gameObject);
                }

                SceneManager.LoadScene("MatchResults");
            }
            
        }

        public void KnockBack(float projectileMass, Vector2 projectileVelocity, float stunTime)
        {
            if (!stationary)
            {
                m_Rigidbody.velocity += (m_Rigidbody.mass / projectileMass) * projectileVelocity;
                StartCoroutine(FreezeMoveInput(stunTime));
            }
        }

        public IEnumerator FreezeMoveInput(float time)
        {
            moveDisable = true;
            yield return new WaitForSeconds(time);
            moveDisable = false;
        }

        public IEnumerator FreezeShootInput(float time)
        {
            shootDisable = true;
            yield return new WaitForSeconds(time);
            shootDisable = false;
        }

        /// <summary>
        /// Sets the value of the health bar.
        /// </summary>
        /// <param name="health">Health.</param>
        public void SetHealthBar(float health)
        {
            healthBar.transform.localScale = new Vector2(health, healthBar.transform.localScale.y);
        }

        public bool IsStacked()
        {
            return stackedTo != null;
        }

        void powerUpTimer()
        {
            if (powerUpCounter1 > 0)
            {
                powerUpTime1 = Time.time + 10;
            }
            else if (powerUpCounter2 > 0)
            {
                powerUpTime2 = Time.time + 10;
            }
            else if (powerUpCounter3 > 0)
            {
                powerUpTime3 = Time.time + 10;
            }
            else if (powerUpCounter4 > 0)
            {
                powerUpTime4 = Time.time + 10;
            }
        }

        // Powerup function used to apply powerup effects to the player
        public void powerUp(int type)
        {
            if (type == 4)
            {
                m_Speed += 1;
                powerUpCounter4++;
            }
            if (type == 3)
            {
                m_NumJumps += 1;
                powerUpCounter3++;
            }
            if (type == 2)
            {
                damageCounter += 1;
                powerUpCounter2++;
            }
            if (type == 1)
            {
                currentHealth += 5;
                if(currentHealth > m_Health)
                {
                    currentHealth = m_Health;
                }
            }
            if (type == 0)
            {
                m_JumpHeight += 1;
                powerUpCounter1++;
            }
            powerUpTimer();
        }

        void powerUpNormalizer()
        {
            if (Time.time > powerUpTime1 && powerUpCounter1 > 0)
            {
                m_JumpHeight -= 1;
                powerUpCounter1--;
            }
            else if (Time.time > powerUpTime2 && powerUpCounter2 > 0)
            {
                damageCounter -= 1;
                powerUpCounter2--;
            }
            else if (Time.time > powerUpTime3 && powerUpCounter3 > 0)
            {
                m_NumJumps -= 1;
                powerUpCounter3--;
            }
            else if (Time.time > powerUpTime4 && powerUpCounter4 > 0)
            {
                m_Speed -= 1;
                powerUpCounter4--;
            }
        }
    }
}
