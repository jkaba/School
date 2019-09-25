using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace StackAttack { 
public class PowerUpSpawner : MonoBehaviour {
        GameSetup setup;
        public List<Transform> spawnPositions; // initialized in LevelLoader
        public List<GameObject> powerups;
        public float powerTimer = 10f;
        int lastSpawn = -1;

        private void Awake()
        {
            setup = FindObjectOfType<GameSetup>();
        }

        // Right now this is going to be very simple:
        //  It will spawn the player in one of the spawn positions,
        //  and it will spawn computer players in all other positions

        
        public void SpawnPower() // called from LevelLoader
        {
            if (setup != null)
            {

            }
            else { Debug.Log("No Setup!"); }
        }


        private void Update()
        {
            PowerTimer();
            if (powerTimer <= 0)
            {


                int playerIndex = Random.Range(0, spawnPositions.Count);
                while(playerIndex == lastSpawn)
                {
                    playerIndex = Random.Range(0, spawnPositions.Count);
                }
                lastSpawn = playerIndex;


                Instantiate(powerups[Random.Range(0, powerups.Count)], spawnPositions[playerIndex].position, spawnPositions[playerIndex].rotation);
                powerTimer = 10f;
            }
        }

        void PowerTimer()
        {
            powerTimer -= Time.deltaTime;

        }
    }

}
