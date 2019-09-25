using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using Rewired;
using UnityEngine.SceneManagement;

namespace StackAttack
{

    public class LevelSelect : MonoBehaviour
    {
        public GameObject levelDisplayPrefab;
        public Transform gridLayout;
        public LevelLoader levelLoader;

        List<Button> gridButtons;

        int indexSelected;

        static float moveTime = 0.2f;
        float moveTimer;

        // Use this for initialization
        void Awake()
        {
            moveTimer = moveTime;
            indexSelected = 0;

            gridButtons = new List<Button>();

            int i = 0;
            foreach (GameObject prefab in levelLoader.levelPrefabs)
            {
                GameObject gridItem = Instantiate(levelDisplayPrefab, gridLayout);
                Transform bg = prefab.transform.Find("Background");
                if (bg != null)
                {
                    if (bg.GetComponent<SpriteRenderer>() != null)
                    {
                        gridItem.GetComponent<Image>().sprite = bg.GetComponent<SpriteRenderer>().sprite;
                    }

                    gridItem.GetComponentInChildren<Text>().text = prefab.name;
                }

                gridItem.GetComponent<LevelDisplayPanel>().index = i;

                gridItem.GetComponent<Button>().interactable = (i == 0);
                gridButtons.Add(gridItem.GetComponent<Button>());


                i++;
            }
        }

        private void Update()
        {
            if (moveTimer < moveTime)
            {
                moveTimer += Time.deltaTime;
            }

            int moveLeft = 0;
            int moveRight = 0;

            for (int i = 0; i < ReInput.players.playerCount; i++)
            {
                if (ReInput.players.GetPlayer(i).GetButtonDown("UICancel"))
                {
                    if (FindObjectOfType<LevelLoader>() != null)
                    {
                        Destroy(FindObjectOfType<LevelLoader>().gameObject);
                        LevelLoader.initialized = false;
                    }
                    SceneManager.LoadScene("CharacterSelect");
                }
                else if (ReInput.players.GetPlayer(i).GetButtonDown("UISubmit"))
                {
                    FindObjectOfType<LevelLoader>().levelIndex = indexSelected;
                    SceneManager.LoadScene("main");
                }
                else if (Mathf.Abs(ReInput.players.GetPlayer(i).GetAxis("UIHorizontal")) > 0.2f)
                {
                    if (ReInput.players.GetPlayer(i).GetAxis("UIHorizontal") < 0)
                    {
                        moveLeft++;
                    }

                    if (ReInput.players.GetPlayer(i).GetAxis("UIHorizontal") > 0)
                    {
                        moveRight++;
                    }
                }
            }

            if (moveTimer >= moveTime && moveLeft != moveRight)
            {
                gridButtons[indexSelected].interactable = false;
                moveTimer = 0f;
                if (moveRight > moveLeft)
                {
                    indexSelected++;
                    if (indexSelected > gridButtons.Count - 1)
                    {
                        indexSelected = 0;
                    }
                }
                else if (moveLeft > moveRight)
                {
                    indexSelected--;
                    if (indexSelected < 0)
                    {
                        indexSelected = gridButtons.Count - 1;
                    }
                }
                gridButtons[indexSelected].interactable = true;
            }
        }
    }

}