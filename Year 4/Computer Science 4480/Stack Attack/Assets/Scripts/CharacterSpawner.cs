using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace StackAttack
{
    public class CharacterSpawner : MonoBehaviour
    {

        GameSetup setup;
        public List<Transform> spawnPositions; // initialized in LevelLoader
        public List<GameObject> computerPlayerPrefabs;

        private void Awake()
        {
            setup = FindObjectOfType<GameSetup>();

            LevelLoader levelLoader = FindObjectOfType<LevelLoader>();
            if (levelLoader != null)
            {
                levelLoader.InitializeLevel();
            }
        }

        // Right now this is going to be very simple:
        //  It will spawn the player in one of the spawn positions,
        //  and it will spawn computer players in all other positions

        public void SpawnCharacters() // called from LevelLoader
        {
            Debug.Log("Spawning Characters!");
            if (setup != null)
            {
                //int playerIndex = Random.Range(0, spawnPositions.Count);

                for (int i = 0; i < spawnPositions.Count; i++)
                {
                    if (i < setup.selectedCharacterPrefabs.Length && setup.selectedCharacterPrefabs[i] != null)
                    {
                        GameObject spawnedPlayer = Instantiate(setup.selectedCharacterPrefabs[i], spawnPositions[i].position, spawnPositions[i].rotation);
                        spawnedPlayer.GetComponent<UserCharacterController>().InitializeController(i);
                    }
                    else if (computerPlayerPrefabs.Count > 0)
                    {
                        // Choose a random computer
                        Instantiate(computerPlayerPrefabs[Random.Range(0, computerPlayerPrefabs.Count)], spawnPositions[i].position, spawnPositions[i].rotation);
                    }
                }
            }
            else { Debug.Log("No Setup!"); }
        }

    }
}