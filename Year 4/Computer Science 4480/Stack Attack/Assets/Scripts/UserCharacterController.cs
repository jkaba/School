using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Rewired;

namespace StackAttack
{
    [RequireComponent(typeof(CharacterController))]
    public class UserCharacterController : MonoBehaviour
    {
        public int playerId = 0;
        
        private Character m_Character;
        private Player player; //Rewired
        private bool m_Jump;
        private bool m_Attack;
        private float m_Stack;
        private float attackTimer = 0f;
        private const float MELEEDELAY = 0.3f;
        private const float ARROWDELAY = 0.4f;
        private const float BOMBDELAY = 0.5f;
        private const float TURRETDELAY = 0.3f;

        private GameObject meleePanel0;
        private GameObject arrowPanel0;
        private GameObject bombPanel0;
        private GameObject cannonPanel0;
        private GameObject bulletPanel0;

        private GameObject meleePanel1;
        private GameObject arrowPanel1;
        private GameObject bombPanel1;
        private GameObject cannonPanel1;
        private GameObject bulletPanel1;

        private GameObject meleePanel2;
        private GameObject arrowPanel2;
        private GameObject bombPanel2;
        private GameObject cannonPanel2;
        private GameObject bulletPanel2;

        private GameObject meleePanel3;
        private GameObject arrowPanel3;
        private GameObject bombPanel3;
        private GameObject cannonPanel3;
        private GameObject bulletPanel3;

        private GameObject player1Panel;
        private GameObject player2Panel;
        private GameObject player3Panel;
        private GameObject player4Panel;

        int count = 0;

        float aimh = 0f;

        private void Start()
        {
            //player 1 HUD
            player1Panel = GameObject.Find("Player1Weapons");
            meleePanel0 = GameObject.Find("MeleePanel0");
            arrowPanel0 = GameObject.Find("ArrowPanel0");
            bombPanel0 = GameObject.Find("BombPanel0");
            cannonPanel0 = GameObject.Find("CannonPanel0");
            bulletPanel0 = GameObject.Find("BulletPanel0");

            //player 2 HUD
            player2Panel = GameObject.Find("Player2Weapons");
            meleePanel1 = GameObject.Find("MeleePanel1");
            arrowPanel1 = GameObject.Find("ArrowPanel1");
            bombPanel1 = GameObject.Find("BombPanel1");
            cannonPanel1 = GameObject.Find("CannonPanel1");
            bulletPanel1 = GameObject.Find("BulletPanel1");

            //player 3 HUD
            player3Panel = GameObject.Find("Player3Weapons");
            meleePanel2 = GameObject.Find("MeleePanel2");
            arrowPanel2 = GameObject.Find("ArrowPanel2");
            bombPanel2 = GameObject.Find("BombPanel2");
            cannonPanel2 = GameObject.Find("CannonPanel2");
            bulletPanel2 = GameObject.Find("BulletPanel2");

            //player 4 HUD
            player4Panel = GameObject.Find("Player4Weapons");
            meleePanel3 = GameObject.Find("MeleePanel3");
            arrowPanel3 = GameObject.Find("ArrowPanel3");
            bombPanel3 = GameObject.Find("BombPanel3");
            cannonPanel3 = GameObject.Find("CannonPanel3");
            bulletPanel3 = GameObject.Find("BulletPanel3");

        }

        // Use this for initialization
        public void InitializeController(int id)
        {
            playerId = id;
            player = ReInput.players.GetPlayer(playerId);
            m_Character = GetComponent<Character>();
            
        }

