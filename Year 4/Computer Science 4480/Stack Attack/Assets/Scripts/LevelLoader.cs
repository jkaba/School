using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace StackAttack
{
    public class LevelLoader : MonoBehaviour
    {
        public int levelIndex = 0;
        public List<GameObject> levelPrefabs;

        CharacterSpawner spawner;
        PowerUpSpawner pupSpawner;
        
        public static bool initialized = false;

        private static LevelLoader instance;

        private void Awake()
        {
            if (instance == null)
            { 
                DontDestroyOnLoad(gameObject);
                instance = this;
            }
            else
            {
                Destroy(gameObject);
            }
        }

        // Use this for initialization
        public void InitializeLevel()
        {
            if (!initialized)
            {
                initialized = true;
                GameObject levelLoaded = LoadLevel(levelIndex);
                spawner = FindObjectOfType<CharacterSpawner>();
                spawner.spawnPositions = new List<Transform>(levelLoaded.transform.Find("SpawnInfo").GetComponentsInChildren<Transform>());
                spawner.spawnPositions.Remove(levelLoaded.transform.Find("SpawnInfo"));
                spawner.SpawnCharacters();
                pupSpawner = FindObjectOfType<PowerUpSpawner>();
                pupSpawner.spawnPositions = new List<Transform>(levelLoaded.transform.Find("SpawnInfo").GetComponentsInChildren<Transform>());
                pupSpawner.spawnPositions.Remove(levelLoaded.transform.Find("SpawnInfo"));
                pupSpawner.SpawnPower();
            }
            
        }

        public GameObject LoadLevel()
        {
            return LoadLevel(levelIndex);
        }

        public GameObject LoadLevel(int index)
        {
            if (index < 0)
            {
                index = 0;
            }

            GameObject level = Instantiate(levelPrefabs[index]);
            List<GameObject> platforms = GameObject.Find("GameManager").GetComponent<GameManager>().platforms;
            List<GameObject> floors = GameObject.Find("GameManager").GetComponent<GameManager>().floors;
            List<GameObject> spikes = GameObject.Find("GameManager").GetComponent<GameManager>().spikes;
            GameObject platform = null;
            GameObject floor = null;
            if (GameObject.Find("Spikes") != null)
            {
                foreach (Transform child in GameObject.Find("Spikes").transform)
                {
                    spikes.Add(child.gameObject);
                }
            }
            for (int i = 0; i < 10; i++)
            {
                if (i == 0)
                {
                    platform = GameObject.Find("Platform");
                    floor = GameObject.Find("Floor");
                }
                else
                {
                    platform = GameObject.Find("Platform (" + i + ")");
                    floor = GameObject.Find("Floor (" + i + ")");
                }
                if (platform != null)
                {
                    platforms.Add(platform);
                }
                if (floor != null)
                {
                    platforms.Add(floor);
                }
            }
            return level;
        }

        public void SetLevel(int index)
        {
            levelIndex = 0;
        }
    }
}
