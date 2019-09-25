using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

namespace StackAttack
{

    /// <summary>
    /// A class for controlling time, spawn position and other aspects
    /// of each level. This is based on code from the following videos:
    /// https://www.youtube.com/watch?v=x-C95TuQtf0 (timer)
    /// https://www.youtube.com/watch?v=QWcbPOPwcBs&t=416s (fighting)
    /// </summary>
    public class TimerScript : MonoBehaviour
    {
        public Text timer;
        public Transform[] spawnPositions;


        private bool runTimer = false; //checks whether the timer should run or not
        public float beginTime;
        private float elapsedTime;

        // Use this for initialization
        void Start()
        {
            StartTimer();
        }

        // Update is called once per frame
        void Update()
        {
            if (runTimer)
            {
                RunTimer();
            }
            else
            {
                StopTimer();
                ResetTimer();
            }
        }

        public void StartTimer()
        {
            runTimer = true;
            ResetTimer();
        }

        public void StopTimer()
        {
            runTimer = false;

        }

        public float GetElapsedTime()
        {
            return beginTime - Time.time;
        }

        public void RunTimer()
        {

            elapsedTime = beginTime - Time.time;

            string minutes = ((int)elapsedTime / 60).ToString();
            //convert seconds to string with only one decimal place
            string seconds = ((int)(elapsedTime % 60)).ToString();


            if (elapsedTime <= 0.0f)
            {
                StopTimer();
                SetMatchResults();
                SceneManager.LoadScene("MatchResults");
            }

            //display timer text
            if (elapsedTime < 60)
            {

                timer.color = Color.red;

                if (elapsedTime % 60 <= 10)
                {
                    timer.text = "0:0" + seconds;
                }
                else
                {
                    timer.text = "0:" + seconds;
                }

            }
            else
            {
                if (elapsedTime % 60 <= 10)
                {
                    timer.text = minutes + ":0" + seconds;
                }
                else
                {
                    timer.text = minutes + ":" + seconds;
                }
            }

        }

        public void ResetTimer()
        {
            beginTime = beginTime + Time.time;
        }

        public void SetMatchResults()
        {
            GameManager gm = FindObjectOfType<GameManager>();
            if (gm != null)
            {
                GameSetup gs = FindObjectOfType<GameSetup>();
                if (gs != null)
                {
                    foreach (GameObject player in gm.players)
                    {
                        if (player.GetComponent<UserCharacterController>() != null)
                        {
                            int playerIndex = player.GetComponent<UserCharacterController>().playerId;

                            if (gs.rankings.ContainsKey(playerIndex))
                            {
                                TimerScript ts = FindObjectOfType<TimerScript>();
                                if (ts != null)
                                {
                                    gs.rankings[playerIndex].deathTime = ts.GetElapsedTime();
                                }
                                gs.rankings[playerIndex].coinReward = 0;
                                gs.rankings[playerIndex].tie = true;
                            }
                            else
                            {
                                MatchStats ms = new MatchStats();
                                TimerScript ts = FindObjectOfType<TimerScript>();
                                if (ts != null)
                                {
                                    gs.rankings[playerIndex].deathTime = ts.GetElapsedTime();
                                }
                                ms.coinReward = 0;
                                ms.coinTotal = 0;
                                ms.tie = true;
                                gs.rankings.Add(playerIndex, ms);
                            }
                        }
                    }
                }
            }
        }
    }
}