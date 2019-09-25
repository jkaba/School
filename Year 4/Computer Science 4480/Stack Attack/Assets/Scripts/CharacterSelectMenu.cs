using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Rewired;

namespace StackAttack
{
    public class CharacterSelectMenu : MonoBehaviour
    {
        public GameObject gameSetupPrefab;
        GameSetup setup;
        public GameObject[] panels;
        public GameObject placeHolder;

        public Transform grid;

        void Start()
        {
            if ((setup = FindObjectOfType<GameSetup>()) == null)
            {
                GameObject gameSetupObj = Instantiate(gameSetupPrefab);
                setup = gameSetupObj.GetComponent<GameSetup>();
                setup.selectedCharacterPrefabs = new GameObject[ReInput.players.playerCount];
            }
            else
            {
                int activePanels = 0;
                for (int i = 0; i < ReInput.players.playerCount; i++)
                {
                    if (i < panels.Length && setup.selectedCharacterPrefabs[i] != null)
                    {
                        panels[i].SetActive(true);
                        activePanels++;
                    }
                }
                if (activePanels > 3)
                {
                    placeHolder.SetActive(false);
                }

                for (int i = 0; i < panels.Length; i++)
                {
                    if (panels[i] != null)
                    {
                        panels[i].transform.SetParent(null);
                        panels[i].transform.SetParent(grid);
                    } 
                }

                if (placeHolder.activeSelf)
                {
                    placeHolder.transform.SetParent(null);
                    placeHolder.transform.SetParent(grid);
                }
            }
        }

        void Update()
        {
            for (int i = 0; i < ReInput.players.playerCount; i++)
            {
                if (ReInput.players.GetPlayer(i).GetButtonDown("UISubmit"))
                {
                    panels[i].SetActive(true);
                    
                    bool allPanelsActive = true;
                    for (int j = 0; j < panels.Length; j++)
                    {
                        panels[j].transform.SetParent(null);
                        panels[j].transform.SetParent(grid);
                        if (!panels[j].activeSelf)
                        {
                            allPanelsActive = false;
                        }
                    }
                    
                    placeHolder.SetActive(!allPanelsActive);

                    if (placeHolder.activeSelf)
                    {
                        placeHolder.transform.SetParent(null);
                        placeHolder.transform.SetParent(grid);
                    }
                }
            }
        }
    }

}
