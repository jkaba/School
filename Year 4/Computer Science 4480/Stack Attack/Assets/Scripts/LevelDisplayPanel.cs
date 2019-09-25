using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

namespace StackAttack
{
    public class LevelDisplayPanel : MonoBehaviour
    {

        public int index;
        LevelLoader loader;

        private void Start()
        {
            loader = FindObjectOfType<LevelLoader>();
            GetComponent<Button>().onClick.AddListener(BtnClicked);
        }

        public void BtnClicked()
        {
            loader.levelIndex = index;
            SceneManager.LoadScene("main");
        }
    }

}