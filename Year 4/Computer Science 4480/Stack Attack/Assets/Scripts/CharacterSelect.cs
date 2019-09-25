using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
using UnityEngine.UI;
using Rewired;

namespace StackAttack
{
    public class CharacterSelect : MonoBehaviour
    {
        public int playerIndex;
        Player player;

        public Image characterDisplay;

        public List<GameObject> characterPrefabs;

        GameSetup setup;

        public int slideSpeed;
        public Button rightButton;
        public Button leftButton;

        private int index;

        public bool ready;

        public int previousInputH;
        public int inputH;

        private void Awake()
        {
            setup = FindObjectOfType<GameSetup>();
            ready = false;

            if (playerIndex < ReInput.players.playerCount)
            {
                player = ReInput.players.GetPlayer(playerIndex);

                if ((setup = FindObjectOfType<GameSetup>()) != null)
                {
                    if (setup.selectedCharacterPrefabs[playerIndex] != null)
                    {
                        index = characterPrefabs.IndexOf(setup.selectedCharacterPrefabs[playerIndex]);
                        if (index == -1)
                        {
                            index = 0;
                        }
                        else
                        {
                            characterDisplay.sprite = characterPrefabs[index].GetComponentInChildren<SpriteRenderer>().sprite;
                        }
                    }

                    if (setup.rankings.ContainsKey(playerIndex))
                    {
                        if (transform.Find("Points") != null)
                        {
                            transform.Find("Points").GetComponent<Text>().text = setup.rankings[playerIndex].coinTotal + " Points";
                        }
                    }
                }
            }
        }

        public void Update()
        {
            if (player != null)
            {
                if (player.GetButtonDown("UISubmit"))
                {
                    ready = true;
                    rightButton.interactable = false;
                    leftButton.interactable = false;
                    StartGame();
                }

                if (player.GetButtonDown("UICancel"))
                {
                    ready = false;
                    rightButton.interactable = true;
                    leftButton.interactable = true;
                }

                if (!ready)
                {
                    previousInputH = inputH;
                    float h = player.GetAxis("UIHorizontal");
                    if (Mathf.Abs(h) < 0.2f)
                    {
                        inputH = 0;
                    }
                    else if (h >= 0.2f)
                    {
                        inputH = 1;
                    }
                    else if (h <= -0.2f)
                    {
                        inputH = -1;
                    }

                    if (!ready && inputH != previousInputH && rightButton.interactable && leftButton.interactable)
                    {
                        if (inputH > 0f)
                        {
                            ToggleRight();
                        }
                        else if (inputH < 0f)
                        {
                            ToggleLeft();
                        }
                    }
                }
            }
        }

        public void ToggleLeft()
        {
            StartCoroutine(SlideRightCo());
        }

        public void ToggleRight()
        {
            StartCoroutine(SlideLeftCo());
        }

        public void StartGame()
        {
            setup.selectedCharacterPrefabs[playerIndex] = characterPrefabs[index];

            bool allReady = true;
            foreach (CharacterSelect cs in FindObjectsOfType<CharacterSelect>())
            {
                if (!cs.ready)
                {
                    allReady = false;
                    break;
                }
            }
            
            if (allReady)
            {
                SceneManager.LoadScene("LevelSelect");
            }
        }

        public IEnumerator SlideRightCo()
        {
            rightButton.interactable = false;
            leftButton.interactable = false;

            Vector3 initialPos = characterDisplay.transform.position;

            while (characterDisplay.transform.position.x < initialPos.x + 120f)
            {
                yield return null;
                characterDisplay.transform.position = new Vector3(characterDisplay.transform.position.x + Time.deltaTime * slideSpeed, initialPos.y, initialPos.z);
            }

            index--;
            if (index < 0)
            {
                index = characterPrefabs.Count - 1;
            }

            characterDisplay.sprite = characterPrefabs[index].GetComponentInChildren<SpriteRenderer>().sprite;

            characterDisplay.transform.position = new Vector3(initialPos.x - 120f, initialPos.y, initialPos.z);
            yield return null;

            while (characterDisplay.transform.position.x < initialPos.x)
            {
                yield return null;
                characterDisplay.transform.position = new Vector3(characterDisplay.transform.position.x + Time.deltaTime * slideSpeed, initialPos.y, initialPos.z);
            }

            characterDisplay.transform.position = initialPos;

            rightButton.interactable = true;
            leftButton.interactable = true;
        }

        public IEnumerator SlideLeftCo()
        {
            rightButton.interactable = false;
            leftButton.interactable = false;

            Vector3 initialPos = characterDisplay.transform.position;

            while (characterDisplay.transform.position.x > initialPos.x - 120f)
            {
                yield return null;
                characterDisplay.transform.position = new Vector3(characterDisplay.transform.position.x + Time.deltaTime * -slideSpeed, initialPos.y, initialPos.z);
            }

            index++;
            if (index == characterPrefabs.Count)
            {
                index = 0;
            }

            characterDisplay.sprite = characterPrefabs[index].GetComponentInChildren<SpriteRenderer>().sprite;

            characterDisplay.transform.position = new Vector3(initialPos.x + 120f, initialPos.y, initialPos.z);
            yield return null;

            while (characterDisplay.transform.position.x > initialPos.x)
            {
                yield return null;
                characterDisplay.transform.position = new Vector3(characterDisplay.transform.position.x + Time.deltaTime * -slideSpeed, initialPos.y, initialPos.z);
            }

            characterDisplay.transform.position = initialPos;

            rightButton.interactable = true;
            leftButton.interactable = true;
        }
    }
}