        private void Update()
        {
            if(count == 0)
            {
                /*set all HUD objects to false for 1 tick in order
                to ensure that ones that aren't assigned to a player
                don't need to be used */
                player1Panel.SetActive(false);
                player2Panel.SetActive(false);
                player3Panel.SetActive(false);
                player4Panel.SetActive(false);

                meleePanel0.SetActive(false);
                arrowPanel0.SetActive(false);
                bombPanel0.SetActive(false);
                cannonPanel0.SetActive(false);
                bulletPanel0.SetActive(false);

                meleePanel1.SetActive(false);
                arrowPanel1.SetActive(false);
                bombPanel1.SetActive(false);
                cannonPanel1.SetActive(false);
                bulletPanel1.SetActive(false);

                meleePanel2.SetActive(false);
                arrowPanel2.SetActive(false);
                bombPanel2.SetActive(false);
                cannonPanel2.SetActive(false);
                bulletPanel2.SetActive(false);

                meleePanel3.SetActive(false);
                arrowPanel3.SetActive(false);
                bombPanel3.SetActive(false);
                cannonPanel3.SetActive(false);
                bulletPanel3.SetActive(false);

                count += 1;
            }

            if (Input.GetKeyDown(KeyCode.Alpha1))
            {
                Debug.Log("MELEE");
                m_Character.weapon = Projectile.Weapon.melee;
            }
            else if (Input.GetKeyDown(KeyCode.Alpha2))
            {
                Debug.Log("ARROWS");
                m_Character.weapon = Projectile.Weapon.ranged;
            }
            else if (Input.GetKeyDown(KeyCode.Alpha3))
            {
                Debug.Log("BOMBS");
                m_Character.weapon = Projectile.Weapon.bomb;
            }

            if (!m_Jump)
            {
                m_Jump = player.GetButtonDown("Jump");
            }

            if ((m_Character.weapon == Projectile.Weapon.bomb && attackTimer > BOMBDELAY)
                || (m_Character.weapon == Projectile.Weapon.ranged && attackTimer > ARROWDELAY)
                || (m_Character.weapon == Projectile.Weapon.melee && attackTimer > ARROWDELAY)
                || (m_Character.weapon != Projectile.Weapon.bomb && m_Character.weapon != Projectile.Weapon.ranged && m_Character.weapon != Projectile.Weapon.melee && attackTimer > TURRETDELAY))
            {
                attackTimer = 0f;
            }
            else if (attackTimer != 0f)
            {
                attackTimer += Time.deltaTime;
            }
            else if (attackTimer == 0f && !m_Attack)
            {
                m_Attack = player.GetButtonDown("Attack");
                aimh = player.GetAxisRaw("Attack_Axis");
            }

            if (m_Stack == 0f)
            {
                m_Stack = player.GetAxisRaw("Vertical");
            }

            //player1 weapon HUD
            if (m_Character.weapon == Projectile.Weapon.melee && playerId == 0)
            {
                player1Panel.SetActive(true);
                meleePanel0.SetActive(true);
                arrowPanel0.SetActive(false);
                bombPanel0.SetActive(false);
                cannonPanel0.SetActive(false);
                bulletPanel0.SetActive(false);
            }
            else if (m_Character.weapon == Projectile.Weapon.ranged && playerId == 0)
            {
                meleePanel0.SetActive(false);
                arrowPanel0.SetActive(true);
                bombPanel0.SetActive(false);
                cannonPanel0.SetActive(false);
                bulletPanel0.SetActive(false);
            }
            else if (m_Character.weapon == Projectile.Weapon.bomb && playerId == 0)
            {
                meleePanel0.SetActive(false);
                arrowPanel0.SetActive(false);
                bombPanel0.SetActive(true);
                cannonPanel0.SetActive(false);
                bulletPanel0.SetActive(false);
            }
            else if (m_Character.weapon == Projectile.Weapon.bullets && playerId == 0)
            {
                meleePanel0.SetActive(false);
                arrowPanel0.SetActive(false);
                bombPanel0.SetActive(false);
                cannonPanel0.SetActive(false);
                bulletPanel0.SetActive(true);
            }
            else if (m_Character.weapon == Projectile.Weapon.rocks && playerId == 0)
            {
                meleePanel0.SetActive(false);
                arrowPanel0.SetActive(false);
                bombPanel0.SetActive(false);
                cannonPanel0.SetActive(true);
                bulletPanel0.SetActive(false);
            }

            //player2 weapon HUD
            if (m_Character.weapon == Projectile.Weapon.melee && playerId == 1)
            {

                player2Panel.SetActive(true);
                meleePanel1.SetActive(true);
                arrowPanel1.SetActive(false);
                bombPanel1.SetActive(false);
                cannonPanel1.SetActive(false);
                bulletPanel1.SetActive(false);
            }
            else if (m_Character.weapon == Projectile.Weapon.ranged && playerId == 1)
            {
                meleePanel1.SetActive(false);
                arrowPanel1.SetActive(true);
                bombPanel1.SetActive(false);
                cannonPanel1.SetActive(false);
                bulletPanel1.SetActive(false);
            }
            else if (m_Character.weapon == Projectile.Weapon.bomb && playerId == 1)
            {
                meleePanel1.SetActive(false);
                arrowPanel1.SetActive(false);
                bombPanel1.SetActive(true);
                cannonPanel1.SetActive(false);
                bulletPanel1.SetActive(false);
            }
            else if (m_Character.weapon == Projectile.Weapon.bullets && playerId == 1)
            {
                meleePanel1.SetActive(false);
                arrowPanel1.SetActive(false);
                bombPanel1.SetActive(false);
                cannonPanel1.SetActive(false);
                bulletPanel1.SetActive(true);
            }
            else if (m_Character.weapon == Projectile.Weapon.rocks && playerId == 1)
            {
                meleePanel1.SetActive(false);
                arrowPanel1.SetActive(false);
                bombPanel1.SetActive(false);
                cannonPanel1.SetActive(true);
                bulletPanel1.SetActive(false);
            }


            //player3 weapon HUD
            if (m_Character.weapon == Projectile.Weapon.melee && playerId == 2)
            {
                player3Panel.SetActive(true);
                meleePanel2.SetActive(true);
                arrowPanel2.SetActive(false);
                bombPanel2.SetActive(false);
                cannonPanel2.SetActive(false);
                bulletPanel2.SetActive(false);
            }
            else if (m_Character.weapon == Projectile.Weapon.ranged && playerId == 2)
            {
                meleePanel2.SetActive(false);
                arrowPanel2.SetActive(true);
                bombPanel2.SetActive(false);
                cannonPanel2.SetActive(false);
                bulletPanel2.SetActive(false);
            }
            else if (m_Character.weapon == Projectile.Weapon.bomb && playerId == 2)
            {
                meleePanel2.SetActive(false);
                arrowPanel2.SetActive(false);
                bombPanel2.SetActive(true);
                cannonPanel2.SetActive(false);
                bulletPanel2.SetActive(false);
            }
            else if (m_Character.weapon == Projectile.Weapon.bullets && playerId == 2)
            {
                meleePanel2.SetActive(false);
                arrowPanel2.SetActive(false);
                bombPanel2.SetActive(false);
                cannonPanel2.SetActive(false);
                bulletPanel2.SetActive(true);
            }
            else if (m_Character.weapon == Projectile.Weapon.rocks && playerId == 2)
            {
                meleePanel2.SetActive(false);
                arrowPanel2.SetActive(false);
                bombPanel2.SetActive(false);
                cannonPanel2.SetActive(true);
                bulletPanel2.SetActive(false);
            }

            //player4 weapon HUD
            if (m_Character.weapon == Projectile.Weapon.melee && playerId == 3)
            {
                player4Panel.SetActive(true);
                meleePanel3.SetActive(true);
                arrowPanel3.SetActive(false);
                bombPanel3.SetActive(false);
                cannonPanel3.SetActive(false);
                bulletPanel3.SetActive(false);
            }
            else if (m_Character.weapon == Projectile.Weapon.ranged && playerId == 3)
            {
                meleePanel3.SetActive(false);
                arrowPanel3.SetActive(true);
                bombPanel3.SetActive(false);
                cannonPanel3.SetActive(false);
                bulletPanel3.SetActive(false);
            }
            else if (m_Character.weapon == Projectile.Weapon.bomb && playerId == 3)
            {
                meleePanel3.SetActive(false);
                arrowPanel3.SetActive(false);
                bombPanel3.SetActive(true);
                cannonPanel3.SetActive(false);
                bulletPanel3.SetActive(false);
            }
            else if (m_Character.weapon == Projectile.Weapon.bullets && playerId == 3)
            {
                meleePanel3.SetActive(false);
                arrowPanel3.SetActive(false);
                bombPanel3.SetActive(false);
                cannonPanel3.SetActive(false);
                bulletPanel3.SetActive(true);
            }
            else if (m_Character.weapon == Projectile.Weapon.rocks && playerId == 3)
            {
                meleePanel3.SetActive(false);
                arrowPanel3.SetActive(false);
                bombPanel3.SetActive(false);
                cannonPanel3.SetActive(true);
                bulletPanel3.SetActive(false);
            }

        }

        private void FixedUpdate()
        {
            float x = player.GetAxisRaw("Horizontal");
            m_Character.Move(x, m_Jump);
            m_Jump = false;

            if (m_Attack || aimh != 0f)
            {
                attackTimer += Time.deltaTime;
                m_Character.Attack(aimh, player.GetAxis("AimV"), player.GetAxis("AimH"), player.GetAxis("AimV"));
                m_Attack = false;
                aimh = 0f;
            }
            if (m_Stack != 0f)
            {
                m_Character.TryStacking(m_Stack);
                m_Stack = 0f;
            }
        }
    }
}
