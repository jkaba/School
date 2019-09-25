using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using Rewired;

namespace StackAttack
{
    public class RankComparer : IComparer<MatchStats>
    {
        public int Compare(MatchStats p1, MatchStats p2)
        {
            if (p1.deathTime < p2.deathTime)
            {
                return -1;
            }
            else if (p1.deathTime == p2.deathTime)
            {
                return 0;
            }
            else
            {
                return 1;
            }
        }
    }

    public class MatchResultsMenu : MonoBehaviour
    {

        public GameObject matchResultPanelPrefab;
        public Transform horizontalLayout;

        static string[] rankString = { "1st", "2nd", "3rd", "4th", "5th", "6th"};


        GameSetup setup;

        public void Start()
        {
            setup = FindObjectOfType<GameSetup>();

            if (setup != null)
            {
                List<MatchStats> l = new List<MatchStats>();

                for (int i = 0; i < ReInput.players.playerCount; i++)
                {
                    if (setup.selectedCharacterPrefabs[i] != null && setup.rankings.ContainsKey(i))
                    {
                        GameObject matchResultObject = Instantiate(matchResultPanelPrefab, horizontalLayout);
                        MatchResultsPanel matchResultPanel = matchResultObject.GetComponent<MatchResultsPanel>();

                        MatchStats m = setup.rankings[i];
                        matchResultPanel.rankText.text = GetRankString(m) + " - P" + i;
                        matchResultPanel.rewardText.text = m.coinReward + " Points";
                        matchResultPanel.playerImage.sprite = setup.selectedCharacterPrefabs[i].GetComponentInChildren<SpriteRenderer>().sprite;
                    }
                }
            }
        }

        string GetRankString(MatchStats m)
        {
            if (m.tie)
            {
                return "Draw";
            }

            if (m.deathTime < 0f)
            {
                return rankString[0];
            }

            List<MatchStats> l = new List<MatchStats>();
            for (int i = 0; i < ReInput.players.playerCount; i++)
            {
                if (setup.rankings.ContainsKey(i))
                {
                    l.Add(setup.rankings[i]);
                }
            }

            l.Sort(new RankComparer());

            int index = l.IndexOf(m);

            if (index == 0)
            {
                // Can't be 1st, AI won.
                return "Last";
            }

            if (index < rankString.Length - 1)
                return rankString[index];
            else
                return "Last"; // I'm cheating a little
        }

    }
}
