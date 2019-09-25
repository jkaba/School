using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace StackAttack
{
    public class GameSetup : MonoBehaviour
    {
        public GameObject[] selectedCharacterPrefabs;
        public int selectedLevelIndex;

        public int matchPoints;

        public Dictionary<int, MatchStats> rankings;

        private static GameSetup instance;

        private void Awake()
        {
            if (instance == null)
            {
                DontDestroyOnLoad(gameObject);
                instance = this;

                rankings = new Dictionary<int, MatchStats>();
            }
            else
            {
                Destroy(gameObject);
            }
        }
    }
}